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

#include <string>
#include <chrono>

#include "DateTime.h"


namespace Oak::Model {

enum class UnionType { Undefined = -1, Char = 0, Bool = 1, Integer = 2, Double = 3, String = 4, DateTime = 5 };
typedef union UValue { bool b; int i; double d; std::string *s; DateTime *dt; } UValue;
typedef union UPtr { const char *c; const bool *b; const int *i; const double *d; const std::string *s; const DateTime *dt; } UPtr;

class UnionRef;
class UnionValue;

// =============================================================================
// Class definition
// =============================================================================
class Union
{
public:
    static UnionType GetType(type_info info);
    static UnionType GetType(const char*);
    static UnionType GetType(bool);
    static UnionType GetType(int);
    static UnionType GetType(double);
    static UnionType GetType(const std::string&);
    static UnionType GetType(const DateTime&);
    static UnionType GetType(UnionType t);
    static UnionType GetType(const UnionRef& ur);
    static UnionType GetType(const UnionValue& uv);

    template<typename T>
    static UnionType GetValueType(const T &v);
};

// =============================================================================
// (public)
template<typename T>
UnionType Union::GetValueType(const T &v)
{
    UnionType type = GetType(v);
    return (type == UnionType::Char) ? UnionType::String : type;

}

} // namespace Oak::Model

