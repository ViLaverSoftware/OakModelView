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

#include "XMLValueRef.h"

namespace Oak::XML {

// =============================================================================
// (public)
ValueRef::ValueRef(std::string attName, RefUPtr elRef)
    : m_attributeName(attName)
{
    if (elRef) {
        m_elementRef = std::move(elRef);
    } else {
        m_elementRef = Ref::MakeUPtr();
    }
}

// =============================================================================
// (public)
ValueRef::ValueRef(const ValueRef &copy)
{
    *this = copy;
}

// =============================================================================
// (public)
ValueRef::ValueRef(ValueRef &&move)
{
    *this = std::move(move);
}

// =============================================================================
// (public)
ValueRef& ValueRef::operator=(const ValueRef &copy)
{
    m_elementRef = copy.m_elementRef->copy();
    m_attributeName = copy.m_attributeName;
    return *this;
}

// =============================================================================
// (public)
ValueRef& ValueRef::operator=(ValueRef &&move)
{
    m_elementRef = std::move(move.m_elementRef);
    m_attributeName = std::move(move.m_attributeName);
    return *this;
}

// =============================================================================
// (public)
ValueRefUPtr ValueRef::copy() const
{
    return MakeUPtr(*this);
}

// =============================================================================
// (public)
bool ValueRef::hasValue(Element baseElement)
{
    baseElement = m_elementRef->getTarget(baseElement);
    if (baseElement.isNull()) { return false; }

    if (m_attributeName.empty()) {
        return baseElement.hasText();
    } else {
        return baseElement.hasAttribute(m_attributeName);
    }
}

// =============================================================================
// (public)
int ValueRef::compareValue(Element baseElement, const std::string& value) const
{
    baseElement = m_elementRef->getTarget(baseElement);
    if (baseElement.isNull()) { return -2; }

    if (m_attributeName.empty()) {
        return baseElement.compareText(value);
    } else {
        return baseElement.compareAttribute(m_attributeName, value);
    }
}

// =============================================================================
// (public)
void ValueRef::getValue(Element baseElement, std::string &value) const
{
    baseElement = m_elementRef->getTarget(baseElement);
    if (baseElement.isNull()) {
        value.clear();
        return;
    }

    if (m_attributeName.empty()) {
        baseElement.getText(value);
    } else {
        baseElement.getAttribute(m_attributeName, value);
    }
}

// =============================================================================
// (public)
bool ValueRef::setValue(Element baseElement, const std::string& value) const
{
    if (value.empty()) {
        return clearValue(baseElement);
    }

    baseElement = m_elementRef->getTarget(baseElement, true);
    if (baseElement.isNull()) { return false; }

    if (m_attributeName.empty()) {
        return baseElement.setText(value);
    } else {
        return baseElement.setAttribute(m_attributeName, value);
    }
}

// =============================================================================
// (public)
bool ValueRef::clearValue(Element baseElement) const
{
    Element refElement = m_elementRef->getTarget(baseElement, true);

    bool result = false;
    if (!refElement.isNull()) {
        if (m_attributeName.empty()) {
            result = refElement.removeText();
        } else {
            result = refElement.removeAttribute(m_attributeName);
        }
    }
    m_elementRef->clearTarget(baseElement);
    return result;
}

// =============================================================================
// (public)
void ValueRef::setAttributeName(std::string attName)
{
    m_attributeName = attName;
}

// =============================================================================
// (public)
void ValueRef::setElementRef(RefUPtr elRef)
{
    if (elRef) {
        m_elementRef = std::move(elRef);
    } else {
        m_elementRef = Ref::MakeUPtr();
    }
}

} // namespace Oak::XML

#endif // XML_BACKEND
