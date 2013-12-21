/*
  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Funk <kevin.funk@kdab.com>

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

#include "toolpluginerrormodel.h"

using namespace GammaRay;

ToolPluginErrorModel::ToolPluginErrorModel(const PluginLoadErrors& errors, QObject* parent)
  : QAbstractTableModel(parent), m_errors(errors)
{
}

ToolPluginErrorModel::~ToolPluginErrorModel()
{
}

int ToolPluginErrorModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return 3;
}

int ToolPluginErrorModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return m_errors.size();
}

QVariant ToolPluginErrorModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  const int row = index.row();
  const int column = index.column();
  if (role == Qt::DisplayRole) {
    switch (column) {
    case 0:
      return m_errors[row].pluginName();
    case 1:
      return m_errors[row].pluginFile;
    case 2:
      return m_errors[row].errorString;
    }
  }
  return QVariant();
}

QVariant ToolPluginErrorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return tr("Plugin Name");
    case 1:
      return tr("Plugin File");
    case 2:
      return tr("Error Message");
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

