/*
  metaobjectbrowserwidget.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

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

#include "metaobjectbrowserwidget.h"
#include "propertywidget.h"
#include <ui/deferredresizemodesetter.h>
#include <ui/deferredtreeviewconfiguration.h>
#include <ui/searchlinecontroller.h>

#include <common/objectbroker.h>

#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QTreeView>

using namespace GammaRay;

MetaObjectBrowserWidget::MetaObjectBrowserWidget(QWidget *parent)
  : QWidget(parent)
{
  QAbstractItemModel *model = ObjectBroker::model(QStringLiteral("com.kdab.GammaRay.MetaObjectBrowserTreeModel"));

  QTreeView *treeView = new QTreeView(this);
  treeView->setIndentation(10);
  treeView->setUniformRowHeights(true);
  treeView->setModel(model);
  new DeferredResizeModeSetter(treeView->header(), 0, QHeaderView::Stretch);
  treeView->setSortingEnabled(true);
  treeView->setSelectionModel(ObjectBroker::selectionModel(model));

  auto objectSearchLine = new QLineEdit(this);
  new SearchLineController(objectSearchLine, model);

  PropertyWidget *propertyWidget = new PropertyWidget(this);
  m_propertyWidget = propertyWidget;
  m_propertyWidget->setObjectBaseName(QStringLiteral("com.kdab.GammaRay.MetaObjectBrowser"));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(objectSearchLine);
  vbox->addWidget(treeView);

  QHBoxLayout *hbox = new QHBoxLayout(this);
  hbox->addLayout(vbox);
  hbox->addWidget(propertyWidget);

  // init widget
  new DeferredTreeViewConfiguration(treeView);
  treeView->sortByColumn(0, Qt::AscendingOrder);
}

