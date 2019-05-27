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

#include <boost/test/included/unit_test.hpp>
using boost::unit_test_framework::test_suite;

#include <iostream>

#ifdef XML_BACKEND

#include "XMLDocument.h"
#include "XMLRefFactory.h"
#include "NodeDefinitionBuilder.h"
#include "ContainerDefinitionBuilder.h"
#include "ValueDefinitionBuilder.h"

#include "Test_ServiceFunctions.h"

using namespace Oak::Model;

void test_nodeDef()
{
    auto node_oakModel = createNodeDefinition();
    auto node_model = node_oakModel->container(nodeId_model).containerDefinition();
    auto node_nodeDef = node_model->container(nodeId_nodeDef).containerDefinition();
    auto node_data = node_oakModel->container(nodeId_data).containerDefinition();

    BOOST_CHECK(node_oakModel->containerCount() == 2);
    BOOST_CHECK(node_model->containerCount() == 1);
    BOOST_CHECK(node_data->containerCount() == 1);
    BOOST_CHECK(node_nodeDef->containerCount() == 1);

    XML::Document document1;
    BOOST_REQUIRE(document1.load(std::string(RESOURCE_PATH)+"test_doc.xml"));
    Node oakModelNode(document1.documentElement());

    BOOST_CHECK(node_oakModel->container(nodeId_model).nodeCount(oakModelNode) == 1);

    Node modelNode = node_oakModel->container(nodeId_model).node(oakModelNode, 0);
    auto tempNI = node_oakModel->container(nodeId_model).containerDefinition();

    BOOST_CHECK(modelNode.xmlNode().compareTagName(nodeId_model) == 0);
    BOOST_CHECK(tempNI->container(nodeId_nodeDef).nodeCount(modelNode) == 5);

    Node tempN = tempNI->container(0).node(modelNode, 0);
    tempNI = tempNI->container(0).containerDefinition();

    BOOST_CHECK(tempNI->valueCount() == 1);
    const ValueDefinition& tempVDef = tempNI->value(std::string("name"));

    UnionValue tempV = tempVDef.value(tempN);

    BOOST_CHECK(!tempV.isNull());

    BOOST_CHECK(tempV == std::string("root"));

    std::string tempStr = tempVDef.value(tempN).getCString();

    BOOST_CHECK(tempV == tempStr);
}


test_suite* Test_NodeDefinition()
{
    test_suite* test = BOOST_TEST_SUITE( "nodeDefinition" );

    test->add(BOOST_TEST_CASE(&test_nodeDef));

    return test;
}

#endif XML_BACKEND
