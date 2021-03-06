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

#include "qmatrixtransform.h"
#include "qmatrixtransform_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {

QMatrixTransformPrivate::QMatrixTransformPrivate(QMatrixTransform *qq)
    : QAbstractTransformPrivate(qq)
{
}

QMatrixTransform::QMatrixTransform(QMatrixTransformPrivate &dd, QNode *parent)
    : QAbstractTransform(dd, parent)
{
}

void QMatrixTransform::copy(const QNode *ref)
{
    QAbstractTransform::copy(ref);
    const QMatrixTransform *matrix = static_cast<const QMatrixTransform*>(ref);
    d_func()->m_matrix = matrix->d_func()->m_matrix;
}

QMatrixTransform::QMatrixTransform(QNode *parent)
    : QAbstractTransform(*new QMatrixTransformPrivate(this), parent)
{
}

QMatrixTransform::QMatrixTransform(const QMatrix4x4& m, QNode *parent)
    : QAbstractTransform(*new QMatrixTransformPrivate(this), parent)
{
    Q_D(QMatrixTransform);
    d->m_matrix = m;
}

QMatrix4x4 QMatrixTransform::matrix() const
{
    Q_D(const QMatrixTransform);
    return d->m_matrix;
}

void QMatrixTransform::setMatrix(const QMatrix4x4 &matrix)
{
    Q_D(QMatrixTransform);
    if (d->m_matrix != matrix) {
        d->m_matrix = matrix;
        emit matrixChanged();
        emit transformMatrixChanged();
    }
}

QMatrix4x4 QMatrixTransform::transformMatrix() const
{
    return matrix();
}

} // namespace Qt3D

QT_END_NAMESPACE
