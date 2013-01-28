/*
  multisignalmapper.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef GAMMARAY_MULTISIGNALMAPPER_H
#define GAMMARAY_MULTISIGNALMAPPER_H

#include <QObject>
#include <QVector>

class QSignalMapper;

namespace GammaRay {

/**
 * A signal mapper that can deal with multiple signals from the same sender.
 */
class MultiSignalMapper : public QObject
{
  Q_OBJECT
  public:
    explicit MultiSignalMapper(QObject *parent = 0);
    ~MultiSignalMapper();

    void connectToSignal(QObject *sender, const QMetaMethod &signal);

  signals:
    void signalEmitted(QObject *sender, int signalIndex);

  private slots:
    void slotMapped(QObject *object);

  private:
    QVector<QSignalMapper*> m_mappers;
};

}

#endif // GAMMARAY_MULTISIGNALMAPPER_H
