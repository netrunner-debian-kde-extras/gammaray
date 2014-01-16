/*
  networkselectionmodel.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef GAMMARAY_NETWORKSELECTIONMODEL_H
#define GAMMARAY_NETWORKSELECTIONMODEL_H

#include <QItemSelectionModel>
#include "protocol.h"

namespace GammaRay {

class Message;

/** Base class for network-transparent item selection models, do not use directly. */
class NetworkSelectionModel : public QItemSelectionModel
{
  Q_OBJECT
public:
  ~NetworkSelectionModel();

protected:
  explicit NetworkSelectionModel(const QString &objectName, QAbstractItemModel *model, QObject *parent = 0);
  QString m_objectName;
  Protocol::ObjectAddress m_myAddress;

private slots:
  void newMessage(const GammaRay::Message &msg);

  void slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
  void slotCurrentColumnChanged(const QModelIndex &current, const QModelIndex &previous);
  void slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);
  void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
  bool m_handlingRemoteMessage;
};

}

#endif // GAMMARAY_NETWORKSELECTIONMODEL_H
