/*
  methodargumentmodel.h

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

#ifndef GAMMARAY_METHODARGUMENTMODEL_H
#define GAMMARAY_METHODARGUMENTMODEL_H

#include <QAbstractTableModel>
#include <QMetaMethod>
#include <QVector>

namespace GammaRay {

class SafeArgument
{
  public:
    SafeArgument();
    explicit SafeArgument(const QVariant &v);
    ~SafeArgument();
    operator QGenericArgument () const;

  private:
    QVariant m_value;
    QByteArray m_name;
    mutable void *m_data;
};

class MethodArgumentModel : public QAbstractTableModel
{
  Q_OBJECT
  public:
    explicit MethodArgumentModel(QObject *parent = 0);
    void setMethod(const QMetaMethod &method);
    QVector<SafeArgument> arguments() const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

  private:
    QMetaMethod m_method;
    QVector<QVariant> m_arguments;
};

}

#endif // GAMMARAY_METHODARGUMENTMODEL_H
