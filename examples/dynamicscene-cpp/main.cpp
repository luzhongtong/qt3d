/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
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

#include <QGuiApplication>

#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QCamera>
#include <Qt3DCore/Window>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRenderer/QRenderAspect>
#include <Qt3DRenderer/QFrameGraph>
#include <Qt3DRenderer/QForwardRenderer>

#include "forwardrenderer.h"
#include "examplescene.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    Qt3D::Window view;
    Qt3D::QAspectEngine engine;
    engine.registerAspect(new Qt3D::QRenderAspect());
    Qt3D::QInputAspect *input = new Qt3D::QInputAspect;
    engine.registerAspect(input);
    engine.initialize();
    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(&view)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(&view));
    engine.setData(data);

    ExampleScene *sceneRoot = new ExampleScene();

    // Scene Camera
    Qt3D::QCamera *basicCamera = new Qt3D::QCamera(sceneRoot);
    basicCamera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);
    basicCamera->setAspectRatio(view.width() / view.height());
    basicCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    basicCamera->setPosition(QVector3D(0.0f, 3.5f, 25.0f));
    // For camera controls
    input->setCamera(basicCamera);

    // Forward Renderer FrameGraph
    Qt3D::QFrameGraph *frameGraph = new Qt3D::QFrameGraph(sceneRoot);
    Qt3D::QForwardRenderer *forwardRenderer = new Qt3D::QForwardRenderer();
    forwardRenderer->setCamera(basicCamera);
    frameGraph->setActiveFrameGraph(forwardRenderer);
    sceneRoot->addComponent(frameGraph);

    engine.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
