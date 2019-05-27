/*
 * OakModelView (http://oakmodelview.com/)
 * Author: Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <QObject>
#include <QtQuick/QQuickItem>
#include <QColor>

#include "QContainerDefBuilderData.h"
#include "QLeafDefBuilderData.h"
#include "QPropertyHelpers.h"

#include "NodeDefBuilderData.h"

// =============================================================================
// Class definition
// =============================================================================
class QNodeDefBuilderData : public QObject
{
    Q_OBJECT
    BUILDER_PROPERTY_STRING(name)
    BUILDER_PROPERTY_STRING(displayName)
    BUILDER_PROPERTY_STRING(tooltip)
    BUILDER_PROPERTY_COLOR(color)
    BUILDER_PROPERTY_STRING(imagePath)
    BUILDER_PROPERTY_STRING(variantId)
    BUILDER_PROPERTY_STRING(tagName)
    BUILDER_PROPERTY_OBJECT(QLeafDefBuilderData, keyLeaf)
    BUILDER_PROPERTY_OBJECT(QLeafDefBuilderData, variantLeaf)
    BUILDER_PROPERTY_OBJECT_LIST(QNodeDefBuilderData, QLeafDefBuilderData, leafs, leaf)
    BUILDER_PROPERTY_OBJECT_LIST(QNodeDefBuilderData, QContainerDefBuilderData, containers, container)
    BUILDER_PROPERTY_OBJECT_LIST(QNodeDefBuilderData, QNodeDefBuilderData, derivedNodeDefs, derivedNodeDef)

public:
    QNodeDefBuilderData(QObject *parent = nullptr);
    Oak::Model::NodeDefBuilderDataUPtr takeBuilder() { return std::move(m_builderOwner); }

private:
    Oak::Model::NodeDefBuilderData * m_builder;
    Oak::Model::NodeDefBuilderDataUPtr m_builderOwner;
};
