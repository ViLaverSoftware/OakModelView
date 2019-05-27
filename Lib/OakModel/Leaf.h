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

#include <utility>

#include "LeafDef.h"
#include "ValueOptions.h"


namespace Oak::Model {

class Node;

// =============================================================================
// Class definition
// =============================================================================
class Leaf
{
public:
    Leaf();
    Leaf(const LeafDef* leafDef, const NodeData &nodeData, const Node* node/* = nullptr*/);
    Leaf(const Leaf& copy);
    Leaf(Leaf&& move);

    Leaf& operator=( const Leaf& copy);
    Leaf& operator=(Leaf&& move);

    bool operator==(const Leaf& _leaf) const;
    bool operator!=(const Leaf& _leaf) const;

    bool isNull() const;
    bool isDefNull() const;
    bool isNodeNull() const;

    const std::string &name() const;
    const std::string &displayName() const;

    const std::string &tooltip() const;

    const NodeData& nodeData() const;
    const LeafDef* def() const;
    const Node* node() const;

    template<typename T>
    bool canGetValue(T &value, bool useDefault = true) const;
    template<typename T>
    bool getValue(T &value, bool useDefault = true) const;

    UnionValue value(bool useDefault = true) const;
    template<typename T>
    T value(bool useDefault = true) const;

    std::string toString(bool useDefault = true) const;

    template<typename T>
    bool canSetValue(const T &value) const;
    template<typename T>
    bool setValue(const T &value) const;

    bool hasDefaultValue() const;
    template<typename T>
    bool getDefaultValue(T &value) const;

    template<typename T>
    T defaultValue() const;

    bool hasOptions() const;
    template<typename T>
    bool hasOption(const T &value) const;
    
    template<typename T>
    bool getOptions(std::vector<T>& value) const;

    const LeafSettings& settings() const;

    static Leaf &emptyLeaf();

    template<typename T>
    bool operator<<(const T& value) const;

protected:
    void onLeafChangeBefore() const;
    void onLeafChangeAfter() const;

protected:
    const LeafDef* m_def;
    NodeData m_nodeData;
    const Node* m_node;

    friend class Node;
};

// =============================================================================
// (public)
template<typename T>
bool Leaf::canGetValue(T &value, bool useDefault) const
{
    assert(m_def != nullptr);
    return m_def->canGetValue(m_nodeData, value, useDefault, true);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::getValue(T &value, bool useDefault) const
{
    assert(m_def != nullptr);
    return m_def->getValue(m_nodeData, value, useDefault, true);
}

// =============================================================================
// (public)
template<typename T>
T Leaf::value(bool useDefault) const
{
    assert(m_def != nullptr);
    return m_def->value<T>(m_nodeData, useDefault, true);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::canSetValue(const T &value) const
{
    assert(m_def != nullptr);
    return m_def->canSetValue(m_nodeData, value, true);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::setValue(const T &value) const
{
    assert(m_def != nullptr);

    if (m_node) {
        onLeafChangeBefore();
    }
    bool result = m_def->setValue(m_nodeData, value, true);
    if (m_node) {
        onLeafChangeAfter();
    }
    return result;
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::getDefaultValue(T &value) const
{
    assert(m_def != nullptr);
    return m_def->getDefaultValue(value);
}

// =============================================================================
// (public)
template<typename T>
T Leaf::defaultValue() const
{
    assert(m_def != nullptr);
    T value;
    m_def->getDefaultValue(value);
    return std::move(value);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::hasOption(const T& value) const
{
    return m_def->options().hasOption(value, m_node);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::getOptions(std::vector<T>& value) const
{
    assert(m_def != nullptr);
    return m_def->options().getOptions(value, m_node);
}

// =============================================================================
// (public)
template<typename T>
bool Leaf::operator<<(const T& value) const
{
    return setValue(value);
}

// =============================================================================
// (free)
template<typename T>
bool operator<<(T & value, const Leaf &node)
{
    assert(!node.isNull());
    return node.getValue(value);
}


} // namespace Oak::Model

