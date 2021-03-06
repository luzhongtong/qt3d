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

#include "meshdatamanager_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {
namespace Render {

// Called by aspect thread when RenderMesh receive a new functor in syncChanges
void MeshDataManager::addMeshData(QAbstractMeshFunctorPtr functor, const QNodeId &meshUuid)
{
    m_meshesPending[meshUuid] = functor;
}

// Called by single thread in QRenderAspect
// Needs to be protected as we ways call it while addMeshData is called
QHash<QNodeId, QAbstractMeshFunctorPtr> MeshDataManager::meshesPending()
{
    QHash<QNodeId, QAbstractMeshFunctorPtr> meshFunctors = m_meshesPending;
    m_meshesPending.clear();
    return meshFunctors;
}

HMeshData MeshDataManager::meshDataFromFunctor(QAbstractMeshFunctorPtr functor) const
{
    Q_FOREACH (const QAbstractMeshFunctorPtr &ptr, m_meshFunctors.keys()) {
        if (*ptr == *functor)
            return m_meshFunctors.value(ptr);
    }
    return HMeshData();
}

void MeshDataManager::addMeshDataForFunctor(HMeshData meshDataHandle, QAbstractMeshFunctorPtr functor)
{
    m_meshFunctors.insert(functor, meshDataHandle);
}

} // namespace Render
} // namespace Qt3D

QT_END_NAMESPACE
