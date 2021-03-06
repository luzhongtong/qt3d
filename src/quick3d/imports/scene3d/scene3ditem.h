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

#ifndef SCENE3DITEM_H
#define SCENE3DITEM_H

#include <QQuickFramebufferObject>

QT_BEGIN_NAMESPACE

namespace Qt3D
{
    class QAspectEngine;
    class QEntity;
    class QRenderAspect;
}

class Scene3DItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QEntity* entity READ entity WRITE setEntity NOTIFY entityChanged)
    Q_PROPERTY(QStringList aspects READ aspects WRITE setAspects NOTIFY aspectsChanged)
    Q_CLASSINFO("DefaultProperty", "entity")
public:
    explicit Scene3DItem(QQuickItem *parent = 0);
    ~Scene3DItem();

    QStringList aspects() const;
    Qt3D::QEntity *entity() const;

public Q_SLOTS:
    void setAspects(const QStringList &aspects);
    void setEntity(Qt3D::QEntity *entity);

Q_SIGNALS:
    void aspectsChanged();
    void entityChanged();

private Q_SLOTS:
    void applyRootEntityChange();

private:
    Renderer *createRenderer() const Q_DECL_OVERRIDE;
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData) Q_DECL_OVERRIDE;

    QStringList m_aspects;
    Qt3D::QEntity *m_entity;

    Qt3D::QAspectEngine *m_aspectEngine;
    Qt3D::QRenderAspect *m_renderAspect;
};

QT_END_NAMESPACE

#endif
