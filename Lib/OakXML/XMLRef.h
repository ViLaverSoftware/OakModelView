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

#include "XMLElement.h"

#include <memory>

namespace Oak::XML {

class Ref;
typedef std::unique_ptr<Ref> RefUPtr;

// =============================================================================
// Class definition
// =============================================================================
class Ref
{
public:
// TODO: Make copy and move constructors for all ElementRef's
    Ref() {}
    Ref(const Ref&) {}
    Ref(Ref&&) {}

    virtual ~Ref() {}

    Ref& operator=(const Ref&) { return *this; }
    Ref& operator=(Ref&&) { return *this; }

    virtual RefUPtr copy() const;

    virtual Element getTarget(Element source, bool create = false) const;
    virtual void clearTarget(Element source, bool onlyIfEmpty = true) const;
    bool hasTarget(Element source) const;

    virtual Element getSource(Element target) const;

    virtual bool isNull() const { return true; }

    virtual const std::string& firstTagName() const { return emptyStr; }
    virtual const std::string& lastTagName() const { return emptyStr; }

    template<class... _Types> inline
    static RefUPtr MakeUPtr(_Types&&... _Args)
    {
        return (RefUPtr(new Ref(_STD forward<_Types>(_Args)...)));
    }

protected:
    static std::string emptyStr;
};

} // namespace Oak::XML

#endif // XML_BACKEND
