/*
  launcherfinder.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "launcherfinder.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

using namespace GammaRay;

const char *executableNames[] = {
  "gammaray",          // the Injector
  "gammaray-launcher", // the LauncherUI
  "gammaray-client"    // the Client
};

QString LauncherFinder::findLauncher(LauncherFinder::Type type)
{
  QString fileName = executableNames[type];
#ifdef Q_OS_WIN
  fileName += ".exe";
#endif

  QStringList appPaths; //a list of all the paths we have searched

  QString appPath =
    QCoreApplication::applicationDirPath() + QDir::separator() + fileName;
  QFileInfo fi(appPath);
  if (fi.isExecutable()) {
    return fi.absoluteFilePath();
  }
  appPaths.append(appPath);

  appPath =
    QLatin1String(GAMMARAY_LOCAL_INSTALL_PREFIX) +
    QDir::separator() + QLatin1String(GAMMARAY_LIBEXEC_INSTALL_DIR) + \
    QDir::separator() + fileName;
  if(!appPaths.contains(appPath)) {
    fi.setFile(appPath);
    if (fi.isExecutable()) {
      return fi.absoluteFilePath();
    }
    appPaths.append(appPath);
  }

  qWarning() << fileName << "not found in the expected location(s):";
  qWarning() << appPaths.join(", ") << endl
             << "continuing anyway, hoping for it to be in PATH.";
  qWarning() << "This is likely a setup problem." << endl;
  return fileName;
}
