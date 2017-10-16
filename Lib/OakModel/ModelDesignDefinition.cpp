/**
 * oakmodelview - version 0.1.0
 * --------------------------------------------------------
 * Copyright (C) 2017, by Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * Report bugs and download new versions at http://oakmodelview.com/
 *
 * This library is distributed under the MIT License.
 * See accompanying file LICENSE in the root folder.
 */

#include "ModelDesignDefinition.h"

#include "NodeDefinitionBuilder.h"
#include "ContainerDefinitionBuilder.h"
#include "ValueDefinitionBuilder.h"

namespace Oak {
namespace Model {

// Node tag names
std::string DesignStr::Design = "Design";
std::string DesignStr::Node = "Node";
std::string DesignStr::Value = "Value";
std::string DesignStr::Container = "Container";

// Value tag and attribute names
std::string DesignStr::Name = "Name";
std::string DesignStr::Key = "Key";
std::string DesignStr::Type = "Type";

// =============================================================================
// (protected)
ModelDesignDefinition::ModelDesignDefinition()
    : NodeDefinition(DesignStr::Design)
{
    m_tagName = DesignStr::Design;
}

// =============================================================================
// (protected)
void ModelDesignDefinition::createModelDesign()
{
    auto NodeDef = NDB::Make(DesignStr::Node);
    NDB::addValueDefAsKey(NodeDef, VDB::MakeXML("", DesignStr::Name, "", "Noname"));

    auto NameTypeDef = VDB::MakeXML("", DesignStr::Name, "Type", "String");
    std::vector<std::string> optionsKyeTypes = {"String", "Number"};
    VDB::setOptions(NameTypeDef, optionsKyeTypes);
    NDB::addValueDef(NodeDef, std::move(NameTypeDef));

    NDB::addContainerDef(sPtr(), CDB::Make(NodeDef));

    auto ValueDef = NDB::Make(DesignStr::Value);
    NDB::addValueDefAsKey(ValueDef, VDB::MakeXML("", "", DesignStr::Name , "Noname"));
    NDB::addContainerDef(NodeDef, CDB::Make(ValueDef));


    auto ContainerDef = NDB::Make(DesignStr::Container);
    NDB::addValueDefAsKey(ContainerDef, VDB::MakeXML("", "", DesignStr::Name , "Noname"));
    NDB::addContainerDef(NodeDef, CDB::Make(ContainerDef));
}

// =============================================================================
// (public)
NodeDefSPtr ModelDesignDefinition::MakeSPtr()
{
    ModelDesignDefSPtr sPtr(new ModelDesignDefinition());
    sPtr->setWPtr(sPtr);
    sPtr->createModelDesign();
    return sPtr;
}

} // namespace Model
} // namespace Oak
