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

#include "NodeQueryParent.h"

#include "../ServiceFunctions/Trace.h"


namespace Oak::Model {

// =============================================================================
// (public)
NodeQueryParent::NodeQueryParent()
    : NodeQuery()
{

}

// =============================================================================
// (public)
NodeQueryParent::NodeQueryParent(const NodeQueryParent &copy)
    : NodeQuery(copy)
{

}

// =============================================================================
// (public)
NodeQueryParent::NodeQueryParent(NodeQueryParent &&move)
    : NodeQuery(move)
{

}

// =============================================================================
// (protected)
Node NodeQueryParent::first(const Node &refNode) const
{
    return refNode.parent();
}

// =============================================================================
// (protected)
Node NodeQueryParent::last(const Node &refNode) const
{
    return refNode.parent();
}

// =============================================================================
// (protected)
const NodeDef *NodeQueryParent::_nodeDef(const NodeDef *nDef) const
{
    // TODO: Node can have multiple parents! Fix this...
    ASSERT(nDef);
    ASSERT(nDef->parentContainerCount() == 1); // Do not work unleass there are only one parent container
    return nDef->parentContainer(0)->hostDef();
}

} // namespace Oak::Model

