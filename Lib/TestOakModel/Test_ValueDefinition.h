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

#include "XMLDocument.h"
#include "XMLRefFactory.h"

#include "ValueDefinitionBuilder.h"

using namespace Oak::Model;

void test_valueDefinition()
{
    XML::Document document1;
    BOOST_REQUIRE(document1.load(std::string(RESOURCE_PATH)+"test_doc.xml"));
    XML::Element docElement = document1.documentElement();

    XML::ChildRefGroupUPtr childGroupRef = XML::RefFactory::MakeChildRef("model;nodeDefinition;valueDefinition");

    XML::Element tempElement = childGroupRef->getTarget(docElement);

    BOOST_CHECK(tempElement.compareTagName("valueDefinition") == 0);

    ValueDefUPtr vDef = VDB::MakeXML(1, "value");

    int value;
    vDef->getValue(tempElement, value);
    BOOST_CHECK(value == 34);

    double dVal;
    vDef->getValue(tempElement, dVal, true, true);
    BOOST_CHECK(dVal == 34.0);

    BOOST_CHECK(vDef->setValue(tempElement, -7.3241, true));

    std::string sVal;
    vDef->getValue(tempElement, sVal);
    BOOST_CHECK(sVal == "-7");

    BOOST_CHECK(vDef->setValue(tempElement, std::string("Fail"), true) == false);
}


test_suite* Test_ValueDefinition()
{
    test_suite* test = BOOST_TEST_SUITE( "valueDefinition" );

    test->add(BOOST_TEST_CASE(&test_valueDefinition));

    return test;
}

#endif XML_BACKEND
