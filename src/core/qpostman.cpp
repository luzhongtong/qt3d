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

#include "qpostman_p.h"
#include <private/qobject_p.h>
#include <Qt3DCore/qscenepropertychange.h>
#include <Qt3DCore/qbackendscenepropertychange.h>
#include <Qt3DCore/qscene.h>
#include <Qt3DCore/qnode.h>
#include <Qt3DCore/private/qnode_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class QPostmanPrivate : public QObjectPrivate
{
public:
    QPostmanPrivate(QPostman *qq)
        : QObjectPrivate()
        , m_scene(Q_NULLPTR)
    {
        q_ptr = qq;
    }

    Q_DECLARE_PUBLIC(QPostman)
    QSceneInterface *m_scene;
};

QPostman::QPostman(QObject *parent)
    : QObject(*new QPostmanPrivate(this), parent)
{
    qRegisterMetaType<QSceneChangePtr >("QSceneChangePtr");
}

void QPostman::setScene(QSceneInterface *scene)
{
    Q_D(QPostman);
    d->m_scene = scene;
}

static inline QMetaMethod notifyFrontendNodeMethod()
{
    int idx = QPostman::staticMetaObject.indexOfMethod("notifyFrontendNode(QSceneChangePtr)");
    Q_ASSERT(idx != -1);
    return QPostman::staticMetaObject.method(idx);
}

void QPostman::sceneChangeEvent(const QSceneChangePtr &e)
{
    static const QMetaMethod notifyFrontendNode = notifyFrontendNodeMethod();
    notifyFrontendNode.invoke(this, Q_ARG(QSceneChangePtr, e));
}

void QPostman::notifyFrontendNode(const QSceneChangePtr &e)
{
    Q_D(QPostman);
    QBackendScenePropertyChangePtr change = qSharedPointerDynamicCast<QBackendScenePropertyChange>(e);
    if (!change.isNull() && d->m_scene != Q_NULLPTR) {
        QNode *n = d->m_scene->lookupNode(change->targetNode());
        if (n != Q_NULLPTR)
            n->sceneChangeEvent(change);
    }
}

} //Qt3D

QT_END_NAMESPACE
