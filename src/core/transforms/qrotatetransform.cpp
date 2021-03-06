/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES // For MSVC
#endif

#include "qrotatetransform.h"
#include "qrotatetransform_p.h"

#include <cmath>

QT_BEGIN_NAMESPACE

namespace Qt3D {

QRotateTransformPrivate::QRotateTransformPrivate(QRotateTransform *qq)
    : QAbstractTransformPrivate(qq)
    , m_angleDeg(0)
    , m_axis(0.0f, 1.0f, 0.0f)
{
    updateMatrix();
}

void QRotateTransformPrivate::updateMatrix()
{
    QMatrix4x4 m;
    m.rotate(m_angleDeg, m_axis);
    m_matrix = m;
}

void QRotateTransform::copy(const QNode *ref)
{
    QAbstractTransform::copy(ref);
    const QRotateTransform *transform = static_cast<const QRotateTransform*>(ref);
    d_func()->m_axis = transform->d_func()->m_axis;
    d_func()->m_angleDeg = transform->d_func()->m_angleDeg;
}

QRotateTransform::QRotateTransform(QNode *parent)
    : QAbstractTransform(*new QRotateTransformPrivate(this), parent)
{
}

QRotateTransform::QRotateTransform(QRotateTransformPrivate &dd, QNode *parent)
    : QAbstractTransform(dd, parent)
{
}

float QRotateTransform::angleDeg() const
{
    Q_D(const QRotateTransform);
    return d->m_angleDeg;
}

float Qt3D::QRotateTransform::angleRad() const
{
    Q_D(const QRotateTransform);
    return (d->m_angleDeg / 180.0) * M_PI;
}

QVector3D QRotateTransform::axis() const
{
    Q_D(const QRotateTransform);
    return d->m_axis;
}

QMatrix4x4 QRotateTransform::transformMatrix() const
{
    Q_D(const QRotateTransform);
    return d->m_matrix;
}

void QRotateTransform::setAngleDeg(float arg)
{
    Q_D(QRotateTransform);
    if (d->m_angleDeg != arg) {
        d->m_angleDeg = arg;
        d->updateMatrix();
        emit angleChanged();
        emit transformMatrixChanged();
    }
}

void QRotateTransform::setAngleRad(float arg)
{
    float angleDeg = (arg * M_PI) / 180.0f;
    setAngleDeg(angleDeg);
}

void QRotateTransform::setAxis(const QVector3D& arg)
{
    Q_D(QRotateTransform);
    if (d->m_axis != arg) {
        d->m_axis = arg;
        d->updateMatrix();
        emit axisChanged();
        emit transformMatrixChanged();
    }
}

} // namespace Qt3D

QT_END_NAMESPACE
