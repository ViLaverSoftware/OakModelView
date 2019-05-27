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

#include "CallbackFunctions.h"

#include "../ServiceFunctions/Assert.h"


namespace Oak::Model {

// =============================================================================
// (public)
Callback::Callback()
{

}

// =============================================================================
// (public)
void Callback::remove(void* funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback::trigger() const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback::trigger()";
        func.second();
    }
}

// =============================================================================
// (public)
Callback_NodeIntNodeInt::Callback_NodeIntNodeInt()
{

}

// =============================================================================
// (public)
void Callback_NodeIntNodeInt::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeIntNodeInt::trigger(const Node &sourceNode, int sourceIndex, const Node &targetNode, int targetIndex) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeIntNodeInt::trigger()";
        func.second(sourceNode, sourceIndex, targetNode, targetIndex);
    }
}

// =============================================================================
// (public)
Callback_NodeInt::Callback_NodeInt()
{

}

// =============================================================================
// (public)
void Callback_NodeInt::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeInt::trigger(const Node &parentNode, int index) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeInt::trigger()";
        func.second(parentNode, index);
    }
}

// =============================================================================
// (public)
Callback_Node::Callback_Node()
{

}

// =============================================================================
// (public)
void Callback_Node::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_Node::trigger(const Node &parentNode) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_Node::trigger()";
        func.second(parentNode);
    }
}

// =============================================================================
// (public)
Callback_NodeIndex::Callback_NodeIndex()
{

}

// =============================================================================
// (public)
void Callback_NodeIndex::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeIndex::trigger(const NodeIndex &nodeIndex) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeIndex::trigger()";
        func.second(nodeIndex);
    }
}

// =============================================================================
// (public)
Callback_NodeIndexNodeIndex::Callback_NodeIndexNodeIndex()
{

}

// =============================================================================
// (public)
void Callback_NodeIndexNodeIndex::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeIndexNodeIndex::trigger(const NodeIndex &nodeIndex1, const NodeIndex &nodeIndex2) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeIndexNodeIndex::trigger()";
        func.second(nodeIndex1, nodeIndex2);
    }
}

// =============================================================================
// (public)
Callback_NodeIndexInt::Callback_NodeIndexInt()
{

}

// =============================================================================
// (public)
void Callback_NodeIndexInt::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeIndexInt::trigger(const NodeIndex &nodeIndex, int index) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeIndexInt::trigger()";
        func.second(nodeIndex, index);
    }
}

// =============================================================================
// (public)
Callback_NodeIndexString::Callback_NodeIndexString()
{

}

// =============================================================================
// (public)
void Callback_NodeIndexString::remove(void *funcObj) const
{
    if (funcObj == nullptr) {
        m_functionMap.clear();
    } else {
        auto it = m_functionMap.find(funcObj);
        while (it != m_functionMap.end()) {
            m_functionMap.erase(it);
            it = m_functionMap.find(funcObj);
        }
    }
}

// =============================================================================
// (public)
void Callback_NodeIndexString::trigger(const NodeIndex &nodeIndex, const std::string &name) const
{
    for (auto func: m_functionMap)
    {
        //qDebug() << "Callback_NodeIndexInt::trigger()";
        func.second(nodeIndex, name);
    }
}

} // namespace Oak::Model

