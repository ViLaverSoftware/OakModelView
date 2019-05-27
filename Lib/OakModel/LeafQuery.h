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

#include "NodeQuery.h"


namespace Oak::Model {

class LeafQuery;
typedef std::shared_ptr<LeafQuery> LeafQuerySPtr;
typedef std::weak_ptr<LeafQuery> LeafQueryWPtr;

// =============================================================================
// Class definition
// =============================================================================
class LeafQuery
{
protected:
    LeafQuery(const std::string &leafName = "");
    LeafQuery(NodeQueryUPtr nodeQueryUPtr, const std::string &leafName = "");

public:
    ~LeafQuery();

    const std::string &valueName() const;
    LeafQuerySPtr setValueName(const std::string &leafName);

    int count(const Node &node);

    const Leaf &leaf(const Node &node, int index) const;

    void getValueList(const Node &node, std::vector<UnionValue> &valueList) const;
    std::vector<UnionValue> valueList(const Node &node) const;

    void getValue(const Node &node, int index, UnionValue value) const;


    template<typename T>
    T value(const Node &node, int index) const;

    template<typename T>
    std::vector<T> toValueList(const Node &node);

    std::vector<Node> toNodeList(const Node &node);

    const NodeQuery &nodeQuery() const;

    static LeafQuerySPtr create(const std::string &valueName = "");
    static LeafQuerySPtr create(NodeQueryUPtr nodeQueryUPtr, const std::string &leafName = "");

protected:
    std::string m_leafName;
    NodeQueryUPtr m_nodeQueryPtr = NodeQueryUPtr();

    LeafQueryWPtr m_thisWPtr;

public:
    // Iterator navigation implementation
    class Iterator : public NodeQuery::Iterator {

    public:
        Iterator(const LeafQuery &leafQuery, const Node *refNode = nullptr);

        virtual ~Iterator() override;

        void getValue(UnionValue value) const;

        template<typename T>
        T value() const;

        const Leaf &leaf() const;

    protected:
        const LeafQuery *m_leafQuery;

        friend class LeafQuery;
    };
    typedef std::unique_ptr<Iterator> IteratorUPtr;

    IteratorUPtr iterator(const Node &refNode) const;
//    IteratorUPtr begin(const Node &refNode) const;
//    IteratorUPtr rBegin(const Node &refNode) const;

    friend class Iterator;
};

// =============================================================================
// (public)
template<typename T>
T LeafQuery::value(const Node &node, int index) const
{
    assert(!m_leafName.empty());

    if (m_nodeQueryPtr) {

        int i = 0;
        auto it = m_nodeQueryPtr->iterator(node);
        while(it->next()) {
            if (i == index) {
                auto tempNode = it->node();
                if (tempNode.hasLeaf(m_leafName)) {
                    return node.leaf(m_leafName).value<T>();
                }
                return T();
            }
            i++;
        }
        assert(false);
    } else {
        assert(index == 0);
        if (node.hasLeaf(m_leafName)) {
            return node.leaf(m_leafName).value<T>();
        }
    }
    return T();
}

// =============================================================================
// (public)
template<typename T>
std::vector<T> LeafQuery::toValueList(const Node &node)
{
    assert(!m_leafName.empty());

    std::vector<T> valueList;
    if (m_nodeQueryPtr) {
        auto it = m_nodeQueryPtr->iterator(node);
        while (it->next()) {
            Node tempNode = it->node();
            if (tempNode.hasLeaf(m_leafName)) {
                valueList.push_back(tempNode.leaf(m_leafName).value<T>());
            }
        }
    } else {
        if (node.hasLeaf(m_leafName)) {
            valueList.push_back(node.leaf(m_leafName).value<T>());
        }
    }

    return valueList;
}

// =============================================================================
// (public)
template<typename T>
T LeafQuery::Iterator::value() const
{
    return leaf().value<T>();
}

} // namespace Oak::Model

