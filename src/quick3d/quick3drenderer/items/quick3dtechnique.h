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

#ifndef QT3D_RENDER_QUICK_QUICK3DTECHNIQUE_H
#define QT3D_RENDER_QUICK_QUICK3DTECHNIQUE_H

#include <Qt3DQuickRenderer/qt3dquickrenderer_global.h>
#include <Qt3DRenderer/qtechnique.h>
#include <QQmlListProperty>

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

class QT3DQUICKRENDERERSHARED_EXPORT Quick3DTechnique : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Qt3D::QAnnotation> annotations READ annotationList)
    Q_PROPERTY(QQmlListProperty<Qt3D::QRenderPass> renderPasses READ renderPassList)
    Q_PROPERTY(QQmlListProperty<Qt3D::QParameter> parameters READ parameterList)
public:
    explicit Quick3DTechnique(QObject *parent = 0);

    QQmlListProperty<Qt3D::QAnnotation> annotationList();
    QQmlListProperty<Qt3D::QRenderPass> renderPassList();
    QQmlListProperty<Qt3D::QParameter> parameterList();

    // Use QAbstractTechnique when it has been properly defined
    inline QTechnique *parentTechnique() const { return qobject_cast<QTechnique*>(parent()); }

private:

    static void appendParameter(QQmlListProperty<QParameter> *list, QParameter *param);
    static QParameter *parameterAt(QQmlListProperty<QParameter> *list, int index);
    static int parametersCount(QQmlListProperty<QParameter> *list);
    static void clearParameterList(QQmlListProperty<QParameter> *list);

    static void appendAnnotation(QQmlListProperty<QAnnotation> *list, QAnnotation *Annotation);
    static QAnnotation *annotationAt(QQmlListProperty<QAnnotation> *list, int index);
    static int annotationCount(QQmlListProperty<QAnnotation> *list);
    static void clearAnnotationList(QQmlListProperty<QAnnotation> *list);

    static void appendRenderPass(QQmlListProperty<QRenderPass> *list, QRenderPass* renderPass);
    static QRenderPass *renderPassAt(QQmlListProperty<QRenderPass> *list, int index);
    static int renderPassCount(QQmlListProperty<QRenderPass> *list);
    static void clearRenderPasses( QQmlListProperty<QRenderPass> *list);
};

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE

#endif // QUICK3DTECHNIQUE_H
