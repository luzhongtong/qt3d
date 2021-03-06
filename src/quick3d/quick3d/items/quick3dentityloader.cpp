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

#include "quick3dentityloader.h"
#include "quick3dentityloader_p.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlIncubator>

#include <QtQml/private/qqmlengine_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Quick {

class Quick3DEntityLoaderIncubator : public QQmlIncubator
{
public:
    Quick3DEntityLoaderIncubator(Quick3DEntityLoaderPrivate *loader)
        : QQmlIncubator(Asynchronous),
          m_loader(loader)
    {
    }

protected:
    void setInitialState(QObject *object) Q_DECL_OVERRIDE
    {
        Q_ASSERT(m_loader->m_entity == Q_NULLPTR);
        m_loader->m_entity = qobject_cast<QEntity*>(object);
        Q_ASSERT(m_loader->m_entity != Q_NULLPTR);
        m_loader->m_entity->setParent(m_loader->q_ptr);

        Quick3DEntityLoader *loader = static_cast<Quick3DEntityLoader*>(m_loader->q_ptr);
        emit loader->entityChanged();
    }

private:
    Quick3DEntityLoaderPrivate *m_loader;
};

Quick3DEntityLoader::Quick3DEntityLoader(QNode *parent)
    : QEntity(*new Quick3DEntityLoaderPrivate(this), parent)
{
}

QObject *Quick3DEntityLoader::entity() const
{
    Q_D(const Quick3DEntityLoader);
    return d->m_entity;
}

QUrl Quick3DEntityLoader::source() const
{
    Q_D(const Quick3DEntityLoader);
    return d->m_source;
}

void Quick3DEntityLoader::setSource(const QUrl &url)
{
    Q_D(Quick3DEntityLoader);

    if (url == d->m_source)
        return;

    d->clear();
    d->m_source = url;
    emit sourceChanged();
    d->loadFromSource();
}

void Quick3DEntityLoader::copy(const QNode *ref)
{
    QNode::copy(ref);
    const Quick3DEntityLoader *loader = static_cast<const Quick3DEntityLoader*>(ref);
    d_func()->m_source = loader->d_func()->m_source;
    d_func()->m_entity = static_cast<QEntity*>(QNode::clone(loader->d_func()->m_entity));
    d_func()->m_entity->setParent(this);
}

Quick3DEntityLoaderPrivate::Quick3DEntityLoaderPrivate(Quick3DEntityLoader *qq)
    : QEntityPrivate(qq),
      m_incubator(Q_NULLPTR),
      m_context(Q_NULLPTR),
      m_component(Q_NULLPTR),
      m_entity(Q_NULLPTR)
{
}

void Quick3DEntityLoaderPrivate::clear()
{
    if (m_incubator) {
        m_incubator->clear();
        delete m_incubator;
        m_incubator = Q_NULLPTR;
    }

    if (m_entity) {
        m_entity->setParent(Q_NULLPTR);
        delete m_entity;
        m_entity = Q_NULLPTR;
    }

    if (m_component) {
        delete m_component;
        m_component = Q_NULLPTR;
    }

    if (m_context) {
        delete m_context;
        m_context = Q_NULLPTR;
    }
}

void Quick3DEntityLoaderPrivate::loadFromSource()
{
    Q_Q(Quick3DEntityLoader);

    if (m_source.isEmpty()) {
        emit q->entityChanged();
        return;
    }

    loadComponent(m_source);
}

void Quick3DEntityLoaderPrivate::loadComponent(const QUrl &source)
{
    Q_Q(Quick3DEntityLoader);

    Q_ASSERT(m_entity == Q_NULLPTR);
    Q_ASSERT(m_component == Q_NULLPTR);
    Q_ASSERT(m_context == Q_NULLPTR);

    m_component = new QQmlComponent(qmlEngine(q), q);
    QObject::connect(m_component, SIGNAL(statusChanged(QQmlComponent::Status)),
                     q, SLOT(_q_componentStatusChanged(QQmlComponent::Status)));
    m_component->loadUrl(source, QQmlComponent::Asynchronous);
}

void Quick3DEntityLoaderPrivate::_q_componentStatusChanged(QQmlComponent::Status status)
{
    Q_Q(Quick3DEntityLoader);

    Q_ASSERT(m_entity == Q_NULLPTR);
    Q_ASSERT(m_component != Q_NULLPTR);
    Q_ASSERT(m_context == Q_NULLPTR);
    Q_ASSERT(m_incubator == Q_NULLPTR);

    if (!m_component->errors().isEmpty()) {
        QQmlEnginePrivate::warning(qmlEngine(q), m_component->errors());
        clear();
        emit q->entityChanged();
        return;
    }

    // Still loading
    if (status != QQmlComponent::Ready)
        return;

    m_context = new QQmlContext(qmlContext(q));
    m_context->setContextObject(q);

    m_incubator = new Quick3DEntityLoaderIncubator(this);
    m_component->create(*m_incubator, m_context);
}

} // Quick

} // Qt3D

QT_END_NAMESPACE

#include "moc_quick3dentityloader.cpp"
