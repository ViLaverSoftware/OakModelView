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

#include "LeafSettingsBuilderData.h"
#include "ValueOptionsBuilderData.h"

namespace Oak::Model {

class LeafDefBuilder;
typedef std::shared_ptr<LeafDefBuilder> LeafDefBuilderSPtr;

// =============================================================================
// Class definition
// =============================================================================
class LeafDefBuilderData
{
public:
    LeafDefBuilderData();
    virtual ~LeafDefBuilderData() {}

    void validate(std::vector<std::string> &errorMessages) const;
    LeafDefBuilderSPtr create() const;

    std::string name;
    std::string displayName;
    std::string tooltip;
    UnionValue defaultValue;
    UnionType dataType = UnionType::Undefined;
    LeafSettingsBuilderDataUPtr settings;
    ValueOptionsBuilderDataUPtr options;
};

typedef std::unique_ptr<LeafDefBuilderData> LeafDefBuilderDataUPtr;

} // namespace Oak::Model
