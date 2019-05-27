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

#include <map>
#include <functional>

#include "Node.h"
#include "NodeIndex.h"


namespace Oak::Model {

// =============================================================================
// Class definition
// =============================================================================
class Callback
{
public:
    Callback();

    template<typename T>
    void add(T* funcObj, void (T::*func)(void)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger() const;

protected:
    mutable std::map<void*, std::function<void(void)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeIntNodeInt
{
public:
    Callback_NodeIntNodeInt();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const Node&, int, const Node&, int)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const Node& sourceNode, int sourceIndex, const Node& targetNode, int targetIndex) const;

protected:
    mutable std::map<void*, std::function<void(const Node&, int, const Node&, int)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeInt
{
public:
    Callback_NodeInt();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const Node&, int)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const Node &parentNode, int index) const;

protected:
    mutable std::map<void*, std::function<void(const Node&, int)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_Node
{
public:
    Callback_Node();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const Node&)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const Node &parentNode) const;

protected:
    mutable std::map<void*, std::function<void(const Node&)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeIndex
{
public:
    Callback_NodeIndex();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const NodeIndex&)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const NodeIndex &nodeIndex) const;

protected:
    mutable std::map<void*, std::function<void(const NodeIndex&)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeIndexNodeIndex
{
public:
    Callback_NodeIndexNodeIndex();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const NodeIndex&, const NodeIndex&)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const NodeIndex &nodeIndex1, const NodeIndex &nodeIndex2) const;

protected:
    mutable std::map<void*, std::function<void(const NodeIndex&, const NodeIndex&)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeIndexInt
{
public:
    Callback_NodeIndexInt();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const NodeIndex&, int)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const NodeIndex &nodeIndex, int index) const;

protected:
    mutable std::map<void*, std::function<void(const NodeIndex&, int)>> m_functionMap;
};

// =============================================================================
// Class definition
// =============================================================================
class Callback_NodeIndexString
{
public:
    Callback_NodeIndexString();

    template<typename T>
    void add(T* funcObj, void (T::*func)(const NodeIndex&, const std::string &)) const
    {
        if (funcObj == nullptr) {
            assert(false);
            return;
        }
        m_functionMap[funcObj] = std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2);
    }

    void remove(void* funcObj = nullptr) const;

    void trigger(const NodeIndex &nodeIndex, const std::string & name) const;

protected:
    mutable std::map<void*, std::function<void(const NodeIndex&, const std::string &)>> m_functionMap;
};

} // namespace Oak::Model

