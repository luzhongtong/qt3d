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

#ifndef QT3D_QLOOKATTRANSFORM_H
#define QT3D_QLOOKATTRANSFORM_H

#include <Qt3DCore/qabstracttransform.h>
#include <Qt3DCore/qt3dcore_global.h>

#include <QVector3D>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class QLookAtTransformPrivate;

class QT3DCORESHARED_EXPORT QLookAtTransform : public Qt3D::QAbstractTransform
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D upVector READ upVector WRITE setUpVector NOTIFY upVectorChanged)
    Q_PROPERTY(QVector3D viewCenter READ viewCenter WRITE setViewCenter NOTIFY viewCenterChanged)
    Q_PROPERTY(QVector3D viewVector READ viewVector NOTIFY viewVectorChanged)

public:
    explicit QLookAtTransform(QNode *parent = 0);

    QMatrix4x4 transformMatrix() const Q_DECL_OVERRIDE;

    void setPosition(const QVector3D &position);
    QVector3D position() const;

    void setUpVector(const QVector3D &upVector);
    QVector3D upVector() const;

    void setViewCenter(const QVector3D &viewCenter);
    QVector3D viewCenter() const;

    void setViewVector(const QVector3D &viewVector);
    QVector3D viewVector() const;

Q_SIGNALS:
    void positionChanged();
    void upVectorChanged();
    void viewCenterChanged();
    void viewVectorChanged();

protected:
    QLookAtTransform(QLookAtTransformPrivate &dd, QNode *parent = 0);
    void copy(const QNode *ref) Q_DECL_OVERRIDE;

private:
    QT3D_CLONEABLE(QLookAtTransform)
    Q_DECLARE_PRIVATE(QLookAtTransform)
};

} // namespace Qt3D

QT_END_NAMESPACE

#endif // QT3D_QLOOKATTRANSFORM_H
