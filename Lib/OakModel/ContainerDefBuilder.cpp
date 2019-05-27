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

#include "ContainerDefBuilder.h"
#include "NodeDefBuilder.h"

#include "NodeDef.h"

#include "../ServiceFunctions/Assert.h"


namespace Oak::Model {

// =============================================================================
// (protected)
ContainerDefBuilder::ContainerDefBuilder(NodeDefBuilderSPtr nodeDefBuilder, int minCount, int maxCount)
{
    ASSERT(nodeDefBuilder);
    ASSERT(minCount >= 0);
    ASSERT(maxCount > 0);
    ASSERT(maxCount >= minCount);

    m_containerDefUPtr = ContainerDef::MakeUPtr(nodeDefBuilder->get(), minCount, maxCount);
    m_containerDef = m_containerDefUPtr.get();

    nodeDefBuilder->get()->m_parentContainerDefs.push_back(m_containerDef);

#ifdef XML_BACKEND
    m_containerDef->m_elementListRef.setTagName(nodeDefBuilder->get()->tagName());
#endif // XML_BACKEND
}

// =============================================================================
// (protected)
ContainerDefBuilder::ContainerDefBuilder(ContainerDef *containerDef)
{
    ASSERT(containerDef);
    m_containerDef = containerDef;
}

// =============================================================================
// (public static)
ContainerDefBuilderSPtr ContainerDefBuilder::create(NodeDefBuilderSPtr nodeDefBuilder, int minCount, int maxCount)
{
    ContainerDefBuilderSPtr sPtr(new ContainerDefBuilder(nodeDefBuilder, minCount, maxCount));
    sPtr->m_thisWPtr = sPtr;
    return sPtr;
}

// =============================================================================
// (public static)
ContainerDefBuilderSPtr ContainerDefBuilder::use(ContainerDef *containerDef)
{
    ContainerDefBuilderSPtr sPtr(new ContainerDefBuilder(containerDef));
    sPtr->m_thisWPtr = sPtr;
    return sPtr;
}

// =============================================================================
// (public)
ContainerDefUPtr ContainerDefBuilder::get()
{
    ASSERT(m_containerDefUPtr);
    return std::move(m_containerDefUPtr);
}

// =============================================================================
// (public)
const ContainerDef &ContainerDefBuilder::containerDef() const
{
    ASSERT(m_containerDef);
    return *m_containerDef;
}

// =============================================================================
// (public)
ContainerDefBuilderSPtr ContainerDefBuilder::setNodeDefElement(NodeDefSPtr nodeDef)
{
    ASSERT(m_containerDef);
    ASSERT(nodeDef);

#ifdef XML_BACKEND
    // todo: Update m_elementListRef so that it refers to a alement with the same name as the new container definition
#endif // XML_BACKEND
    m_containerDef->m_containerDef = nodeDef;
    nodeDef->m_parentContainerDefs.push_back(m_containerDef);
    return m_thisWPtr.lock();
}

// =============================================================================
// (public)
ContainerDefBuilderSPtr ContainerDefBuilder::setNodeDefParent(NodeDefSPtr hostDef)
{
    ASSERT(m_containerDef);

    m_containerDef->m_hostDef = hostDef;
    return m_thisWPtr.lock();
}

// =============================================================================
// (public)
ContainerDefBuilderSPtr ContainerDefBuilder::setMinMaxCount(int minCount, int maxCount)
{
    ASSERT(m_containerDef);
    ASSERT(minCount >= 0 && maxCount >= minCount);

    m_containerDef->m_minCount = minCount;
    m_containerDef->m_maxCount = maxCount;

    return m_thisWPtr.lock();
}

#ifdef XML_BACKEND
// =============================================================================
// (public)
ContainerDefBuilderSPtr ContainerDefBuilder::setElementListRef(XML::ListRef listRef)
{
    ASSERT(m_containerDef);

    // todo: Validate listRef
    // It needs to reference a list of tags with the same tag name as the container node definition
    m_containerDef->m_elementListRef = listRef;
    return m_thisWPtr.lock();
}
#endif // XML_BACKEND

} // namespace Oak::Model

