/*
  launcherwindow.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2011-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef GAMMARAY_LAUNCHERWINDOW_H
#define GAMMARAY_LAUNCHERWINDOW_H

#include <QDialog>

namespace GammaRay {

namespace Ui {
  class LauncherWindow;
}

class LauncherWindow : public QDialog
{
  Q_OBJECT
  public:
    explicit LauncherWindow(QWidget *parent = 0);
    ~LauncherWindow();

    /// returns the selected PID, if the attach page is active
    QString pid() const;

    /// returns the command and arguments, if the launch page is active
    QStringList launchArguments() const;

    void accept();

  private slots:
    void tabChanged();

  private:
    Ui::LauncherWindow *ui;
};

}

#endif // GAMMARAY_LAUNCHERWINDOW_H
