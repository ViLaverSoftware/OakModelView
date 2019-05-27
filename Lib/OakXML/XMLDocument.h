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

#include <memory>

namespace Oak::XML {

// =============================================================================
// Class definition
// =============================================================================
class Document
{
public:
    Document();
    Document(const Document &copy);

    Document & operator=(const Document &copy);

    bool operator == (const Document &doc) const;
    bool operator != (const Document &doc) const;
    bool isContentEqual(const Document &doc) const;

    bool isNull() const;

    bool save(std::string filePath) const;
    void save(std::string &str, int indent) const;

    Element appendChild(const std::string &tagName);

    void clear();

    void clone(const Document &copy);

    bool load(std::string filePath);
    bool load(std::istream stream);
    Element documentElement();

private:
    std::shared_ptr<pugi::xml_document> m_document;
};

} // namespace Oak::XML

#endif // XML_BACKEND
