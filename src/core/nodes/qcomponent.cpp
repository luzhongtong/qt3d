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

#include "qcomponent.h"
#include "qcomponent_p.h"
#include "qentity.h"
#include "qentity_p.h"

#include <Qt3DCore/qscenepropertychange.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {

QComponentPrivate::QComponentPrivate(QComponent *qq)
    : QNodePrivate(qq)
    , m_shareable(true)
    , m_enabled(true)
{
}

void QComponentPrivate::addEntity(QEntity *entity)
{
    m_entities.append(entity);

    // We notify only if we have a QChangeArbiter
    if (m_changeArbiter != Q_NULLPTR) {
        Q_Q(QComponent);
        QScenePropertyChangePtr e(new QScenePropertyChange(ComponentAdded, q));
        e->setPropertyName(QByteArrayLiteral("entity"));
        e->setValue(QVariant::fromValue(entity->id()));
        notifyObservers(e);
    }
}

void QComponentPrivate::removeEntity(QEntity *entity)
{
    // We notify only if we have a QChangeArbiter
    if (m_changeArbiter != Q_NULLPTR) {
        Q_Q(QComponent);
        QScenePropertyChangePtr e(new QScenePropertyChange(ComponentRemoved, q));
        e->setPropertyName(QByteArrayLiteral("entity"));
        e->setValue(QVariant::fromValue(entity->id()));
        notifyObservers(e);
    }

    m_entities.removeAll(entity);
}

/*!
    Constructs a new QComponent instance with \a parent as the parent.
    \note a QComponent should never be instanced directly,
    instance one of the subclasses instead.
 */
QComponent::QComponent(QNode *parent)
    : QNode(*new QComponentPrivate(this), parent)
{
}

QComponent::~QComponent()
{
    Q_FOREACH (QEntity *entity, entities()) {
        QEntityPrivate *entityPimpl = dynamic_cast<QEntityPrivate *>(QEntityPrivate::get(entity));
        if (entityPimpl)
            entityPimpl->m_components.removeAll(this);
    }
}

/*!
    \return whether the QComponent is shareable across entities or not.
 */
bool QComponent::shareable() const
{
    Q_D(const QComponent);
    return d->m_shareable;
}

/*!
    \returns whether the QComponent is enabled or not.
 */
bool QComponent::isEnabled() const
{
    Q_D(const QComponent);
    return d->m_enabled;
}

/*!
    Set the QComponent to enabled if \a enabled is true.
    By default a Qt3D::QComponent is always enabled.

    \note the interpretation of what enabled means is aspect-dependent. Even if
    enabled is set to false, some aspects may still consider the component in
    some manner. This is documented on a class by class basis.
 */
void QComponent::setEnabled(bool enabled)
{
    Q_D(QComponent);
    if (d->m_enabled != enabled) {
        d->m_enabled = enabled;
        emit enabledChanged();
    }
}

/*!
    The QComponent can be shared across several entities if \a shareable is true.
 */
void QComponent::setShareable(bool shareable)
{
    Q_D(QComponent);
    if (d->m_shareable != shareable) {
        d->m_shareable = shareable;
        emit shareableChanged();
    }
}

void QComponent::copy(const QNode *ref)
{
    QNode::copy(ref);
    const QComponent *comp = static_cast<const QComponent *>(ref);
    setEnabled(comp->isEnabled());
    setShareable(comp->shareable());
}

/*!
 * \return a QVector containing all the entities that reference this component.
 */
QVector<QEntity *> QComponent::entities() const
{
    Q_D(const QComponent);
    return d->m_entities;
}

QComponent::QComponent(QComponentPrivate &dd, QNode *parent)
    : QNode(dd, parent)
{
}

} // namespace Qt3D

QT_END_NAMESPACE
