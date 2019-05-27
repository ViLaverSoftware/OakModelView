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

#ifdef XML_BACKEND

#include "XMLRefFactory.h"

#include "XMLChildRef.h"
#include "XMLParentRef.h"
#include "XMLRefGroup.h"
#include "XMLChildRefGroup.h"

#include "XMLListRef.h"

#include "XMLValueRef.h"
#include "XMLServiceFunctions.h"

#include "../ServiceFunctions/Assert.h"

#include <sstream>
#include <iostream>

namespace Oak::XML {

// =============================================================================
// (public)
ValueRefUPtr RefFactory::MakeValueRef(const std::string& elementRef, const std::string& attributeName)
{
    return ValueRef::MakeUPtr(attributeName, MakeRef(elementRef));
}

// =============================================================================
// (public)
RefUPtr RefFactory::MakeRef(const std::string &elementRef)
{
    RefGroupUPtr groupRef = MakeGroupRef(elementRef);
    if (groupRef->count() == 0) {
        return Ref::MakeUPtr();
    } else if (groupRef->count() == 1) {
        return groupRef->take(0);
    }
    return std::move(groupRef);
}

// =============================================================================
// (public)
RefGroupUPtr RefFactory::MakeGroupRef(const std::string &elementRef)
{
    std::vector<std::vector<std::string>> sMatrix = doubleSplit(elementRef);

    std::vector<RefUPtr> refList;
    for (const std::vector<std::string> &sList: sMatrix)
    {
        if (sList.empty()) { continue; }

        switch (sList.size()) {
        case 1: {
            refList.push_back(MakeSingle("c", sList.front()));
            break;
        }
        case 2: {
            refList.push_back(MakeSingle(sList[0], sList[1]));
            break;
        }
        case 3: {
            bool ok;
            int index = toInteger(sList[2], &ok);
            ASSERT(ok);
            refList.push_back(MakeSingle(sList[0], sList[1], index));
            break;
        }
        default:
            ASSERT(false);
        }
    }
    RefGroupUPtr refGroup = RefGroup::MakeUPtr();
    for (int i = 0; i < static_cast<int>(refList.size()); i++)
    {
        refGroup->add(std::move(refList[static_cast<vSize>(i)]));
    }
    return refGroup;
}

// =============================================================================
// (public)
ChildRefGroupUPtr RefFactory::MakeChildRef(const std::string &childRef)
{
    RefGroupUPtr groupRef = MakeGroupRef(childRef);
    ChildRefGroupUPtr childGroup = ChildRefGroup::MakeUPtr();
    for (int i = 0; i < groupRef->count(); i++)
    {
        childGroup->add(dynamic_unique_pointer_cast<ChildRef>(groupRef->take(i)));
    }

    return childGroup;
}

// =============================================================================
// (public)
RefUPtr RefFactory::MakeSingle(const std::string &refType, const std::string &refValue, int index)
{
    if (refType.empty() || refType.find("c") == 0) {
        return ChildRef::MakeUPtr(refValue, index);
    } else if (refType.find("p") == 0) {
        // refValue is the parent tagName. If empty the link is to the direct parent
        return ParentRef::MakeUPtr(refValue);
    } else {
        ASSERT(false);
        return Ref::MakeUPtr();
    }
}

} // namespace Oak::XML

#endif // XML_BACKEND
