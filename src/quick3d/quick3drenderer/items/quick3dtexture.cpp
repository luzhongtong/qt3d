/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "quick3dtexture.h"
#include <QDebug>

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

Quick3DTexture1D::Quick3DTexture1D(QNode *parent)
    : QTexture(Target1D, parent)
{
}

Quick3DTexture1DArray::Quick3DTexture1DArray(QNode *parent)
    : QTexture(Target1DArray, parent)
{
}

Quick3DTexture2D::Quick3DTexture2D(QNode *parent)
    : QTexture(Target2D, parent)
{
}

Quick3DTexture2DArray::Quick3DTexture2DArray(QNode *parent)
    : QTexture(Target2DArray, parent)
{
}

Quick3DTexture3D::Quick3DTexture3D(QNode *parent)
    : QTexture(Target3D, parent)
{
}

Quick3DTextureCubeMap::Quick3DTextureCubeMap(QNode *parent)
    : QTexture(TargetCubeMap, parent)
{
}

Quick3DTextureCubeMapArray::Quick3DTextureCubeMapArray(QNode *parent)
    : QTexture(TargetCubeMapArray, parent)
{
}

Quick3DTexture2DMultisample::Quick3DTexture2DMultisample(QNode *parent)
    : QTexture(Target2DMultisample, parent)
{
}

Quick3DTexture2DMultisampleArray::Quick3DTexture2DMultisampleArray(QNode *parent)
    : QTexture(Target2DMultisampleArray, parent)
{
}

Quick3DTextureRectangle::Quick3DTextureRectangle(QNode *parent)
    : QTexture(TargetRectangle, parent)
{
}

Quick3DTextureBuffer::Quick3DTextureBuffer(QNode *parent)
    : QTexture(TargetBuffer, parent)
{
}

// TO DO: This needs to be reworked to handle more than just 2D images
Quick3DTexture2DExtension::Quick3DTexture2DExtension(QObject *parent)
    : QObject(parent)
{
}

QUrl Quick3DTexture2DExtension::source() const
{
    return m_source;
}

void Quick3DTexture2DExtension::setSource(QUrl arg)
{
    if (m_source != arg) {
        m_source = arg;
        // There is maybe a better way to check for resources files
        if (m_source.isLocalFile() || m_source.scheme() == QStringLiteral("qrc")) {
            QString source = m_source.toString().replace(QStringLiteral("qrc"), QStringLiteral(""));
            QImage img;
            if (img.load(source)) {
                parentTexture()->setFormat(img.hasAlphaChannel() ?
                                                       QTexture::RGBA8_UNorm :
                                                       QTexture::RGB8_UNorm);
                parentTexture()->setFromQImage(img);
            }
            else {
                qWarning() << "Failed to load image : " << source;
            }

        } else {
            qWarning() << "implement loading from remote URLs";
        }
        emit sourceChanged();
    }
}

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE
