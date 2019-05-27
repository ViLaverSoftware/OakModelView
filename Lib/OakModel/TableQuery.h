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

#include "LeafQuery.h"


namespace Oak::Model {

class TableQuery;
typedef std::shared_ptr<TableQuery> TableQuerySPtr;
typedef std::weak_ptr<TableQuery> TableQueryWPtr;

// =============================================================================
// Class definition
// =============================================================================
class TableQuery
{
public:
    TableQuery();
    TableQuery(NodeQueryUPtr nodeQuery);

    void setNodeQuery(NodeQueryUPtr nodeQuery);

    int columnCount() const;
    void addValueQuery(LeafQuerySPtr valueQuery);

    int count(const Node &node) const;

    NodeQuery &nodeQuery();
    const NodeQuery &nodeQuery() const;

protected:
    NodeQueryUPtr m_nodeQuery;
    std::vector<LeafQuerySPtr> m_leafList; // Should be a valueRef (to be leafRef)

public:
    // Iterator navigation implementation
    class Iterator : public NodeQuery::Iterator {

    public:
        Iterator(const TableQuery &tableQuery, const Node *refNode = nullptr);

        virtual ~Iterator() override;

        const Leaf &leaf(int index) const;
        void getValue(int index, UnionValue value) const;

        template<typename T>
        T value(int index);

    protected:
        const TableQuery *m_tableQuery;
        std::vector<LeafQuery::Iterator*> m_leafIteratorList;

        friend class TableQuery;
    };
    typedef std::unique_ptr<Iterator> IteratorUPtr;

    IteratorUPtr iterator(const Node &refNode) const;
//    IteratorUPtr begin(const Node &refNode) const;
//    IteratorUPtr rBegin(const Node &refNode) const;
};

// =============================================================================
// (public)
template<typename T>
T TableQuery::Iterator::value(int index)
{
    const Leaf &e = leaf(index);
    if (e.isNull()) { T(); }
    return e.value<T>();
}

} // namespace Oak::Model


