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

#include "QueryBase.h"

#include "Test_ServiceFunctions.h"
#include "OakModel.h"

#ifdef XML_BACKEND

using namespace Oak::Model;

void test_ItemQuery()
{
    OakModel dataModel;
    dataModel.setRootNodeDefinition(createNodeDefinition());
    dataModel.loadXMLRootNode(std::string(RESOURCE_PATH)+"test_doc.xml");

    Item item_oakModel = dataModel.rootItem();

    BOOST_CHECK(item_oakModel.childCount() == 2);

    auto query = QueryBase::MakeSPtr(item_oakModel)->children("model")->children("nodeDefinition");
    BOOST_CHECK(query->count() == 5);

    std::vector<int> list = query->children("valueDefinition")->toList<int>("value");
    BOOST_CHECK(list.size() == 2);
    BOOST_CHECK(list[0] == 34);
    BOOST_CHECK(list[1] == -7);
}

test_suite* Test_ItemQuery()
{
    test_suite* test = BOOST_TEST_SUITE("ItemQuery");

    test->add(BOOST_TEST_CASE(&test_ItemQuery));

    return test;
}

#endif // XML_BACKEND
