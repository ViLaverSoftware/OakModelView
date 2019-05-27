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
#include <stdarg.h>
#include <memory>

#include "XMLRef.h"

namespace Oak::XML {

class RefGroup;
typedef std::unique_ptr<RefGroup> RefGroupUPtr;

// =============================================================================
// Class definition
// =============================================================================
class RefGroup : public Ref
{
public:
    RefGroup(RefUPtr eRef1 = RefUPtr(), RefUPtr eRef2 = RefUPtr(), RefUPtr eRef3 = RefUPtr(), RefUPtr eRef4 = RefUPtr());
    RefGroup(const RefGroup& copy);
    RefGroup(RefGroup &&move);

    RefGroup& operator=(const RefGroup& copy);
    RefGroup& operator=(RefGroup&& move);

    virtual RefUPtr copy() const override;
    RefGroupUPtr copyGroup() const;

    virtual Element getTarget(Element source, bool create = false) const override;
    virtual void clearTarget(Element source, bool onlyIfEmpty = true) const override;

    virtual Element getSource(Element target) const override;

    virtual bool isNull() const override { return false; }

    bool empty() const { return m_references.empty(); }
    int count() const { return static_cast<int>(m_references.size()); }
    Ref* at(int index) { return m_references[static_cast<vSize>(index)].get(); }
    template<typename T>
    T* at(int index) { return dynamic_cast<T*>(m_references.at(index).get()); }
    RefUPtr take(int index) { return std::move(m_references[static_cast<vSize>(index)]); }

    void add(RefUPtr eRef);
    void clear();

    virtual const std::string& firstTagName() const override { return m_references.front()->firstTagName(); }
    virtual const std::string& lastTagName() const override { return m_references.back()->lastTagName(); }

    template<class... _Types> inline
    static RefGroupUPtr MakeUPtr(_Types&&... _Args)
    {
        return (RefGroupUPtr(new RefGroup(_STD forward<_Types>(_Args)...)));
    }

protected:
    std::vector<RefUPtr> m_references;

};

} // namespace Oak::XML

#endif // XML_BACKEND
