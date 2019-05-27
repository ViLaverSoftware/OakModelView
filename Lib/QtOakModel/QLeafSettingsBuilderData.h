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
#include <QString>

#include "QOakBaseTypes.h"
#include "LeafSettingsBuilderData.h"

#include "QPropertyHelpers.h"


// =============================================================================
// Class definition
// =============================================================================
class QLeafSettingsBuilderData : public QObject
{
    Q_OBJECT
    BUILDER_PROPERTY_ENUM(QTriState::TriStateEnum, Oak::Model::BoolState, optionsOnly)
    BUILDER_PROPERTY_STRING(unit)
    BUILDER_PROPERTY_ENUM(QTriState::TriStateEnum, Oak::Model::BoolState, unique)
    BUILDER_PROPERTY_ENUM(QTriState::TriStateEnum, Oak::Model::BoolState, required)

public:
    QLeafSettingsBuilderData(QObject *parent = nullptr);
    Oak::Model::LeafSettingsBuilderDataUPtr takeBuilder() { return std::move(m_builderOwner); }

private:
    Oak::Model::LeafSettingsBuilderData * m_builder;
    Oak::Model::LeafSettingsBuilderDataUPtr m_builderOwner;
};
