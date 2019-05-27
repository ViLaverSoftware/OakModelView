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

#include "NodeDefBuilderData.h"

#include "../ServiceFunctions/Trace.h"

#include "NodeDefBuilder.h"

namespace Oak::Model {

// =============================================================================
// (public)
NodeDefBuilderData::NodeDefBuilderData()
{
    //TRACE("NodeDefBuilderData");
}

// =============================================================================
// (public)
NodeDefBuilderData::~NodeDefBuilderData()
{

}

// =============================================================================
// (public)
void NodeDefBuilderData::validate(std::vector<std::string>& errorMessages) const
{
    //errorMessages.push_back("NodeDef validation not implemented");

    if (keyLeaf) {
        keyLeaf->validate(errorMessages);
    }

    if (variantLeaf) {
        variantLeaf->validate(errorMessages);
    }

    for (const auto& value: leafs) {
        value->validate(errorMessages);
    }

    for (const auto& container: containers) {
        container->validate(errorMessages);
    }

    for (const auto& nodeDef: derivedNodeDefs) {
        nodeDef->validateDerived(errorMessages);
    }
}

// =============================================================================
// (public)
void NodeDefBuilderData::validateDerived(std::vector<std::string>& errorMessages) const
{
    //errorMessages.push_back("Derived NodeDef validation not implemented");

    if (keyLeaf) {
        errorMessages.push_back("Derived NodeDef can not have a key value (It is inherited from it's base NodeDef)");
    }

    if (variantLeaf) {
        errorMessages.push_back("Derived NodeDef can not have a variant value (It is inherited from it's base NodeDef)");
    }

    if (variantId.empty()) {
        errorMessages.push_back("Derived NodeDef must have a variant id");
    }

    for (const auto& value: leafs) {
        value->validate(errorMessages);
    }

    for (const auto& container: containers) {
        container->validate(errorMessages);
    }

    for (const auto& nodeDef: derivedNodeDefs) {
        nodeDef->validateDerived(errorMessages);
    }
}

// =============================================================================
// (public)
NodeDefSPtr NodeDefBuilderData::create()
{
    bool isRoot = variantLeaf != nullptr;
    NodeDefBuilderSPtr builder;
    if (isRoot) {
        builder = NodeDefBuilder::createVariantRoot(name, variantId);
    } else {
        builder = NodeDefBuilder::create(name);
    }

    createShared(builder);

    for (const auto & derivedBuilder: derivedNodeDefs)
    {
        derivedBuilder->createVariant(builder);
    }

    return builder->get();
}

// =============================================================================
// (public)
bool NodeDefBuilderData::createVariant(NodeDefBuilderSPtr baseNodeDefBuilder) const
{
    NodeDefBuilderSPtr builder = NodeDefBuilder::createVariant(baseNodeDefBuilder, variantId);

    createShared(builder);

    for (const auto & derivedBuilder: derivedNodeDefs)
    {
        derivedBuilder->createVariant(builder);
    }

    return builder.get();
}

// =============================================================================
// (public)
bool NodeDefBuilderData::createContainers(NodeDefSPtr nodeDef, std::vector<NodeDefSPtr> nodeDefList) const
{
    NodeDefBuilderSPtr builder = NodeDefBuilder::use(nodeDef);

    bool success = true;
    for (const auto& container: containers) {
        if (!container->set(builder, nodeDefList)) {
            success = false;
        }
    }

    for (const auto& variantNodeDef: derivedNodeDefs) {
        NodeDefSPtr vnd = builder->getDerivedNodeDef(variantNodeDef->variantId);
        if (!vnd || vnd->isNull()) {
            success = false;
        } else if (!variantNodeDef->createContainers(vnd, nodeDefList)) {
            success = false;
        }
    }

    return success;
}

// =============================================================================
// (private)
void NodeDefBuilderData::createShared(NodeDefBuilderSPtr builder) const
{
    if (!displayName.empty()) {
        builder->setDisplayName(displayName);
    }

    if (!tooltip.empty()) {
        builder->setTooltip(tooltip);
    }

    if (color.isValid()) {
        builder->setColor(color);
    }

    if (!imagePath.empty()) {
        builder->setImagePath(imagePath);
    }

#ifdef XML_BACKEND
    if (!tagName.empty()) {
        builder->setTagName(tagName);
    }
#endif // XML_BACKEND

    if (keyLeaf) {
        builder->addKeyLeaf(keyLeaf->create());
    }

    if (variantLeaf) {
        builder->addVariantLeaf(variantLeaf->create());
    }

    for (const LeafDefBuilderDataUPtr& value: leafs) {
        builder->addLeafDef(value->create());
    }
}

} // namespace Oak::Model
