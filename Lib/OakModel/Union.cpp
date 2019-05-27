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

#include "Union.h"

#include "UnionRef.h"
#include "UnionValue.h"


namespace Oak::Model {

// =============================================================================
// (public)
UnionType Union::GetType(type_info info)
{
    if (typeid(std::string) == info) {
        return UnionType::String;
    }
    if (typeid(double) == info) {
        return UnionType::Double;
    }
    if (typeid(int) == info) {
        return UnionType::Integer;
    }
    if (typeid(bool) == info) {
        return UnionType::Bool;
    }
    if (typeid(char) == info) {
        return UnionType::Char;
    }
    if (typeid(DateTime) == info) {
        return UnionType::DateTime;
    }
    return UnionType::Undefined;
}

// =============================================================================
// (public)
UnionType Union::GetType(const char *)
{
    return UnionType::Char;
}

// =============================================================================
// (public)
UnionType Union::GetType(bool)
{
    return UnionType::Bool;
}

// =============================================================================
// (public)
UnionType Union::GetType(int)
{
    return UnionType::Integer;
}

// =============================================================================
// (public)
UnionType Union::GetType(double)
{
    return UnionType::Double;
}

// =============================================================================
// (public)
UnionType Union::GetType(const std::string &)
{
    return UnionType::String;
}

// =============================================================================
// (public)
UnionType Union::GetType(const DateTime &)
{
    return UnionType::DateTime;
}

// =============================================================================
// (public)
UnionType Union::GetType(UnionType t)
{
    return t;
}

// =============================================================================
// (public)
UnionType Union::GetType(const UnionRef &ur)
{
    return ur.type();
}

// =============================================================================
// (public)
UnionType Union::GetType(const UnionValue &uv)
{
    return uv.type();
}

} // namespace Oak::Model

