/*
  selectionmodelinspectorwidget.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Stephen Kelly <stephen.kelly@kdab.com>

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

#include "selectionmodelinspectorwidget.h"
#include "ui_selectionmodelinspectorwidget.h"

#include <common/objectmodel.h>
#include <common/objectbroker.h>

using namespace GammaRay;

SelectionModelInspectorWidget::SelectionModelInspectorWidget(QWidget *widget)
  : QWidget(widget), ui(new Ui::SelectionModelInspectorWidget)
{
  ui->setupUi(this);

  ui->selectionModelView->setModel(ObjectBroker::model("com.kdab.GammaRay.SelectionModelsModel"));
  ui->selectionModelView->setRootIsDecorated(false);
  ui->selectionModelView->setSelectionModel(ObjectBroker::selectionModel(ui->selectionModelView->model()));
  ui->selectionModelVisualizer->setRootIsDecorated(false);
  ui->selectionModelVisualizer->setModel(ObjectBroker::model("com.kdab.GammaRay.CurrentSelectionModel"));
}

SelectionModelInspectorWidget::~SelectionModelInspectorWidget()
{
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN(SelectionModelInspectorUiFactory)
#endif
