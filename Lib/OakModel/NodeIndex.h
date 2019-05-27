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

#include "Node.h"


namespace Oak::Model {

class NodeIndex;
typedef std::unique_ptr<NodeIndex> NodeIndexUPtr;

// =============================================================================
// Class definition
// =============================================================================
class NodeIndex
{
public:
    NodeIndex();
    NodeIndex(int index);
    NodeIndex(const std::string &name, int index);
    NodeIndex(const NodeIndex &nodeIndex);
    ~NodeIndex();

    bool isNull() const;
    bool isNamed(bool recursive = false) const;
    bool isUnnamed(bool recursive = false) const;

    bool equal(const NodeIndex &nodeIndex) const;
    int depthWhereEqual(const NodeIndex &nodeIndex) const;

    const std::string &name() const;
    int index() const;

    // Returns how many levels down the NodeIndex points
    int depth() const;

    bool contains(const NodeIndex &nodeIndex) const;

    Node node(const Node &rootNode, int depth = -1) const;
    Node nodeParent(const Node &rootNode) const;

    bool hasChildNodeIndex() const;

    const NodeIndex &childNodeIndex(int depth = 1) const;
    NodeIndex &childNodeIndex(int depth = 1);
    const NodeIndex &lastNodeIndex() const;
    NodeIndex &lastNodeIndex();

    static NodeIndex &emptyNodeIndex();

    static NodeIndexUPtr create(const Node &_node, bool namedIndex = true);

    // Manual creation of NodeIndex
    void setChildNodeIndex(NodeIndex *nodeIndex);

    // ************* Convert index to grouped of seperate format *************
    int convertIndexToUnnamed(const Node &_node) const;
    int convertIndexToNamed(const Node &_node, std::string &name) const;

    std::string toString() const;
    void toString(std::stringstream &ss) const;

protected:
    std::string m_name;
    int m_index;

    NodeIndex *m_childIndex;

    static NodeIndex s_nodeIndex;
};

} // namespace Oak::Model

