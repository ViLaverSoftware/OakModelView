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

// Assertion severity level
// 1. warn
// 2. check
// 3. require

#include "Test_XML.h"
//#include "Test_Variant.h"
#include "Test_Union.h"

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    UNUSED(argc);
    UNUSED(argv);
    test_suite* test = BOOST_TEST_SUITE( "Master test suite" );

    test->add(Test_Union());
#ifdef XML_BACKEND
    test->add(Test_XML());
#endif

    return test;
}
