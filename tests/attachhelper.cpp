/*
  attachdialog.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2011 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Milian Wolff <milian.wolff@kdab.com>

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

#include "attachhelper.h"

#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

#include <QCoreApplication>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QDateTime>

AttachHelper::AttachHelper(const QString &gammaray, const QString &injector,
                           const QString &debuggee, const QStringList &arguments,
                           QObject *parent)
  : QObject(parent),
    m_timer(new QTimer(this)),
    m_proc(new QProcess(this)),
    m_gammaray(gammaray),
    m_injector(injector)
{
  m_proc->setProcessChannelMode(QProcess::ForwardedChannels);
  connect(m_proc, SIGNAL(started()), this, SLOT(processStarted()));
  connect(m_proc, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
  m_proc->start(debuggee, arguments);
}

void AttachHelper::processStarted()
{
  // attach randomly after 1-1500 ms
  qsrand(QDateTime::currentMSecsSinceEpoch());
  const int timeout = qrand() % 1500 + 1;
  qDebug() << "attaching gammaray in" << timeout << "ms";
  m_timer->setSingleShot(true);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(attach()));
  m_timer->start(timeout);
}

void AttachHelper::processFinished(int exitCode)
{
  qApp->exit(exitCode);
}

void AttachHelper::attach()
{
  if (m_proc->state() != QProcess::Running) {
    return;
  }
  qDebug() << "attaching gammaray";
  QProcess gammaray;
  QStringList args;
#ifdef Q_OS_WIN32
  args << "-i" << m_injector << "-p" << QString::number(m_proc->pid()->dwProcessId);
#else
  args << "-i" << m_injector << "-p" << QString::number(m_proc->pid());
#endif
  args << "-nodialogs";
  const int ret = gammaray.execute(m_gammaray, args);
  if (ret != 0) {
    m_proc->kill();
    qFatal("could not attach to debuggee");
  }
}

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  if (app.arguments().size() < 4) {
    qWarning() << "usage: " << app.applicationName()
               << " GAMMARAY INJECTOR DEBUGGEE [DEBUGGEE_ARGS]";
    return 1;
  }

  QStringList args = app.arguments();
  // remove path to this bin
  args.removeFirst();
  // gammaray
  const QString gammaray = args.takeFirst();
  // injector
  const QString injector = args.takeFirst();
  // app to run
  const QString debuggee = args.takeFirst();

  AttachHelper helper(gammaray, injector, debuggee, args);

  return app.exec();
}

#include "attachhelper.moc"
