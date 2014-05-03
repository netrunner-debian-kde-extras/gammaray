/*
  styleinspectorinterface.h

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

#ifndef GAMMARAY_STYLEINSPECTORINTERFACE_H
#define GAMMARAY_STYLEINSPECTORINTERFACE_H

#include <QObject>

class QSize;

namespace GammaRay {

class StyleInspectorInterface : public QObject
{
  Q_OBJECT
  public:
    explicit StyleInspectorInterface(QObject *parent = 0);
    virtual ~StyleInspectorInterface();

    int cellHeight() const;
    int cellWidth() const;
    int cellZoom() const;
    QSize cellSizeHint() const;

  signals:
    void cellSizeChanged();

  public slots:
    virtual void setCellHeight(int height);
    virtual void setCellWidth(int width);
    virtual void setCellZoom(int zoom);

  private:
    int m_cellHeight;
    int m_cellWidth;
    int m_cellZoom;
};

}

Q_DECLARE_INTERFACE(GammaRay::StyleInspectorInterface, "com.kdab.GammaRay.StyleInspectorInterface")

#endif // GAMMARAY_STYLEINSPECTORINTERFACE_H