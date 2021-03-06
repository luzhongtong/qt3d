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

#include "trefoilknot.h"

TrefoilKnot::TrefoilKnot(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_mesh(new Qt3D::QMesh())
    , m_transform(new Qt3D::QTransform())
    , m_scaleTransform(new Qt3D::QScaleTransform())
    , m_xaxisRotation(new Qt3D::QRotateTransform())
    , m_yaxisRotation(new Qt3D::QRotateTransform())
    , m_translateTransform(new Qt3D::QTranslateTransform())
{
    m_mesh->setSource(QUrl("qrc:/assets/obj/trefoil.obj"));
    m_xaxisRotation->setAxis(QVector3D(1.0f, 0.0f, 0.0f));
    m_yaxisRotation->setAxis(QVector3D(0.0f, 1.0f, 0.0f));

    m_transform->addTransform(m_scaleTransform);
    m_transform->addTransform(m_xaxisRotation);
    m_transform->addTransform(m_yaxisRotation);
    m_transform->addTransform(m_translateTransform);

    addComponent(m_mesh);
    addComponent(m_transform);
}

TrefoilKnot::~TrefoilKnot()
{
}

Qt3D::QScaleTransform *TrefoilKnot::scaleTransform() const
{
    return m_scaleTransform;
}

Qt3D::QRotateTransform *TrefoilKnot::xaxisRotateTransform() const
{
    return m_xaxisRotation;
}

Qt3D::QRotateTransform *TrefoilKnot::yaxisRotateTransform() const
{
    return m_yaxisRotation;
}

Qt3D::QTranslateTransform *TrefoilKnot::translateTransform() const
{
    return m_translateTransform;
}
