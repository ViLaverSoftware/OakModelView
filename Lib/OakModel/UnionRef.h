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

#include <assert.h>

#include "Union.h"
#include "ConvertFunctions.h"


namespace Oak::Model {

class UnionValue;

// =============================================================================
// Class definition
// =============================================================================
class UnionRef
{
public:
    UnionRef();
    UnionRef(const char *c);
    UnionRef(const bool &b);
    UnionRef(const int &i);
    UnionRef(const double &d);
    UnionRef(const std::string &s);
    UnionRef(const DateTime &dt);
    UnionRef(const UnionValue &v);

    UnionRef(const UnionRef &copy);

    ~UnionRef();

    UnionRef& operator=(const UnionRef& copy);

    template<typename T>
    UnionRef& operator=(T value) { return *this = UnionRef(value); }

    bool operator==(const UnionRef& value) const;
    bool operator!=(const UnionRef& value) const;

    bool operator>(const UnionRef& value) const;
    bool operator>=(const UnionRef& value) const;
    bool operator<(const UnionRef& value) const;
    bool operator<=(const UnionRef& value) const;

    template<typename T>
    bool operator==(T value) const { return *this == UnionRef(value); }
    template<typename T>
    bool operator!=(T value) const { return *this != UnionRef(value); }

    template<typename T>
    bool operator>(T value) const { return *this > UnionRef(value); }
    template<typename T>
    bool operator>=(T value) const { return *this >= UnionRef(value); }
    template<typename T>
    bool operator<(T value) const { return *this < UnionRef(value); }
    template<typename T>
    bool operator<=(T value) const { return *this <= UnionRef(value); }

    int compare(UnionRef value, bool allowConversion = true, Conversion* properties = nullptr) const;

    bool isEqual(const UnionRef& value, bool allowConversion = true, Conversion* properties = nullptr) const;

    bool isNull() const;

    UnionType type() const;

    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const std::string& getCString() const;
    std::string& getString();
    const DateTime &getDateTime() const;

    template<typename T>
    bool canGet(T& target, bool allowConversion = true, Conversion* properties = nullptr) const;
    template<typename T>
    bool get(T& target, bool allowConversion = true, Conversion* properties = nullptr) const;

    bool canGet(UnionRef& target, bool allowConversion = true, Conversion* properties = nullptr) const;
    bool get(UnionRef& target, bool allowConversion = true, Conversion* properties = nullptr) const;

    bool canGet(UnionValue& target, bool allowConversion = true, Conversion* properties = nullptr) const;
    bool get(UnionValue& target, bool allowConversion = true, Conversion* properties = nullptr) const;

    template<typename T>
    T value(bool allowConversion = true, Conversion* properties = nullptr) const;

protected:
    UPtr r;
    UnionType t;

    friend class UnionValue;
};

// =============================================================================
// (public)
template<typename T>
bool UnionRef::canGet(T &target, bool allowConversion, Conversion *properties) const
{
    if (t == UnionType::Undefined) { return false; }
    if (!allowConversion && t != Union::GetValueType(target)) { return false; }

    switch (t) {
        case UnionType::Undefined:
            return false;
        case UnionType::Char:
            return canConvert(target, r.c, properties);
        case UnionType::Bool:
            return canConvert(target, *r.b, properties);
        case UnionType::Integer:
            return canConvert(target, *r.i, properties);
        case UnionType::Double:
            return canConvert(target, *r.d, properties);
        case UnionType::String:
            return canConvert(target, *r.s, properties);
        case UnionType::DateTime:
            return canConvert(target, *r.dt, properties);
        default:
            assert(false);
            return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
bool UnionRef::get(T &target, bool allowConversion, Conversion *properties) const
{
    if (t == UnionType::Undefined) { return false; }
    if (!allowConversion && t != Union::GetValueType(target)) { return false; }

    switch (t) {
        case UnionType::Undefined:
            return false;
        case UnionType::Char:
            return convert(target, r.c, properties);
        case UnionType::Bool:
            return convert(target, *r.b, properties);
        case UnionType::Integer:
            return convert(target, *r.i, properties);
        case UnionType::Double:
            return convert(target, *r.d, properties);
        case UnionType::String:
            return convert(target, *r.s, properties);
        case UnionType::DateTime:
            return convert(target, *r.dt, properties);
        default:
            assert(false);
            return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
T UnionRef::value(bool allowConversion, Conversion *properties) const
{
    T v;
    get(v, allowConversion, properties);
    return std::move(v);
}

} // namespace Oak::Model

