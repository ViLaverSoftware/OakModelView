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

#include "ContainerDefBuilderData.h"

#include "NodeDefBuilderData.h"
#include "NodeDefBuilder.h"
#include "ContainerDefBuilder.h"

#include "../ServiceFunctions/Trace.h"

namespace Oak::Model {

// =============================================================================
// (public)
ContainerDefBuilderData::ContainerDefBuilderData()
{
    //TRACE("ContainerDefBuilderData");
}

// =============================================================================
// (public)
void ContainerDefBuilderData::validate(std::vector<std::string>& errorMessages) const
{
    //errorMessages.push_back("ContainerDef validation not implemented");

    if (name.empty()) {
        errorMessages.push_back("ContainerDef's have to have a NodeDef reference");
    }

    if (minCount < 0) {
        errorMessages.push_back("ContainerDef's minimum count have to be greater than or equal to 0");
    }

    if (maxCount == 0) {
        errorMessages.push_back("ContainerDef's maximum count have to be greater than 0");
    } else if (maxCount < minCount) {
        errorMessages.push_back("ContainerDef's maximum count have to be greater than or equal to minimum count");
    }
}

// =============================================================================
// (public)
bool ContainerDefBuilderData::set(NodeDefBuilderSPtr builder, std::vector<NodeDefSPtr> nodeDefList) const
{
    NodeDef* containerNodeDef = nullptr;
    for (auto nDef: nodeDefList) {
        if (nDef->name() == name) {
            containerNodeDef = const_cast<NodeDef*>(nDef->validVariant(variantId)); // Const cast is allowed here
        }
    }
    if (containerNodeDef == nullptr) { return false; }

    auto containerNodeBuilder = NodeDefBuilder::use(containerNodeDef->sPtr());
    auto containerBuilder = ContainerDefBuilder::create(containerNodeBuilder, minCount, maxCount);
    builder->addContainerDef(containerBuilder);
    return true;
}

} // namespace Oak::Model
