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


#include "ContainerDef.h"

namespace Oak::Model {

class NodeDefBuilder;
typedef std::shared_ptr<NodeDefBuilder> NodeDefBuilderSPtr;

class ContainerDefBuilder;
typedef std::shared_ptr<ContainerDefBuilder> ContainerDefBuilderSPtr;
typedef std::weak_ptr<ContainerDefBuilder> ContainerDefBuilderWPtr;

// =============================================================================
// Class definition
// =============================================================================
class ContainerDefBuilder
{
protected:
    ContainerDefBuilder(NodeDefBuilderSPtr nodeDefBuilder, int minCount, int maxCount);
    ContainerDefBuilder(ContainerDef *containerDef);

public:
    static ContainerDefBuilderSPtr create(NodeDefBuilderSPtr nodeDefBuilder, int minCount = 0, int maxCount = std::numeric_limits<int>::max());
    static ContainerDefBuilderSPtr use(ContainerDef *containerDef);

public:
    ContainerDefUPtr get();
    const ContainerDef & containerDef() const;

    ContainerDefBuilderSPtr setNodeDefElement(NodeDefSPtr nodeDef);
    ContainerDefBuilderSPtr setNodeDefParent(NodeDefSPtr hostDef);

    ContainerDefBuilderSPtr setMinMaxCount(int minCount = 0, int maxCount = std::numeric_limits<int>::max());

#ifdef XML_BACKEND
    ContainerDefBuilderSPtr setElementListRef(XML::ListRef listRef);
#endif // XML_BACKEND

private:
    ContainerDefUPtr m_containerDefUPtr;
    ContainerDef * m_containerDef;

    ContainerDefBuilderWPtr m_thisWPtr;
};

typedef ContainerDefBuilder CDB;

} // namespace Oak::Model

