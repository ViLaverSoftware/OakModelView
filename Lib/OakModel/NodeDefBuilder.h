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

#include "NodeDef.h"
#include "LeafDefBuilder.h"


namespace Oak::Model {

class ContainerDefBuilder;
typedef std::shared_ptr<ContainerDefBuilder> ContainerDefBuilderSPtr;

class NodeDefBuilder;
typedef std::shared_ptr<NodeDefBuilder> NodeDefBuilderSPtr;
typedef std::weak_ptr<NodeDefBuilder> NodeDefBuilderWPtr;

// =============================================================================
// Class definition
// =============================================================================
class NodeDefBuilder
{
protected:
    NodeDefBuilder(const std::string &name);
    NodeDefBuilder(const std::string &name, const UnionRef &variantId);
    NodeDefBuilder(NodeDefSPtr variantRoot, const UnionRef &variantId);
    NodeDefBuilder(NodeDefSPtr nodeDef);

public:
    static NodeDefBuilderSPtr create(const std::string &name);
    static NodeDefBuilderSPtr createVariantRoot(const std::string &name, const UnionRef &variantId);
    static NodeDefBuilderSPtr createVariant(NodeDefBuilderSPtr variantBase, const UnionRef &variantId);
    static NodeDefBuilderSPtr use(NodeDefSPtr nodeDef);

    NodeDefSPtr get();

    NodeDefBuilderSPtr addLeafDef(LeafDefBuilderSPtr leafDef);
    NodeDefBuilderSPtr addKeyLeaf(LeafDefBuilderSPtr keyLeafDef);
    NodeDefBuilderSPtr addVariantLeaf(LeafDefBuilderSPtr variantLeafDef);

    NodeDefBuilderSPtr addContainerDef(ContainerDefBuilderSPtr cDef);

    NodeDefBuilderSPtr setDisplayName(const std::string& displayName);

    NodeDefBuilderSPtr setTooltip(const std::string& tooltip);

    NodeDefBuilderSPtr setColor(int red, int green, int blue, int alpha = 255);
    NodeDefBuilderSPtr setColor(const Color& color);
    NodeDefBuilderSPtr setImagePath(const std::string &imagePath);

#ifdef XML_BACKEND
    NodeDefBuilderSPtr setTagName(const std::string& tagName);
#endif // XML_BACKEND

    NodeDefSPtr getDerivedNodeDef(const std::string &variantId);

    static LeafDefUPtr takeLeafDef(NodeDefSPtr nodeDef, const std::string &valueName);
    static ContainerDefUPtr takeContainerDef(NodeDefSPtr nodeDef, const std::string &name);

protected:
    // ************* SERVICE FUNCTIONS *************
    // Set the keyLeafDef or variantLeafDef on all variants in the inheritance heiracky
    static void setKeyLeafDefForAllVariants(NodeDefSPtr nodeDef, int index);
    static void setVariantLeafDefForAllVariants(NodeDefSPtr nodeDef, int index);

#ifdef XML_BACKEND
    static void setTagNameForAllVariants(NodeDefSPtr nodeDef, const std::string& tagName);
#endif // XML_BACKEND

private:
    NodeDefSPtr m_nodeDef;
    NodeDefBuilderWPtr m_thisWPtr;
};

typedef NodeDefBuilder NDB;

} // namespace Oak::Model

