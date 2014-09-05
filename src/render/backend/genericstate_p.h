/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#ifndef QT3D_RENDER_STATE_IMPLS_H
#define QT3D_RENDER_STATE_IMPLS_H

#include <QList>

#include <Qt3DRenderer/private/renderstate_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {
namespace Render {

template <typename Derived, typename T>
class GenericState1 : public RenderState
{
public:

    bool isEqual(const Derived& i) const
    { return (m_1 == i.m_1); }


protected:
    GenericState1(T t) :
        m_1(t)
    {}

    T m_1;

};

template <typename Derived, typename T, typename S>
class GenericState2 : public RenderState
{
public:
    bool isEqual(const Derived& i) const
    { return (m_1 == i.m_1) && (m_2 == i.m_2); }
protected:
    GenericState2(T t, S s) :
        m_1(t),
        m_2(s)
    {}


    T m_1;
    S m_2;
};

template <typename Derived, typename T, typename S, typename U>
class GenericState3 : public RenderState
{
public:
    bool isEqual(const Derived& i) const
    { return (m_1 == i.m_1) && (m_2 == i.m_2) && (m_3 == i.m_3); }

protected:
    GenericState3(T t, S s, U u) :
        m_1(t),
        m_2(s),
        m_3(u)
    {}

    T m_1;
    S m_2;
    U m_3;
};

template <typename Derived, typename T, typename S, typename U, typename Z>
class GenericState4 : public RenderState
{
public:
    bool isEqual(const Derived& i) const
    { return (m_1 == i.m_1) && (m_2 == i.m_2) && (m_3 == i.m_3) && (m_4 == i.m_4); }

protected:
    GenericState4(T t, S s, U u, Z z) :
        m_1(t),
        m_2(s),
        m_3(u),
        m_4(z)
    {}

    T m_1;
    S m_2;
    U m_3;
    Z m_4;
};

} // Render
} // Qt3D of namespace

QT_END_NAMESPACE

#endif // STATE_IMPLS_H