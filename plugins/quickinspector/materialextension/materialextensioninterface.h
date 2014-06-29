/*
  materialextensioninterface.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef GAMMARAY_QUICKINSPECTOR_MATERIALEXTENSIONINTERFACE_H
#define GAMMARAY_QUICKINSPECTOR_MATERIALEXTENSIONINTERFACE_H

#include <QObject>

namespace GammaRay {

/** @brief Client/Server interface of the material viewer. */
class MaterialExtensionInterface : public QObject
{
  Q_OBJECT
  public:
    explicit MaterialExtensionInterface(const QString &name, QObject *parent = 0);
    virtual ~MaterialExtensionInterface();

    const QString &name() const;

  signals:
    void shaderListChanged(const QStringList &materialList);
    void gotShader(const QString &shaderSource);

  public slots:
    virtual void getShader(const QString &fileName) = 0;

  private:
    QString m_name;
};

}

Q_DECLARE_INTERFACE(GammaRay::MaterialExtensionInterface,
                    "com.kdab.GammaRay.MaterialExtensionInterface")

#endif // GAMMARAY_MATERIALEXTENSIONINTERFACE_H
