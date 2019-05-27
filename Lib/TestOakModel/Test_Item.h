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

#include "Item.h"

#include "Test_ServiceFunctions.h"
#include "OakModel.h"

#ifdef XML_BACKEND

using namespace Oak::Model;

void test_Item()
{
    OakModel dataModel;
    dataModel.setRootNodeDefinition(createNodeDefinition());
    dataModel.loadXMLRootNode(std::string(RESOURCE_PATH)+"test_doc.xml");

    Item item_oakModel = dataModel.rootItem();

    BOOST_CHECK(item_oakModel.childCount() == 2);

    Item item_model = item_oakModel.firstChild(nodeId_model);

    int childCount = item_model.childCount();
    BOOST_CHECK(childCount == 5);

    BOOST_CHECK(item_model.canInsertChild(nodeId_nodeDef, childCount));

    item_model.insertChild(nodeId_nodeDef, childCount);

    BOOST_CHECK(item_model.childCount() == 6);

    BOOST_CHECK(item_model.removeChild(childCount));

    Item niItem = item_model.lastChild();

    std::vector<std::string> options;
    niItem.value("name").getOptions(options);

    BOOST_CHECK(!niItem.isNull());

    std::string name;
    BOOST_CHECK(niItem.value(valueId_name).getValue(name));

    BOOST_CHECK(name == "description");
}

test_suite* Test_Item()
{
    test_suite* test = BOOST_TEST_SUITE("Item");

    test->add(BOOST_TEST_CASE(&test_Item));

    return test;
}

#endif // XML_BACKEND

