/*
  methodsextension.h

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

#ifndef GAMMARAY_OBJECTINSPECTOR_METHODSEXTENSION_H
#define GAMMARAY_OBJECTINSPECTOR_METHODSEXTENSION_H

#include "common/tools/objectinspector/methodsextensioninterface.h"
#include "core/propertycontrollerextension.h"

#include <QPointer>

class QStandardItemModel;

namespace GammaRay {

class PropertyController;
class ObjectMethodModel;
class MethodArgumentModel;
class MultiSignalMapper;

class MethodsExtension : public MethodsExtensionInterface, public PropertyControllerExtension
{
  Q_OBJECT
  Q_INTERFACES(GammaRay::MethodsExtensionInterface)

  public:
    explicit MethodsExtension(PropertyController *controller);
    ~MethodsExtension();

    bool setQObject(QObject *object);
    bool setMetaObject(const QMetaObject *metaObject);

  public slots:
    void activateMethod();
    void invokeMethod(Qt::ConnectionType type);
    void connectToSignal();

  private slots:
    void signalEmitted(QObject *sender, int signalIndex, const QVector<QVariant> &args);

  private:
    ObjectMethodModel *m_model;
    QStandardItemModel *m_methodLogModel;
    MethodArgumentModel *m_methodArgumentModel;
    MultiSignalMapper *m_signalMapper;
    QPointer<QObject> m_object;
};

}

#endif // METHODSEXTENSION_H
