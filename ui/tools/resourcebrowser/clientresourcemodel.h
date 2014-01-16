/*
  clientresourcemodel.h

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

#ifndef GAMMARAY_CLIENTRESOURCEMODEL_H
#define GAMMARAY_CLIENTRESOURCEMODEL_H

#include "kde/krecursivefilterproxymodel.h"
#include <QFileIconProvider>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0 ,0)
#include <QMimeDatabase>
#endif

namespace GammaRay {

/**
 * Adds file icons for the resource model.
 * This can't be done server-side since the icon stuff might not exist in a pure QtCore application.
 */
class ClientResourceModel : public KRecursiveFilterProxyModel
{
    Q_OBJECT
public:
  explicit ClientResourceModel(QObject *parent = 0);
  ~ClientResourceModel();

  /*override*/ QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
  QFileIconProvider m_iconProvider;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
  QMimeDatabase m_mimeDb;
#endif
};
}

#endif // GAMMARAY_CLIENTRESOURCEMODEL_H
