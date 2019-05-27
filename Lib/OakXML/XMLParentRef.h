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

namespace Oak::XML {

class ParentRef;
typedef std::unique_ptr<ParentRef> ParentRefUPtr;

//! \brief This class is a relative reference to a parent Element.
/*!
 * It is one of several ElementRef derivities that together makes it possible to refer any other Element in the XML::Document.
 * \sa ElementRefChild, ElementRefGroup
*/

// =============================================================================
// Class definition
// =============================================================================
class ParentRef : public Ref
{
public:
    ParentRef(std::string parentTagName = std::string());
    ParentRef(const ParentRef& copy);
    ParentRef(ParentRef &&move);

    ParentRef& operator=(const ParentRef& copy);
    ParentRef& operator=(ParentRef&& move);

    virtual RefUPtr copy() const override;
    ParentRefUPtr copyParent() const;

    /*!
     * The function takes a Element as argument and returns the referenced Element if possible.<br>
     * An empty Element is returned if the operation fails.<br>
     * On success a parent Element that matches m_parentTagName is returned. Parent elements are checked recursively.<br>
     * If m_parentTagName is empty the first parent Element is returned.
    */
    virtual Element getTarget(Element source, bool create = false) const override;

    virtual Element getSource(Element target) const override;

    virtual bool isNull() const override { return false; }

    virtual const std::string& firstTagName() const override { return emptyStr; }
    virtual const std::string& lastTagName() const override { return emptyStr; }

    template<class... _Types> inline
    static ParentRefUPtr MakeUPtr(_Types&&... _Args)
    {
        return (ParentRefUPtr(new ParentRef(_STD forward<_Types>(_Args)...)));
    }

protected:
    /*! \brief Name of the referenced tag */
    std::string m_parentTagName;
};

} // namespace Oak::XML

#endif // XML_BACKEND
