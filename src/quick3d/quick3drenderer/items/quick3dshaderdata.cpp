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

#include "quick3dshaderdata.h"
#include <private/qshaderdata_p.h>

#include <Qt3DQuickRenderer/quick3dshaderdataarray.h>
#include <QMetaProperty>

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

namespace {

const int qjsValueTypeId = qMetaTypeId<QJSValue>();
const int quick3DShaderDataArrayTypeId = qMetaTypeId<Quick3DShaderDataArray*>();
const int quick3DShaderDataTypeId = qMetaTypeId<Quick3DShaderData*>();

}

class Quick3DShaderDataPropertyReader : public PropertyReaderInterface
{
public:
    Quick3DShaderDataPropertyReader()
    {
    }

    QVariant readProperty(const QVariant &v) Q_DECL_OVERRIDE
    {
        // qjsValueTypeId are not compile time constant (no switch)
        if (v.userType() == qjsValueTypeId) {
            QJSValue jsValue = v.value<QJSValue>();
            if (jsValue.isArray())
                return v.value<QVariantList>();
            else if (jsValue.isVariant())
                return jsValue.toVariant();
        } else if (v.userType() == quick3DShaderDataArrayTypeId) {
            Quick3DShaderDataArray *array = v.value<Quick3DShaderDataArray *>();
            QVariantList innerValues;
            if (array) {
                Q_FOREACH (QShaderData *d, array->values()) {
                    if (d)
                        innerValues.append(QVariant::fromValue(d->id()));
                }
            }
            return innerValues;
        } else if (v.userType() == quick3DShaderDataTypeId) {
            QNodeId id;
            QShaderData *shaderData = v.value<Quick3DShaderData *>();
            if (shaderData)
                id = shaderData->id();
            return QVariant::fromValue(id);
        }
        return v;
    }
};

Quick3DShaderData::Quick3DShaderData(QNode *parent)
    : QShaderData(*new QShaderDataPrivate(this, PropertyReaderInterfacePtr(new Quick3DShaderDataPropertyReader()))
                  , parent)
{
}

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE
