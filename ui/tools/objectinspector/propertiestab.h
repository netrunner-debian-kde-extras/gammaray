/*
  propertiestab.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Anton Kreuzkamp <anton.kreuzkamp@kdab.com>

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

#ifndef PROPERTIESTAB_H
#define PROPERTIESTAB_H

#include <QWidget>

class QModelIndex;

namespace GammaRay {

class PropertiesExtensionInterface;

class Ui_PropertiesTab;
class PropertyWidget;

class PropertiesTab : public QWidget
{
  Q_OBJECT
  public:
    explicit PropertiesTab(PropertyWidget *parent);
    virtual ~PropertiesTab();

  private:
    void setObjectBaseName(const QString &baseName);

  private slots:
    void updateNewPropertyValueEditor();
    void validateNewProperty();
    void propertyContextMenu(const QPoint &pos);
    void onDoubleClick(const QModelIndex &index);
    void addNewProperty();

  private:
    Ui_PropertiesTab *m_ui;
    PropertiesExtensionInterface *m_interface;

    QWidget *m_newPropertyValue;
};

}

#endif // PROPERTIESTAB_H
