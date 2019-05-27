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

#include "ValueOptions.h"

#include "UnionRef.h"
#include "LeafQuery.h"


namespace Oak::Model {

// =============================================================================
// (public)
ValueOptions::ValueOptions()
{

}

// =============================================================================
// (public)
ValueOptions::ValueOptions(const ValueOptions &copy)
{
    m_options.assign(copy.m_options.begin(), copy.m_options.end());
    m_excluded.assign(copy.m_excluded.begin(), copy.m_excluded.end());
}

// =============================================================================
// (public)
bool ValueOptions::isUsed() const
{
    return !m_options.empty() || m_query;
}

// =============================================================================
// (public)
bool ValueOptions::hasOption(const UnionRef& value, const Node* node, bool allowConversion, ConversionSPtr conversion) const
{
    UnionValueList options;
    // Todo: This function can be optimized
    if (!getOptions(options, node, allowConversion, conversion)) { return false; }

    return std::find(options.begin(), options.end(), value) != options.end();
}

// =============================================================================
// (public)
bool ValueOptions::getOptions(std::vector<UnionValue> &options, const Node *node, bool allowConversion, ConversionSPtr conversion) const
{
    options.resize(m_options.size());
    if (!isUsed()) { return false; }

    // Add static options
    for (std::vector<UnionValue>::size_type i = 0; i < m_options.size(); i++)
    {
        options[i] = m_options[i];
    }

    std::vector<UnionValue>::const_iterator it;
    if (node && m_query) {
        std::vector<UnionValue> oList = m_query->valueList(*node);
        for(const UnionValue &option: oList)
        {
            it = std::find(options.begin(), options.end(), option);
            if (it == options.end()) {
                options.push_back(option);
            }
        }
    }

    if (node && m_queryExcluded) {
        std::vector<UnionValue> oList = m_queryExcluded->valueList(*node);
        for(const UnionValue &option: oList)
        {
            it = std::find(options.begin(), options.end(), option);
            if (it != options.end()) {
                options.erase(it);
            }
        }
    }

    // Remove excluded options
    UnionValue option;
    for (const UnionValue& vo: m_excluded)
    {
        if (vo.get(option, allowConversion, conversion.get())) {
            it = std::find(options.begin(), options.end(), option);
            if (it != options.end()) {
                options.erase(it);
            }
        }

    }

    std::sort(options.begin(), options.end());

    return true;
}

// =============================================================================
// (public)
bool ValueOptions::hasQuery() const
{
    return m_query.operator bool();
}

// =============================================================================
// (public)
bool ValueOptions::hasQueryExcluded() const
{
    return m_queryExcluded.operator bool();
}

// =============================================================================
// (public)
const LeafQuery *ValueOptions::query() const
{
    return m_query.get();
}

// =============================================================================
// (public)
const LeafQuery *ValueOptions::queryExcluded() const
{
    return m_queryExcluded.get();
}

// =============================================================================
// (public)
const ValueOptions &ValueOptions::empty()
{
    static ValueOptions vo;
    return vo;
}

//// =============================================================================
//// (public)
//bool ValueOptions::getOptions(std::vector<VariantCRef>& options) const
//{
//    options.clear();
//    if (m_options.empty()) { return false; }

//    for (const auto& option: m_options) {
//        options.push_back(option);
//    }
//    return true;
//}

} // namespace Oak::Model

