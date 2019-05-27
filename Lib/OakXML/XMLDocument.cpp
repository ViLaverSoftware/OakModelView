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

#ifdef XML_BACKEND

#include "XMLDocument.h"

#include "XMLServiceFunctions.h"

#include "../ServiceFunctions/Assert.h"

namespace Oak::XML {

// =============================================================================
//
Document::Document()
    : m_document(new pugi::xml_document())
{
}

// =============================================================================
//
Document::Document(const Document &copy)
{
    *this = copy;
}

// =============================================================================
//
Document & Document::operator=(const Document &copy)
{
    m_document = copy.m_document;
    return *this;
}

// =============================================================================
//
bool Document::operator==(const Document &doc) const
{
    return m_document.get() == doc.m_document.get();
}

// =============================================================================
//
bool Document::operator !=(const Document &doc) const
{
    return !(operator ==(doc));
}

// =============================================================================
//
bool Document::isContentEqual(const Document &doc) const
{
    // TODO: Implement this
    return m_document == doc.m_document;
}

// =============================================================================
//
bool Document::isNull() const
{
    return m_document->first_child().empty();
}

// =============================================================================
//
Element Document::appendChild(const std::string &tagName)
{
    return Element(m_document->append_child(tagName.c_str()));
}

// =============================================================================
//
void Document::clear()
{
    m_document->reset();
}

// =============================================================================
//
bool Document::save(std::string filePath) const
{
    return m_document->save_file(filePath.c_str(), "  ", pugi::format_indent | pugi::format_save_file_text);
}

// =============================================================================
//
void Document::save(std::string &str, int indent) const
{
    // TODO
    UNUSED(str);
    UNUSED(indent);
}

// =============================================================================
//
void Document::clone(const Document &copy)
{
    m_document->reset(*copy.m_document.get());
}

// =============================================================================
//
bool Document::load(std::string filePath)
{
    return m_document->load_file(filePath.c_str(), pugi::parse_full).status == pugi::status_ok;
}

// =============================================================================
//
bool Document::load(std::istream stream)
{
    return m_document->load(stream).status == pugi::status_ok;
}

// =============================================================================
//
Element Document::documentElement()
{
    return Element(m_document->document_element());
}

} // namespace Oak::XML

#endif // XML_BACKEND
