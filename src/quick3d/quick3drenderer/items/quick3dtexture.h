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

#ifndef QT3D_RENDER_QUICK_QUICK3DTEXTURE_H
#define QT3D_RENDER_QUICK_QUICK3DTEXTURE_H

#include <Qt3DQuickRenderer/qt3dquickrenderer_global.h>
#include <Qt3DQuick/quick3dnode.h>
#include <Qt3DRenderer/qtexture.h>

#include <QUrl>

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture1D : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture1D(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture1DArray : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture1DArray(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture2D : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture2D(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture2DArray : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture2DArray(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture3D : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture3D(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTextureCubeMap : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTextureCubeMap(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTextureCubeMapArray : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTextureCubeMapArray(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture2DMultisample : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture2DMultisample(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture2DMultisampleArray : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTexture2DMultisampleArray(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTextureRectangle : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTextureRectangle(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTextureBuffer : public QTexture
{
    Q_OBJECT
public:
    explicit Quick3DTextureBuffer(QNode *parent = 0);
};

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTexture2DExtension : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit Quick3DTexture2DExtension(QObject *parent = 0);

    QUrl source() const;
    void setSource(QUrl arg);

Q_SIGNALS:
    void sourceChanged();

private:
    QUrl m_source;
    inline Qt3D::QTexture *parentTexture() const { return qobject_cast<Qt3D::QTexture *>(parent()); }
};

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE

#endif // QUICK3DTEXTURE_H
