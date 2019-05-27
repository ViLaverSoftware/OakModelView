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

#include "LeafDefBuilderData.h"

#include "LeafDefBuilder.h"

#include "../ServiceFunctions/Trace.h"

namespace Oak::Model {

// =============================================================================
// (public)
LeafDefBuilderData::LeafDefBuilderData()
{
    //TRACE("LeafDefBuilderData");
}

// =============================================================================
// (public)
void LeafDefBuilderData::validate(std::vector<std::string>& errorMessages) const
{
    //errorMessages.push_back("LeafDef validation not implemented");

    if (name.empty()) {
        errorMessages.push_back("LeafDef have to have a name");
    }

    if (dataType == UnionType::Undefined) {
        errorMessages.push_back("LeafDef dataType have to be defined");
    } else if (dataType == UnionType::Char) {
        errorMessages.push_back("LeafDef dataType Char is not supported use String");
    }

    if (settings) {
        settings->validate(errorMessages);
    }

    if (options) {
        options->validate(errorMessages);
    }
}

// =============================================================================
// (public)
LeafDefBuilderSPtr LeafDefBuilderData::create() const
{
    UnionType type = (dataType == UnionType::Undefined) ? UnionType::String : dataType;
    LeafDefBuilderSPtr builder = LeafDefBuilder::create(type, name);
    if (!displayName.empty()) {
        builder->setDisplayName(displayName);
    }
    if (!defaultValue.isNull()) {
        builder->setDefaultValue(defaultValue);
    }
    if (!tooltip.empty()) {
        builder->setTooltip(tooltip);
    }


    if (settings) {
        settings->set(builder);
    }
    if (options) {
        options->set(builder);
    }
    return builder;
}


} // namespace Oak::Model
