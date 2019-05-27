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

#include "LeafSettingsBuilderData.h"

#include "LeafDefBuilder.h"

#include "../ServiceFunctions/Trace.h"

namespace Oak::Model {

// =============================================================================
// (public)
LeafSettingsBuilderData::LeafSettingsBuilderData()
{
    //TRACE("LeafSettingsBuilderData");
}

// =============================================================================
// (public)
void LeafSettingsBuilderData::validate(std::vector<std::string>& errorMessages) const
{
    UNUSED(errorMessages)
    //errorMessages.push_back("LeafSettings validation not implemented");
}

// =============================================================================
// (public)
void LeafSettingsBuilderData::set(LeafDefBuilderSPtr builder) const
{
    if (optionsOnly != BoolState_Undefined) {
        builder->setSetting(OPTION_ONLY, optionsOnly == BoolState_True);
    }

    if (!unit.empty()) {
        builder->setSetting(UNIT, unit);
    }

    if (unique != BoolState_Undefined) {
        builder->setSetting(UNIQUE, unique);
    }

    if (required != BoolState_Undefined) {
        builder->setSetting(REQUIRED, required);
    }
}


} // namespace Oak::Model
