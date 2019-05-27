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

#include "Color.h"

#include <string>
#include <memory>
#include <vector>

#include "LeafDefBuilderData.h"
#include "ContainerDefBuilderData.h"

#include "NodeDef.h"

namespace Oak::Model {

class NodeDefBuilderData;
typedef std::unique_ptr<NodeDefBuilderData> NodeDefBuilderDataUPtr;

class NodeDefBuilder;
typedef std::shared_ptr<NodeDefBuilder> NodeDefBuilderSPtr;

// =============================================================================
// Class definition
// =============================================================================
class NodeDefBuilderData
{
public:
    NodeDefBuilderData();
    virtual ~NodeDefBuilderData();

    void validate(std::vector<std::string> &errorMessages) const;
    void validateDerived(std::vector<std::string> &errorMessages) const;
    NodeDefSPtr create();
    bool createVariant(NodeDefBuilderSPtr baseNodeDefBuilder) const;

    bool createContainers(NodeDefSPtr nodeDef, std::vector<NodeDefSPtr> nodeDefList) const;

private:
    void createShared(NodeDefBuilderSPtr builder) const;

public:
    std::string name;
    std::string displayName;
    std::string tooltip;
    Color color;
    std::string imagePath;
    std::string variantId;

#ifdef XML_BACKEND
    std::string tagName;
#endif // XML_BACKEND

    LeafDefBuilderDataUPtr keyLeaf;
    LeafDefBuilderDataUPtr variantLeaf;

    std::vector<LeafDefBuilderDataUPtr> leafs;
    std::vector<ContainerDefBuilderDataUPtr> containers;
    std::vector<NodeDefBuilderDataUPtr> derivedNodeDefs;
};


typedef std::unique_ptr<NodeDefBuilderData> NodeDefBuilderDataUPtr;

} // namespace Oak::Model
