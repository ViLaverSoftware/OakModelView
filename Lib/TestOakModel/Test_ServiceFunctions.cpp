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

#include "Test_ServiceFunctions.h"

#include "NodeDefinitionBuilder.h"
#include "ContainerDefinitionBuilder.h"
#include "ValueDefinitionBuilder.h"

NodeDefSPtr createNodeDefinition()
{
    auto node_oakModel = NDB::Make(nodeId_oakModel);
    auto node_model = NDB::Make(nodeId_model);
    auto node_nodeDef = NDB::Make(nodeId_nodeDef);
    auto node_valueDef = NDB::Make(nodeId_valueDef);
    auto node_data = NDB::Make(nodeId_data);
    auto node_node = NDB::Make(nodeId_node);

    NDB::addContainerDef(node_oakModel, CDB::Make(node_model,1,1));
    NDB::addContainerDef(node_oakModel, CDB::Make(node_data,1,1));
    NDB::addContainerDef(node_model, CDB::Make(node_nodeDef));
    NDB::addContainerDef(node_nodeDef, CDB::Make(node_valueDef));

    NDB::addContainerDef(node_data, CDB::Make(node_node));


    NDB::addValueDefAsKey(node_nodeDef, VDB::MakeXML(std::string(), "", valueId_name));

    NDB::addValueDefAsKey(node_valueDef, VDB::MakeXML(std::string(), "", valueId_idName));
    NDB::addValueDefAsDerivedId(node_valueDef, VDB::MakeXML(std::string(), valueId_type));
    NDB::addValueDef(node_valueDef, VDB::MakeXML(0, valueId_value));

    return node_oakModel;
}
