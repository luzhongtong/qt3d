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

#include "quick3dtechniquefilter.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

Quick3DTechniqueFilter::Quick3DTechniqueFilter(QObject *parent)
    : QObject(parent)
{
}

QQmlListProperty<Qt3D::QAnnotation> Quick3DTechniqueFilter::requireList()
{
    return QQmlListProperty<Qt3D::QAnnotation>(this, 0,
                                       &Quick3DTechniqueFilter::appendRequire,
                                       &Quick3DTechniqueFilter::requiresCount,
                                       &Quick3DTechniqueFilter::requireAt,
                                       &Quick3DTechniqueFilter::clearRequires);
}

void Quick3DTechniqueFilter::appendRequire(QQmlListProperty<QAnnotation> *list, QAnnotation *criterion)
{
    Quick3DTechniqueFilter *filter = qobject_cast<Quick3DTechniqueFilter *>(list->object);
    if (filter) {
        criterion->setParent(filter->parentTechniqueFilter());
        filter->parentTechniqueFilter()->addRequirement(criterion);
    }
}

QAnnotation *Quick3DTechniqueFilter::requireAt(QQmlListProperty<QAnnotation> *list, int index)
{
    Quick3DTechniqueFilter *filter = qobject_cast<Quick3DTechniqueFilter *>(list->object);
    if (filter)
        return filter->parentTechniqueFilter()->criteria().at(index);
    return 0;
}

int Quick3DTechniqueFilter::requiresCount(QQmlListProperty<QAnnotation> *list)
{
    Quick3DTechniqueFilter *filter = qobject_cast<Quick3DTechniqueFilter *>(list->object);
    if (filter)
        return filter->parentTechniqueFilter()->criteria().size();
    return 0;
}

void Quick3DTechniqueFilter::clearRequires(QQmlListProperty<QAnnotation> *list)
{
    Quick3DTechniqueFilter *filter = qobject_cast<Quick3DTechniqueFilter *>(list->object);
    if (filter) {
        Q_FOREACH (QAnnotation *criterion, filter->parentTechniqueFilter()->criteria())
            filter->parentTechniqueFilter()->removeRequirement(criterion);
    }
}

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE
