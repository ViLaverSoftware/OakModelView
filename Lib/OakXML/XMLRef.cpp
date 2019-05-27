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

#include "XMLRef.h"

namespace Oak::XML {

std::string Ref::emptyStr = "";

// =============================================================================
// (public)
RefUPtr Ref::copy() const
{
    return MakeUPtr();
}

// =============================================================================
// (public)
Element Ref::getTarget(Element source, bool create) const
{
    UNUSED(create);
    return source;
}

// =============================================================================
// (public)
void Ref::clearTarget(Element source, bool onlyIfEmpty) const
{
    UNUSED(source);
    UNUSED(onlyIfEmpty);
}

// =============================================================================
// (public)
bool Ref::hasTarget(Element source) const
{
    return !getTarget(source).isNull();
}

// =============================================================================
// (public)
Element Ref::getSource(Element target) const
{
    return target;
}

} // namespace Oak::XML

#endif // XML_BACKEND
