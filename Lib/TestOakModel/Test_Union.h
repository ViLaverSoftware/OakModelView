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

#include "UnionValue.h"
#include "UnionRef.h"

using namespace Oak::Model;

void test_Union()
{
    std::cout << "Size of UnionValue: " << sizeof(UnionValue) << std::endl;
    std::cout << "Size of UnionRef:   " << sizeof(UnionRef)   << std::endl;

    const char *c = "Hallo World";
    bool b = true;
    int i = 32;
    double d = 3.21;
    std::string s = "Testing...";

    UnionValue uv;
    UnionValue uvc(c);
    UnionValue uvb(b);
    UnionValue uvi(i);
    UnionValue uvd(d);
    UnionValue uvs(s);

    BOOST_CHECK(uv.type() == UnionType::Undefined);

    BOOST_CHECK(uvc.type() == UnionType::String);
    BOOST_CHECK(uvc.getString() == c);

    BOOST_CHECK(uvb.type() == UnionType::Bool);
    BOOST_CHECK(uvb.getBool() == b);

    BOOST_CHECK(uvi.type() == UnionType::Integer);
    BOOST_CHECK(uvi.getInt() == i);

    BOOST_CHECK(uvd.type() == UnionType::Double);
    BOOST_CHECK(uvd.getDouble() == d);

    BOOST_CHECK(uvs.type() == UnionType::String);
    BOOST_CHECK(uvs.getString() == s);

    UnionRef ur;
    UnionRef urc(c);
    UnionRef urb(b);
    UnionRef uri(i);
    UnionRef urd(d);
    UnionRef urs(s);

    BOOST_CHECK(uri.canGet(urs));
    BOOST_CHECK(!urs.canGet(uri));

    BOOST_CHECK(uri.canGet(s));
    BOOST_CHECK(!urs.canGet(i));

    BOOST_CHECK(urd.canGet(uvc));
    BOOST_CHECK(!ur.canGet(uvb));

}

test_suite* Test_Union()
{
    test_suite* test = BOOST_TEST_SUITE("Union");

    test->add(BOOST_TEST_CASE(&test_Union));

    return test;
}
