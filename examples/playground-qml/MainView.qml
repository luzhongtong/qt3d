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

import Qt3D 2.0
import Qt3D.Render 2.0
import QtQuick 2.0 as QQ2

Entity {

    property Entity camera: Camera {
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane: 0.01
        farPlane: 1000.0
        position: Qt.vector3d( 10.0, 10.0, -25.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 10.0 )
    }

    // Shareable Components

    Mesh {
        id: ballMesh
        objectName: "ballMesh"
        source: "assets/ball.obj"
    }

    Mesh {
        id: cubeMesh
        objectName: "cubeMesh"
        source: "assets/cube.obj"
    }

    AnimatedDiffuseMaterial {
        id: animatedMaterial
        texture: Texture2D { source : "assets/gltf/wine/Wood_Cherry_Original_.jpg" }
    }

    // Scene elements

    Entity {
        id : sceneEntity
        components : SceneLoader {
            id: scene
            source: ":/assets/test_scene.dae"
            objectName: "dae_scene"
        }
    }

    RenderableEntity {
        mesh: ballMesh
        material: animatedMaterial
        transform: Transform {
            Translate {
                dx: 0; dy: -10; dz : 25
                QQ2.SequentialAnimation on dz {
                    running : true
                    loops: QQ2.Animation.Infinite
                    QQ2.NumberAnimation { to : -1000; duration : 5000 }
                    QQ2.NumberAnimation { to : 1000; duration : 3000 }
                }
            }
            Scale {scale : 0.3}
        }
    }

    RenderableEntity {
        mesh: cubeMesh
        material: animatedMaterial
        transform: Transform {
            Translate {
                dx: 0; dy: -10; dz : 25
                QQ2.SequentialAnimation on dx {
                    running : true
                    loops: QQ2.Animation.Infinite
                    QQ2.NumberAnimation { to : -100; duration : 10000 }
                    QQ2.NumberAnimation { to : 100; duration : 5000 }
                }
            }
            Scale {scale : 0.3}
        }
    }
}
