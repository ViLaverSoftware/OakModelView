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

class QueryBuilder;
typedef std::shared_ptr<QueryBuilder> QueryBuilderSPtr;
typedef std::weak_ptr<QueryBuilder> QueryBuilderWPtr;

// =============================================================================
// Class definition
// =============================================================================
class QueryBuilder
{
public:
    QueryBuilder();
    NodeQueryUPtr UPtr();
    LeafQuerySPtr leafSPtr(const std::string &leafName);

    QueryBuilderSPtr children(const std::string &nodeName, bool invertOrder = false);
    QueryBuilderSPtr parent(bool invertOrder = false);
    QueryBuilderSPtr siblings(bool invertOrder = false);

    static QueryBuilderSPtr createChildren(const std::string &nodeName);
    static QueryBuilderSPtr createParent();
    static QueryBuilderSPtr createSiblings();

    static QueryBuilderSPtr createInverse(const NodeQuery &query, const NodeDef *sourceNodeDef);

    static LeafQuerySPtr createLeaf(const std::string &leafName);

    static NodeQueryUPtr duplicate(const NodeQueryUPtr &c);

    static NodeQueryUPtr createNodeQuery(const std::string& queryString);
    static LeafQuerySPtr createLeafQuery(const std::string& queryString);

protected:
    NodeQueryUPtr m_nodeQuery;
    QueryBuilderWPtr m_thisWPtr;
};

typedef QueryBuilder QB;

} // namespace Oak::Model

