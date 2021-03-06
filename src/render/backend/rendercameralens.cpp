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

#include "rendercameralens_p.h"
#include <Qt3DRenderer/private/renderlogging_p.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qcameralens.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qscenepropertychange.h>

#include <QOpenGLContext>

QT_BEGIN_NAMESPACE

namespace Qt3D {
namespace Render {

RenderCameraLens::RenderCameraLens()
    : QBackendNode()
{
    m_clearColor = QVector4D(0.5, 0.5, 1.0, 1.0);
}

RenderCameraLens::~RenderCameraLens()
{
    cleanup();
}

void RenderCameraLens::cleanup()
{

}

void RenderCameraLens::updateFromPeer(QNode *peer)
{
    QCameraLens *lens = static_cast<QCameraLens *>(peer);
    setProjection(lens->projectionMatrix());
    m_enabled = lens->isEnabled();
}

void RenderCameraLens::setProjection(const QMatrix4x4 &projection)
{
    m_projection = projection;
}

void RenderCameraLens::sceneChangeEvent(const QSceneChangePtr &e)
{
    switch (e->type()) {
    case NodeUpdated: {
        QScenePropertyChangePtr propertyChange = qSharedPointerCast<QScenePropertyChange>(e);

        if (propertyChange->propertyName() == QByteArrayLiteral("projectionMatrix")) {
            QMatrix4x4 projectionMatrix = propertyChange->value().value<QMatrix4x4>();
            m_projection = projectionMatrix;
        } else if (propertyChange->propertyName() == QByteArrayLiteral("enabled")) {
            m_enabled = propertyChange->value().toBool();
        }
    }
        break;

    default:
        break;
    }
}

} // Render
} // Qt3D

QT_END_NAMESPACE
