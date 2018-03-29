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
    auto NodeDef = NDB::createRoot("Node", "Standard")
        ->setDisplayName("Node")
        ->addValueDefAsKey(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Noname"))
        ->addValueDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name"))
        ->addValueDef(VDB::create(UnionType::String, "KeyValue")
            ->setDisplayName("Key Value")
            ->setOptionsStatic(std::vector<std::string>{""})
            ->setOptionsQuery(QueryRef::MakeSPtr()->children("Value")->setValueName("Name"))
            ->setOptionsExcludedQuery(QueryRef::MakeSPtr()->setValueName("DerivedIDValue"))
            ->setSetting("OptionsOnly", true))
        ->addValueDefAsDerivedId(VDB::create(UnionType::String, "Type")
            ->setDisplayName("Node Type"));

    /************************** Node(DerivedRoot) **************************/
    auto NodeRootDef = NDB::createDerived(NodeDef, "DerivedRoot")
        ->addValueDef(VDB::create(UnionType::String, "DerivedId")
            ->setDisplayName("Derived ID"))
        ->addValueDef(VDB::create(UnionType::String, "DerivedIDValue")
            ->setDisplayName("Derived ID Value")
            ->setOptionsQuery(QueryRef::MakeSPtr()->children("Value")->setValueName("Name"))
            ->setOptionsExcludedQuery(QueryRef::MakeSPtr()->setValueName("KeyValue"))
            ->setSetting("OptionsOnly", true));

    /************************** Node(Rerived) **************************/
    auto NodeDerivedDef = NDB::createDerived(NodeDef, "Derived")
        ->addValueDef(VDB::create(UnionType::String, "DerivedBase")
            ->setDisplayName("Derived Base"));

    /************************** Value(String) **************************/
    auto ValueDef = NDB::createRoot("Value", "String")
        ->addValueDefAsKey(VDB::create(UnionType::String, "Name")
            ->setDefaultValue("Value"))
        ->addValueDef(VDB::create(UnionType::String, "DisplayName")
            ->setDisplayName("Display Name"))
        ->addValueDefAsDerivedId(VDB::create(UnionType::String, "Type"))
        ->addValueDef(VDB::create(UnionType::String, "Tooltip"));


    NodeDef->addContainerDef(CDB::Make(ValueDef->get()));

    /************************** Value(Integer) **************************/
    auto ValueDefInt = NDB::createDerived(ValueDef, "Integer")
        ->addValueDef(VDB::create(UnionType::Integer, "Min")
            ->setDefaultValue(-std::numeric_limits<int>::max()))
        ->addValueDef(VDB::create(UnionType::Integer, "Max")
            ->setDefaultValue(std::numeric_limits<int>::max()));

    /************************** Value(Double) **************************/
    auto ValueDefReal = NDB::createDerived(ValueDef, "Real")
        ->addValueDef(VDB::create(UnionType::Double, "Min")
            ->setDefaultValue(-std::numeric_limits<double>::max()))
        ->addValueDef(VDB::create(UnionType::Double, "Max")
            ->setDefaultValue(std::numeric_limits<double>::max()));

    /************************** Container **************************/
    auto ContainerDef = NDB::create("Container")
        ->addValueDefAsKey(VDB::create(UnionType::String, "Name")
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
