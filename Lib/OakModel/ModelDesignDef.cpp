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

#include "ModelDesignDef.h"

#include "NodeDefBuilder.h"
#include "ContainerDefBuilder.h"
#include "LeafDefBuilder.h"
#include "LeafQuery.h"
#include <memory>

#include "QueryBuilder.h"


namespace Oak::Model {

// =============================================================================
// (protected)
ModelDesignDef::ModelDesignDef()
    : NodeDef("Design")
{
    m_tagName = "Design";
}

// =============================================================================
// (protected)
void ModelDesignDef::createModelDesign()
{
    /************************** Node(Standard) **************************/
    auto NodeDef = NDB::createVariantRoot("Node", "Standard")
        ->setDisplayName("Node")
        ->addKeyLeaf(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Noname"))
        ->addLeafDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name")
            ->setTooltip("The name will be used if left empty"))
        ->addLeafDef(VDB::create(UnionType::String, "KeyValue")
            ->setDisplayName("Key Value")
            ->setOptionsQuery(QB::createChildren("Value")->leafSPtr("Name"))
            ->setOptionsExcludedQuery(LeafQuery::create()->setValueName("InheritanceIDValue"))
            ->setSetting("OptionsOnly", true))
        ->addVariantLeaf(VDB::create(UnionType::String, "Type")
            ->setDisplayName("Node Type"));

    /************************** Node(InheritanceRoot) **************************/
    auto NodeRootDef = NDB::createVariant(NodeDef, "InheritanceRoot")
        ->addLeafDef(VDB::create(UnionType::String, "NodeInheritanceId")
            ->setDisplayName("Root Inheritance ID"))
        ->addLeafDef(VDB::create(UnionType::String, "InheritanceIDValue")
            ->setDisplayName("Value for Inheritance ID")
            ->setOptionsQuery(QB::createChildren("Value")->leafSPtr("Name"))
            ->setOptionsExcludedQuery(LeafQuery::create()->setValueName("KeyValue"))
            ->setSetting("OptionsOnly", true));

    /************************** Node(Rerived) **************************/
    auto NodeVariantDef = NDB::createVariant(NodeDef, "Variant")
        ->addLeafDef(VDB::create(UnionType::String, "VariantId")
            ->setDisplayName("Variant ID"))
        ->addLeafDef(VDB::create(UnionType::String, "Base")
            ->setDisplayName("Base Node"));

    /************************** Value(String) **************************/
    auto LeafDef = NDB::createVariantRoot("Leaf", "String")
        ->addKeyLeaf(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Leaf"))
        ->addLeafDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name"))
        ->addVariantLeaf(VDB::create(UnionType::String, "Type"))
        ->addLeafDef(VDB::create(UnionType::String, "Tooltip"));

    NodeDef->addContainerDef(CDB::create(LeafDef));

    /************************** Value(Integer) **************************/
    auto LeafDefInt = NDB::createVariant(LeafDef, "Integer")
        ->addLeafDef(VDB::create(UnionType::Integer, "Min")
            ->setDefaultValue(-std::numeric_limits<int>::max()))
        ->addLeafDef(VDB::create(UnionType::Integer, "Max")
            ->setDefaultValue(std::numeric_limits<int>::max()));

    /************************** Value(Double) **************************/
    auto LeafDefReal = NDB::createVariant(LeafDef, "Real")
        ->addLeafDef(VDB::create(UnionType::Double, "Min")
            ->setDefaultValue(-std::numeric_limits<double>::max()))
        ->addLeafDef(VDB::create(UnionType::Double, "Max")
            ->setDefaultValue(std::numeric_limits<double>::max()));

    /************************** Container **************************/
    auto ContainerDef = NDB::create("Container")
        ->addKeyLeaf(VDB::create(UnionType::String, "Name")
            ->setDisplayName("Container Node Name")
            ->setOptionsQuery(QB::createParent()->createSiblings()->leafSPtr("Name"))
            ->setSetting("OptionsOnly", true))
        ->addLeafDef(VDB::create(UnionType::Integer, "Min")
            ->setDefaultValue(0))
        ->addLeafDef(VDB::create(UnionType::Integer, "Max")
            ->setDefaultValue(std::numeric_limits<int>::max()));

    NodeDef->addContainerDef(CDB::create(ContainerDef));

    // Add the node definition to the Model design definition
    NDB::use(m_thisWPtr.lock())->addContainerDef(CDB::create(NodeDef));
}

// =============================================================================
// (public)
NodeDefSPtr ModelDesignDef::MakeSPtr()
{
    ModelDesignDefSPtr sPtr(new ModelDesignDef());
    sPtr->m_thisWPtr = sPtr;
    //sPtr->setWPtr(sPtr);
    sPtr->createModelDesign();
    return sPtr;
}

} // namespace Oak::Model

