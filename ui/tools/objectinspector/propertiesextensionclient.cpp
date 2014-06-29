/*
  propertiesextensionclient.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Milian Wolff <milian.wolff@kdab.com>

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

#include "propertiesextensionclient.h"

#include <common/endpoint.h>
#include <common/metatypedeclarations.h>
#include <common/variantwrapper.h>

using namespace GammaRay;

PropertiesExtensionClient::PropertiesExtensionClient(const QString &name, QObject *parent)
  : PropertiesExtensionInterface(name, parent)
{

}

PropertiesExtensionClient::~PropertiesExtensionClient()
{

}

void PropertiesExtensionClient::navigateToValue(int modelRow)
{
  Endpoint::instance()->invokeObject(name(), "navigateToValue", QVariantList() << QVariant::fromValue(modelRow));
}

void PropertiesExtensionClient::setProperty(const QString& propertyName, const QVariant& value)
{
  Endpoint::instance()->invokeObject(name(), "setProperty", QVariantList() << QVariant::fromValue(propertyName) << VariantWrapper(value));
}

void PropertiesExtensionClient::resetProperty(const QString& propertyName)
{
  Endpoint::instance()->invokeObject(name(), "resetProperty", QVariantList() << QVariant::fromValue(propertyName));
}
