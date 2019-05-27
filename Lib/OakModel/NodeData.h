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

#ifdef XML_BACKEND
#include "XMLElement.h"
#endif // XML_BACKEND


namespace Oak::Model {

// =============================================================================
// Class definition
// =============================================================================
class NodeData
{
public:
    enum class Type { UNDEFINED, XML };

    NodeData();
    NodeData(void * internalPtr, Type type);
    NodeData(const NodeData& copy);
    NodeData(NodeData&& move);

    ~NodeData() {}

    NodeData& operator=(const NodeData& copy);
    NodeData& operator=(NodeData&& move);

    bool operator==(const NodeData& _node) const;
    bool operator!=(const NodeData& _node) const;

    void clear();

    bool isNull() const;

    Type type() const;

    void * internalPtr() const;

#ifdef XML_BACKEND
    NodeData(XML::Element _xmlNode);
    bool isXML() const;
    XML::Element xmlNode() const;
#endif // XML_BACKEND

private:
    Type m_type;

    //union {
    #ifdef XML_BACKEND
        XML::Element m_xmlNode;
    #endif // XML_BACKEND
    //};
};

} // namespace Oak::Model

