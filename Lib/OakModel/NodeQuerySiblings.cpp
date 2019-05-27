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

#include "NodeQuerySiblings.h"

#include "../ServiceFunctions/Trace.h"


namespace Oak::Model {

// =============================================================================
// (public)
NodeQuerySiblings::NodeQuerySiblings()
{
}

// =============================================================================
// (public)
NodeQuerySiblings::NodeQuerySiblings(const NodeQuerySiblings &copy)
    : NodeQuery(copy)
{
}

// =============================================================================
// (public)
NodeQuerySiblings::NodeQuerySiblings(NodeQuerySiblings &&move)
    : NodeQuery(move)
{
}

// =============================================================================
// (protected)
Node NodeQuerySiblings::first(const Node &refNode) const
{
    m_parent = refNode.parent();
    Node sibling = m_parent.firstChild(refNode.def()->name());

    if (refNode == sibling) {
        // Skip self
        return next(refNode, sibling);
    } else {
        return sibling;
    }
}

// =============================================================================
// (protected)
Node NodeQuerySiblings::last(const Node &refNode) const
{
    m_parent = refNode.parent();
    Node sibling = m_parent.lastChild(refNode.def()->name());

    if (refNode == sibling) {
        // Skip self
        return previous(refNode, sibling);
    } else {
        return sibling;
    }
}

// =============================================================================
// (protected)
Node NodeQuerySiblings::next(const Node &refNode, const Node &cNode) const
{
    Node sibling = m_parent.nextChild(refNode.def()->name(), cNode);

    if (refNode == sibling) {
        // Skip self
        return next(refNode, sibling);
    } else {
        return sibling;
    }
}

// =============================================================================
// (protected)
Node NodeQuerySiblings::previous(const Node &refNode, const Node &cNode) const
{
    Node sibling = m_parent.previousChild(refNode.def()->name(), cNode);

    if (refNode == sibling) {
        // Skip self
        return previous(refNode, sibling);
    } else {
        return sibling;
    }
}

// =============================================================================
// (protected)
const NodeDef *NodeQuerySiblings::_nodeDef(const NodeDef *nDef) const
{
    // TODO: Node can have multiple parents! Fix this...
    ASSERT(nDef);
    ASSERT(nDef->parentContainerCount() == 1); // Do not work unleass there are only one parent container

    // Return the container variant base class
    return nDef->parentContainer(0)->containerDef();
}

} // namespace Oak::Model

