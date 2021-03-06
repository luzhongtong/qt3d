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

#include <QGuiApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/Window>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QCamera>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRenderer/QRenderAspect>
#include <Qt3DRenderer/QPhongMaterial>
#include <Qt3DRenderer/QDiffuseMapMaterial>
#include <Qt3DRenderer/QForwardRenderer>
#include <Qt3DRenderer/QFrameGraph>

#include "planeentity.h"
#include "rotatingtrefoilknot.h"
#include "barrel.h"
#include "exampleresources.h"
#include "houseplant.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    initializeAssetResources("../exampleresources/example-assets.qrb");

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

    // Scene Root
    Qt3D::QEntity *sceneRoot = new Qt3D::QEntity();

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
    Qt3D::QFrameGraph *frameGraphComponent = new Qt3D::QFrameGraph(sceneRoot);
    Qt3D::QForwardRenderer *forwardRenderer = new Qt3D::QForwardRenderer();
    forwardRenderer->setCamera(basicCamera);
    frameGraphComponent->setActiveFrameGraph(forwardRenderer);
    sceneRoot->addComponent(frameGraphComponent);

    // Scene floor
    PlaneEntity *planeEntity = new PlaneEntity(sceneRoot);
    planeEntity->mesh()->setHeight(100.0f);
    planeEntity->mesh()->setWidth(100.0f);
    planeEntity->mesh()->setMeshResolution(QSize(20, 20));

    Qt3D::QNormalDiffuseSpecularMapMaterial *normalDiffuseSpecularMapMaterial = new Qt3D::QNormalDiffuseSpecularMapMaterial();
    normalDiffuseSpecularMapMaterial->setTextureScale(10.0f);
    normalDiffuseSpecularMapMaterial->setShininess(80.0f);
    normalDiffuseSpecularMapMaterial->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));

    QImage img;
    // Providing image loaders for textures would make sense
    if (img.load(QStringLiteral(":/assets/textures/pattern_09/diffuse.webp"))) {
        normalDiffuseSpecularMapMaterial->diffuse()->setFormat(img.hasAlphaChannel() ?
                                                                   Qt3D::QTexture::RGBA8_UNorm :
                                                                   Qt3D::QTexture::RGB8_UNorm);
        normalDiffuseSpecularMapMaterial->diffuse()->setFromQImage(img);
    }

    if (img.load(QStringLiteral(":/assets/textures/pattern_09/specular.webp"))) {
        normalDiffuseSpecularMapMaterial->specular()->setFormat(img.hasAlphaChannel() ?
                                                                    Qt3D::QTexture::RGBA8_UNorm :
                                                                    Qt3D::QTexture::RGB8_UNorm);
        normalDiffuseSpecularMapMaterial->specular()->setFromQImage(img);
    }

    if (img.load(QStringLiteral(":/assets/textures/pattern_09/normal.webp"))) {
        normalDiffuseSpecularMapMaterial->normal()->setFormat(img.hasAlphaChannel() ?
                                                                  Qt3D::QTexture::RGBA8_UNorm :
                                                                  Qt3D::QTexture::RGB8_UNorm);
        normalDiffuseSpecularMapMaterial->normal()->setFromQImage(img);
    }
    planeEntity->addComponent(normalDiffuseSpecularMapMaterial);

    // Chest
    RenderableEntity *chest = new RenderableEntity(sceneRoot);
    chest->scaleTransform()->setScale(0.03f);
    chest->mesh()->setSource(QUrl(QStringLiteral("qrc:/assets/chest/Chest.obj")));
    Qt3D::QDiffuseMapMaterial *diffuseMapMaterial = new Qt3D::QDiffuseMapMaterial();
    diffuseMapMaterial->setSpecular(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));
    diffuseMapMaterial->setShininess(2.0f);

    if (img.load(QStringLiteral(":/assets/chest/diffuse.webp"))) {
        diffuseMapMaterial->diffuse()->setFormat(img.hasAlphaChannel() ?
                                                     Qt3D::QTexture::RGBA8_UNorm :
                                                     Qt3D::QTexture::RGB8_UNorm);
        diffuseMapMaterial->diffuse()->setFromQImage(img);
    }
    chest->addComponent(diffuseMapMaterial);


    // TrefoilKnot
    RotatingTrefoilKnot *trefoil = new RotatingTrefoilKnot(sceneRoot);
    trefoil->translateTransform()->setDy(3.5);
    trefoil->scaleTransform()->setScale(0.5f);
    Qt3D::QPhongMaterial *phongMaterial = new Qt3D::QPhongMaterial();
    phongMaterial->setDiffuse(QColor(204, 205, 75)); // Safari Yellow #cccd4b
    phongMaterial->setSpecular(Qt::white);
    trefoil->addComponent(phongMaterial);

    // Barrels
    Barrel *basicBarrel = new Barrel(sceneRoot);
    basicBarrel->translateTransform()->setDx(8.0f);

    Barrel *rustyBarrel = new Barrel(sceneRoot);
    rustyBarrel->setDiffuse(Barrel::RustDiffuse);
    rustyBarrel->setSpecular(Barrel::RustSpecular);
    rustyBarrel->setBumps(Barrel::HardBumps);
    rustyBarrel->translateTransform()->setDx(10.0f);

    Barrel *blueBarrel = new Barrel(sceneRoot);
    blueBarrel->setDiffuse(Barrel::Blue);
    blueBarrel->setBumps(Barrel::MiddleBumps);
    blueBarrel->translateTransform()->setDx(12.0f);

    Barrel *greenBarrel = new Barrel(sceneRoot);
    greenBarrel->setDiffuse(Barrel::Green);
    greenBarrel->setBumps(Barrel::SoftBumps);
    greenBarrel->translateTransform()->setDx(14.0f);

    Barrel *stainlessBarrel = new Barrel(sceneRoot);
    stainlessBarrel->setDiffuse(Barrel::StainlessSteelDiffuse);
    stainlessBarrel->setBumps(Barrel::NoBumps);
    stainlessBarrel->setSpecular(Barrel::StainlessSteelSpecular);
    stainlessBarrel->setShininess(150.0f);
    stainlessBarrel->translateTransform()->setDx(16);

    // Plants
    HousePlant *squareBamboo = new HousePlant(sceneRoot);
    squareBamboo->setPotShape(HousePlant::Square);
    squareBamboo->setX(4.0f);

    HousePlant *trianglePalm = new HousePlant(sceneRoot);
    trianglePalm->setPlantType(HousePlant::Palm);
    trianglePalm->setPotShape(HousePlant::Triangle);
    trianglePalm->setZ(4.0f);

    HousePlant *spherePine = new HousePlant(sceneRoot);
    spherePine->setPlantType(HousePlant::Pine);
    spherePine->setPotShape(HousePlant::Sphere);
    spherePine->setX(-4.0f);

    HousePlant *crossSpikes = new HousePlant(sceneRoot);
    crossSpikes->setPlantType(HousePlant::Spikes);
    crossSpikes->setZ(-4.0f);

    HousePlant *crossPalm = new HousePlant(sceneRoot);
    crossPalm->setPlantType(HousePlant::Palm);
    crossPalm->setZ(-8.0f);
    crossPalm->setScale(0.05f);

    HousePlant *crossShrub = new HousePlant(sceneRoot);
    crossShrub->setPlantType(HousePlant::Shrub);
    crossShrub->setZ(8.0f);
    crossShrub->setScale(0.05f);

    engine.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
