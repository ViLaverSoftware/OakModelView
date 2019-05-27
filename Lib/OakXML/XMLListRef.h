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

#include <vector>
#include <memory>

#include "XMLChildRefGroup.h"

namespace Oak::XML {

class ListRef;
typedef std::unique_ptr<ListRef> ListRefUPtr;

// =============================================================================
// Class definition
// =============================================================================
class ListRef
{
public:
    ListRef(const std::string& tagName = std::string());
    ListRef(RefUPtr listBaseRef, const std::string& tagName, ChildRefGroupUPtr subRef = ChildRefGroup::MakeUPtr());
    ListRef(const ListRef &copy);
    ListRef(ListRef &&move);

    virtual ~ListRef();

    ListRef& operator=(const ListRef &copy);
    ListRef& operator=(ListRef&& move);

    ListRefUPtr copy() const;

    int count(Element refBase) const;
    int indexOf(Element refBase, Element refElement) const;
    Element at(Element refBase, int index) const;
    std::vector<Element> list(Element refBase) const;

    Element first(Element refBase) const;
    Element last(Element refBase) const;

    Element next(Element element) const;
    Element previous(Element element) const;

    Element insert(Element refBase, int index) const;
    Element insertBefore(Element refBase, Element refElement) const;
    Element insertAfter(Element refBase, Element refElement) const;

    Element clone(Element refBase, int index, Element cloneElement) const;
    Element cloneBefore(Element refBase, Element refElement, Element cloneElement) const;
    Element cloneAfter(Element refBase, Element refElement, Element cloneElement) const;

    Element move(Element refBase, int index, Element moveElement) const;
    Element moveBefore(Element refBase, Element refElement, Element moveElement) const;
    Element moveAfter(Element refBase, Element refElement, Element moveElement) const;

    bool remove(Element refBase, Element refElement) const;
    bool remove(Element refBase, int index) const;

    virtual Element invertedAt(Element refElement) const;

    const Ref& listBaseRef() const { return *m_listBaseRef.get(); }
    const std::string& tagName() const { return m_tagName; }
    const ChildRefGroup& subRef() const { return *m_subRef.get(); }

    void setListBaseRef(RefUPtr value);
    void setTagName(const std::string& value);
    void setSubRef(ChildRefGroupUPtr value);

    template<class... _Types> inline
    static ListRefUPtr MakeUPtr(_Types&&... _Args)
    {
        return (ListRefUPtr(new ListRef(_STD forward<_Types>(_Args)...)));
    }

protected:
    // The number of elements in a element reference list is the number of elements
    // with element tag name in in the list base ref element.
    // The ref element in each element can be a sub ref of the element
    RefUPtr m_listBaseRef;
    std::string m_tagName;
    ChildRefGroupUPtr m_subRef;
};

} // namespace Oak::XML

#endif // XML_BACKEND
