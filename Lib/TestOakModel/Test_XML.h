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

#ifdef XML_BACKEND

#include "Test_XMLDoc.h"
#include "Test_XMLReferences.h"
#include "Test_ValueDefinition.h"
#include "Test_NodeDefinition.h"
#include "Test_Item.h"
#include "Test_ItemQuery.h"

test_suite* Test_XML()
{
    test_suite* test = BOOST_TEST_SUITE( "XML" );

    test->add(Test_XMLDoc());
    test->add(Test_XMLReferences());
    test->add(Test_ValueDefinition());
    test->add(Test_NodeDefinition());
    test->add(Test_Item());
    test->add(Test_ItemQuery());

    return test;
}

#endif XML_BACKEND


