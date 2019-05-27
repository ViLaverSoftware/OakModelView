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

#include "QNodeDefBuilderData.h"

#include "../ServiceFunctions/Trace.h"

#include "NodeDefBuilderData.h"
#include "NodeDefBuilder.h"

// =============================================================================
// (public)
QNodeDefBuilderData::QNodeDefBuilderData(QObject *parent)
    : QObject(parent)
{
    //TRACE("Constructor: QuickNodeDef");
    m_builderOwner = std::make_unique<Oak::Model::NodeDefBuilderData>();
    m_builder = m_builderOwner.get();
}
