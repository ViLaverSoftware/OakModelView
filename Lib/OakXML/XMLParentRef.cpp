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

#include "XMLParentRef.h"

namespace Oak::XML {

// =============================================================================
// (public)
ParentRef::ParentRef(std::string parentTagName)
    : Ref(),
      m_parentTagName(parentTagName)
{
}

// =============================================================================
// (public)
ParentRef::ParentRef(const ParentRef& copy)
    : Ref()
{
    *this = copy;
}

// =============================================================================
// (public)
ParentRef::ParentRef(ParentRef&& move)
    : Ref()
{
    *this = std::move(move);
}

// =============================================================================
// (public)
ParentRef& ParentRef::operator=(const ParentRef &copy)
{
    m_parentTagName = copy.m_parentTagName;
    return *this;
}

// =============================================================================
// (public)
ParentRef& ParentRef::operator=(ParentRef &&move)
{
    m_parentTagName = std::move(move.m_parentTagName);
    return *this;
}

// =============================================================================
// (public)
RefUPtr ParentRef::copy() const
{
    return MakeUPtr(*this);
}

// =============================================================================
// (public)
ParentRefUPtr ParentRef::copyParent() const
{
    return MakeUPtr(*this);
}

// =============================================================================
// (public)
Element ParentRef::getTarget(Element source, bool create) const
{
    UNUSED(create);
    if (source.isNull()) { return Element(); }

    Element refElement = source.parentElement();

    // Direct parent is returned if the parent tag name is empty
    if (m_parentTagName.empty()) { return refElement; }

    while (!refElement.isNull() && refElement.compareTagName(m_parentTagName) != 0) {
        refElement = refElement.parentElement();
    }

    return refElement;
}

// =============================================================================
// (public)
Element ParentRef::getSource(Element target) const
{
    UNUSED(target);
    // It can be any of the child elements so none is returned
    return Element();
}

} // namespace Oak::XML

#endif // XML_BACKEND
