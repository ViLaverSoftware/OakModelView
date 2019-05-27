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
#include <QVariant>

#include "QValueOptionsBuilderData.h"
#include "QLeafSettingsBuilderData.h"

#include "Union.h"
#include "QPropertyHelpers.h"

#include "LeafDefBuilderData.h"

// =============================================================================
// Class definition
// =============================================================================
class QLeafDefBuilderData : public QObject
{
    Q_OBJECT
public:
    enum dataTypeEnum {
        Undefined = -1,
        Char = 0,
        Boolean = 1,
        Integer = 2,
        Double = 3,
        String = 4,
        DateTime = 5
    };
    Q_ENUM(dataTypeEnum)

private:
    BUILDER_PROPERTY_STRING(name)
    BUILDER_PROPERTY_STRING(displayName)
    BUILDER_PROPERTY_STRING(tooltip)
    BUILDER_PROPERTY_VARIANT(defaultValue)
    BUILDER_PROPERTY_ENUM(dataTypeEnum, Oak::Model::UnionType, dataType)
    BUILDER_PROPERTY_OBJECT(QLeafSettingsBuilderData, settings)
    BUILDER_PROPERTY_OBJECT(QValueOptionsBuilderData, options)

public:
    QLeafDefBuilderData(QObject* parent = nullptr);
    Oak::Model::LeafDefBuilderDataUPtr takeBuilder() { return std::move(m_builderOwner); }

private:
    Oak::Model::LeafDefBuilderData * m_builder;
    Oak::Model::LeafDefBuilderDataUPtr m_builderOwner;
};
