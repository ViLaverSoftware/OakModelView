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
#include <memory>

#include "QServiceFunctions.h"
#include "QNodeDefBuilderData.h"

#include "ModelBuilderData.h"
#include "QPropertyHelpers.h"

namespace Oak::Model {
    class NodeDef;
    typedef std::shared_ptr<NodeDef> NodeDefSPtr;
}

// =============================================================================
// Class definition
// =============================================================================
class QOakModelBuilderData : public QObject
{
    Q_OBJECT

public:
    enum StatusEnum {
        INITIAL = 0,
        SUCCESS = 1,
        FAILED = 2
    };
    Q_ENUM(StatusEnum)

private:
    BUILDER_PROPERTY_OBJECT_LIST(QOakModelBuilderData, QNodeDefBuilderData, nodeDefs, nodeDef)
    BUILDER_PROPERTY_STRING_LIST(errorMessages)

public:
    QOakModelBuilderData(QObject *parent = nullptr);
    Oak::Model::ModelBuilderDataUPtr takeBuilder() { return std::move(m_builderOwner); }

    bool validate();
    Oak::Model::NodeDefSPtr create();

private:
    Oak::Model::ModelBuilderData * m_builder;
    Oak::Model::ModelBuilderDataUPtr m_builderOwner;
};
