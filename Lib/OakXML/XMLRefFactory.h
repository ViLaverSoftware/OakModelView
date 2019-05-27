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

#ifdef XML_BACKEND

#include <memory>
#include <string>

namespace Oak::XML {

class Ref;
typedef std::unique_ptr<Ref> RefUPtr;

class ValueRef;
typedef std::unique_ptr<ValueRef> ValueRefUPtr;

class RefGroup;
typedef std::unique_ptr<RefGroup> RefGroupUPtr;

class ChildRefGroup;
typedef std::unique_ptr<ChildRefGroup> ChildRefGroupUPtr;

// =============================================================================
// Class definition
// =============================================================================
class RefFactory
{
    RefFactory() = delete;
public:
    static ValueRefUPtr MakeValueRef(const std::string& elementRef = "", const std::string& attributeName = "");

    static RefUPtr MakeRef(const std::string& elementRef);

    static RefGroupUPtr MakeGroupRef(const std::string& elementRef);

    static ChildRefGroupUPtr MakeChildRef(const std::string& childRef);

    static RefUPtr MakeSingle(const std::string& refType = "c", const std::string& refValue = "", int index = 0);


};

} // namespace Oak::XML

#endif // XML_BACKEND
