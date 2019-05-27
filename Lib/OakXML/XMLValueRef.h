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

#include "XMLRef.h"
#include <memory>

namespace Oak::XML {

class ValueRef;
typedef std::unique_ptr<ValueRef> ValueRefUPtr;

// =============================================================================
// Class definition
// =============================================================================
class ValueRef
{
public:
    ValueRef(std::string attName = std::string(), RefUPtr elRef = Ref::MakeUPtr());
    ValueRef(const ValueRef &copy);
    ValueRef(ValueRef &&move);

    ValueRef& operator=(const ValueRef &copy);
    ValueRef& operator=(ValueRef&& move);

    ValueRefUPtr copy() const;

    bool hasValue(Element baseElement);
    int compareValue(Element baseElement, const std::string& value) const;

    void getValue(Element baseElement, std::string& value) const;
    bool setValue(Element baseElement, const std::string& value) const;

    bool clearValue(Element baseElement) const;

    const std::string& attributeName() const { return m_attributeName; }
    void setAttributeName(std::string attName);

    Ref* elementRef() const { return m_elementRef.get(); }
    template<typename T>
    T* elementRef() const { return dynamic_cast<T*>(m_elementRef.get()); }

    void setElementRef(RefUPtr elRef);

    template<class... _Types> inline
    static ValueRefUPtr MakeUPtr(_Types&&... _Args)
    {
        return (ValueRefUPtr(new ValueRef(_STD forward<_Types>(_Args)...)));
    }

protected:

    RefUPtr m_elementRef;
    /*!
     * \brief Name of the attribute that contains the value.
     * If empty the value is stored as element text.
    */
    std::string m_attributeName;
};

} // namespace Oak::XML

#endif // XML_BACKEND
