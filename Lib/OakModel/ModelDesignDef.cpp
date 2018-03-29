/**
 * oakmodelview - version 0.1.0
 * --------------------------------------------------------
 * Copyright (C) 2017, by Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * Report bugs and download new versions at http://oakmodelview.com/
 *
 * This library is distributed under the MIT License.
 * See accompanying file LICENSE in the root folder.
 */

#include "ModelDesignDef.h"

#include "NodeDefBuilder.h"
#include "ContainerDefBuilder.h"
#include "ValueDefBuilder.h"
#include "QueryRef.h"
#include <memory>

namespace Oak {
namespace Model {

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
    auto NodeDef = NDB::createInheritanceRoot("Node", "Standard")
        ->setDisplayName("Node")
        ->addValueKey(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Noname"))
        ->addValueDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name")
            ->setTooltip("The name will be used if left empty"))
        ->addValueDef(VDB::create(UnionType::String, "KeyValue")
            ->setDisplayName("Key Value")
            ->setOptionsStatic(std::vector<std::string>{""})
            ->setOptionsQuery(QueryRef::MakeSPtr()->children("Value")->setValueName("Name"))
            ->setOptionsExcludedQuery(QueryRef::MakeSPtr()->setValueName("InheritanceIDValue"))
            ->setSetting("OptionsOnly", true))
        ->addValueInheritanceId(VDB::create(UnionType::String, "Type")
            ->setDisplayName("Node Type"));

    /************************** Node(InheritanceRoot) **************************/
    auto NodeRootDef = NDB::createInheritancDerived(NodeDef, "InheritanceRoot")
        ->addValueDef(VDB::create(UnionType::String, "NodeInheritanceId")
            ->setDisplayName("Root Inheritance ID"))
        ->addValueDef(VDB::create(UnionType::String, "InheritanceIDValue")
            ->setDisplayName("Value for Inheritance ID")
            ->setOptionsQuery(QueryRef::MakeSPtr()->children("Value")->setValueName("Name"))
            ->setOptionsExcludedQuery(QueryRef::MakeSPtr()->setValueName("KeyValue"))
            ->setSetting("OptionsOnly", true));

    /************************** Node(Rerived) **************************/
    auto NodeDerivedDef = NDB::createInheritancDerived(NodeDef, "Derived")
        ->addValueDef(VDB::create(UnionType::String, "NodeInheritanceId")
            ->setDisplayName("Derived Inheritance ID"))
        ->addValueDef(VDB::create(UnionType::String, "BaseNode")
            ->setDisplayName("Base Node"));

    /************************** Value(String) **************************/
    auto ValueDef = NDB::createInheritanceRoot("Value", "String")
        ->addValueKey(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Value"))
        ->addValueDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name"))
        ->addValueInheritanceId(VDB::create(UnionType::String, "Type"))
        ->addValueDef(VDB::create(UnionType::String, "Tooltip"));

    NodeDef->addContainerDef(CDB::Make(ValueDef->get()));

    /************************** Value(Integer) **************************/
    auto ValueDefInt = NDB::createInheritancDerived(ValueDef, "Integer")
        ->addValueDef(VDB::create(UnionType::Integer, "Min")
            ->setDefaultValue(-std::numeric_limits<int>::max()))
        ->addValueDef(VDB::create(UnionType::Integer, "Max")
            ->setDefaultValue(std::numeric_limits<int>::max()));

    /************************** Value(Double) **************************/
    auto ValueDefReal = NDB::createInheritancDerived(ValueDef, "Real")
        ->addValueDef(VDB::create(UnionType::Double, "Min")
            ->setDefaultValue(-std::numeric_limits<double>::max()))
        ->addValueDef(VDB::create(UnionType::Double, "Max")
            ->setDefaultValue(std::numeric_limits<double>::max()));

    /************************** Container **************************/
    auto ContainerDef = NDB::create("Container")
        ->addValueKey(VDB::create(UnionType::String, "Name")
            ->setDisplayName("Derived ID Value")
            ->setOptionsQuery(QueryRef::MakeSPtr()->parent()->parent()->children("Node")->setValueName("Name"))
            ->setOptionsExcludedQuery(QueryRef::MakeSPtr()->ignore()->parent()->children("Container")->setValueName("Name"))
            ->setSetting("OptionsOnly", true))
        ->addValueDef(VDB::create(UnionType::Integer, "Min")
            ->setDefaultValue(0))
        ->addValueDef(VDB::create(UnionType::Integer, "Max")
            ->setDefaultValue(std::numeric_limits<int>::max()));

    NodeDef->addContainerDef(CDB::Make(ContainerDef->get()));

    // Add the node definition to the Model design definition
    NDB::use(sPtr())->addContainerDef(CDB::Make(NodeDef->get()));
}

// =============================================================================
// (public)
NodeDefSPtr ModelDesignDef::MakeSPtr()
{
    ModelDesignDefSPtr sPtr(new ModelDesignDef());
    sPtr->setWPtr(sPtr);
    sPtr->createModelDesign();
    return sPtr;
}

} // namespace Model
} // namespace Oak
