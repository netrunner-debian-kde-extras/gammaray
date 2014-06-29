/*
  probeabidetector_mac.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config-gammaray.h"

#include "probeabidetector.h"
#include "probeabi.h"

#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QString>

#include <mach-o/loader.h>

using namespace GammaRay;

static QString qtCoreFromOtool(const QString &path)
{
  QProcess proc;
  proc.setProcessChannelMode(QProcess::SeparateChannels);
  proc.setReadChannel(QProcess::StandardOutput);
  proc.start("otool", QStringList() << "-L" << path);
  proc.waitForFinished();

  forever {
    const QByteArray line = proc.readLine();
    if (line.isEmpty())
      break;

    if (ProbeABIDetector::containsQtCore(line)) {
      const int pos = line.lastIndexOf(" (");
      if (pos <= 0)
        continue;
      return QString::fromLocal8Bit(line.left(pos).trimmed());
    }
  }

  return QString();
}

ProbeABI ProbeABIDetector::abiForExecutable(const QString& path) const
{
  const QString qtCorePath = qtCoreFromOtool(path);
  if (qtCorePath.isEmpty())
    return ProbeABI();

  return abiForQtCore(qtCorePath);
}


ProbeABI ProbeABIDetector::abiForProcess(qint64 pid) const
{
  const QString qtCorePath = qtCoreFromLsof(pid);
  if (qtCorePath.isEmpty())
    return ProbeABI();

  return abiForQtCore(qtCorePath);
}


template <typename T>
static QString readMachOHeader(const uchar* data, quint64 size, quint32 &offset, qint32 &ncmds, qint32 &cmdsize)
{
  if (size <= sizeof(T))
    return QString();
  const T* header = reinterpret_cast<const T*>(data);

  offset = sizeof(T);
  ncmds = header->ncmds;
  cmdsize = header->sizeofcmds;

  switch (header->cputype) {
    case CPU_TYPE_I386: return "i686";
    case CPU_TYPE_X86_64: return "x86_64";
  }

  return QString();
}

static ProbeABI abiFromMachO(const uchar* data, qint64 size)
{
  ProbeABI abi;
  const quint32 magic = *reinterpret_cast<const quint32*>(data);

  quint32 offset = 0;
  qint32 ncmds = 0;
  qint32 cmdsize = 0;

  switch (magic) {
    case MH_MAGIC:
      abi.setArchitecture(readMachOHeader<mach_header>(data, size, offset, ncmds, cmdsize));
      break;
    case MH_MAGIC_64:
      abi.setArchitecture(readMachOHeader<mach_header_64>(data, size, offset, ncmds, cmdsize));
      break;
  }

  if (offset >= size || ncmds <= 0 || cmdsize <= 0 || size <= offset + cmdsize)
    return ProbeABI();

  // read load commands
  for (int i = 0; i < ncmds; ++i) {
    const load_command* cmd = reinterpret_cast<const load_command*>(data + offset);
    if (cmd->cmd == LC_ID_DYLIB) {
      const dylib_command* dlcmd = reinterpret_cast<const dylib_command*>(data + offset);
      const int majorVersion = (dlcmd->dylib.current_version & 0x00ff0000) >> 16;
      const int minorVersion = (dlcmd->dylib.current_version & 0x0000ff00) >> 8;
      abi.setQtVersion(majorVersion, minorVersion);
    }
    offset += cmd->cmdsize;
  }

  return abi;
}

ProbeABI ProbeABIDetector::detectAbiForQtCore(const QString& path) const
{
  QFile f(path);
  if (!f.open(QFile::ReadOnly))
    return ProbeABI();

  const uchar* data = f.map(0, f.size());
  if (!data || (uint)f.size() <= sizeof(quint32))
    return ProbeABI();
  return abiFromMachO(data, f.size());
}
