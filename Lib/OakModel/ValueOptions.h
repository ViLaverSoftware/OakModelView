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

#include "UnionRef.h"
#include "UnionValue.h"

#include <algorithm>


namespace Oak::Model {

class Node;
class LeafQuery;
typedef std::shared_ptr<LeafQuery> LeafQuerySPtr;
typedef std::weak_ptr<LeafQuery> LeafQueryWPtr;

// =============================================================================
// Class definition
// =============================================================================
class ValueOptions
{
public:
    ValueOptions();
    ValueOptions(const ValueOptions &copy);

    bool isUsed() const;

    bool hasOption(const UnionRef& value, const Node *node, bool allowConversion = false, ConversionSPtr conversion = ConversionSPtr()) const;

    template<typename T>
    bool hasOption(const T& value, const Node *node, bool allowConversion = false, ConversionSPtr conversion = ConversionSPtr()) const;

    bool getOptions(std::vector<UnionValue>& options, const Node *node, bool allowConversion = false, ConversionSPtr conversion = ConversionSPtr()) const;

    template<typename T>
    bool getOptions(std::vector<T>& options, const Node *node, bool allowConversion = false, ConversionSPtr conversion = ConversionSPtr()) const;

    bool hasQuery() const;
    bool hasQueryExcluded() const;

    const LeafQuery *query() const;
    const LeafQuery *queryExcluded() const;

    static const ValueOptions& empty();

protected:
    std::vector<UnionValue> m_options;
    std::vector<UnionValue> m_excluded;

    LeafQuerySPtr m_query;
    LeafQuerySPtr m_queryExcluded;

    friend class LeafDef;
    friend class LeafDefBuilder;
};

// =============================================================================
// (public)
template<typename T>
bool ValueOptions::hasOption(const T& value, const Node* node, bool allowConversion, ConversionSPtr conversion) const
{
    UnionRef uRef(value);
    return hasOption(uRef, node, allowConversion, conversion);
}

// =============================================================================
// (public)
template<typename T>
bool ValueOptions::getOptions(std::vector<T>& options, const Node *node, bool allowConversion, ConversionSPtr conversion) const
{
    std::vector<UnionValue> oList;
    getOptions(oList, node, allowConversion, conversion);
    options.resize(oList.size());
    for (std::vector<UnionValue>::size_type i = 0; i < oList.size(); i++)
    {
        oList[i].get(options[i], allowConversion, conversion.get());
    }
    return true;
}

} // namespace Oak::Model

