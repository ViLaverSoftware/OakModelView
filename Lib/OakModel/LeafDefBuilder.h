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

#include "LeafDef.h"
#include "XMLRefFactory.h"
#include "XMLValueRef.h"
#include "ValueOptions.h"


namespace Oak::Model {

class LeafDefBuilder;
typedef std::shared_ptr<LeafDefBuilder> LeafDefBuilderSPtr;
typedef std::weak_ptr<LeafDefBuilder> LeafDefBuilderWPtr;

// =============================================================================
// Class definition
// =============================================================================
class LeafDefBuilder
{
protected:
    LeafDefBuilder(UnionType type, const std::string &name);
    LeafDefBuilder(LeafDef *leafDef);

public:
    static LeafDefBuilderSPtr create(UnionType type, const std::string &name);
    static LeafDefBuilderSPtr use(LeafDef *leafDef);

    LeafDefBuilderSPtr setName(const std::string &value);
    LeafDefBuilderSPtr setDisplayName(const std::string &value);
    LeafDefBuilderSPtr setTooltip(const std::string &value);


    LeafDefBuilderSPtr setDefaultValue(const UnionRef &value);

    LeafDefBuilderSPtr setDefaultConversion(ConversionSPtr value);

    LeafDefBuilderSPtr addOptionStatic(const UnionRef & value);

    LeafDefBuilderSPtr setOptionsStatic(const std::vector<UnionValue> &options);
    template<typename T>
    LeafDefBuilderSPtr setOptionsStatic(const std::vector<T> &options);

    LeafDefBuilderSPtr setOptionsExcludedStatic(const std::vector<UnionValue> &options);
    template<typename T>
    LeafDefBuilderSPtr setOptionsExcludedStatic(const std::vector<T> &options);

    LeafDefBuilderSPtr setOptionsQuery(LeafQuerySPtr value);
    LeafDefBuilderSPtr setOptionsExcludedQuery(LeafQuerySPtr value);

    LeafDefBuilderSPtr setSetting(std::string name, const UnionRef &value);

#ifdef XML_BACKEND
    LeafDefBuilderSPtr setXMLValueRef(XML::ValueRefUPtr value);
#endif
    const LeafDef &leafDef() const;
    LeafDefUPtr get();

private:
    LeafDefUPtr m_leafDefUPtr;
    LeafDef *m_leafDef;

    LeafDefBuilderWPtr m_thisWPtr;
};

// =============================================================================
// (public)
template<typename T>
LeafDefBuilderSPtr LeafDefBuilder::setOptionsStatic(const std::vector<T> &options)
{
    assert(m_leafDef);
    if (!options.empty() && m_leafDef->m_valueTemplate.type() == UnionValue::GetType(options.front())) {
        m_leafDef->m_options->m_options.clear();
        for (const auto& option: options)
        {
            m_leafDef->m_options->m_options.push_back(option);
        }
    } else {
        assert(false);
    }
    return m_thisWPtr.lock();
}

// =============================================================================
// (public)
template<typename T>
LeafDefBuilderSPtr LeafDefBuilder::setOptionsExcludedStatic(const std::vector<T> &options)
{
    assert(m_leafDef);
    if (!options.empty() && m_leafDef->m_valueTemplate.type() == UnionValue::GetType(options.front())) {
        m_leafDef->m_options->m_excluded.clear();
        for (const auto& option: options)
        {
            m_leafDef->m_options->m_excluded.push_back(option);
        }
    } else {
        assert(false);
    }
    return m_thisWPtr.lock();
}

typedef LeafDefBuilder VDB;

} // namespace Oak::Model

