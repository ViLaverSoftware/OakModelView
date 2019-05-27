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

#include "Union.h"
#include "UnionRef.h"
#include "Conversion.h"
#include "ConvertFunctions.h"


namespace Oak::Model {

// =============================================================================
// Class definition
// =============================================================================
class UnionValue
{
public:
    UnionValue();
    UnionValue(const char *c);
    UnionValue(bool b);
    UnionValue(int i);
    UnionValue(double d);
    UnionValue(const std::string &s);
    UnionValue(const DateTime &dt);
    UnionValue(UnionType type);

    UnionValue(const UnionRef& uRef);

    UnionValue(const UnionValue& copy);
    UnionValue(UnionValue&& move);

    ~UnionValue();

    UnionValue& operator=(const UnionRef& value);
    UnionValue& operator=(const UnionValue& copy);
    UnionValue& operator=(UnionValue&& move);

    template<typename T>
    UnionValue& operator=(T value) { return *this = UnionRef(value); }

    operator bool() const;

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

    int compare(const UnionRef& value, bool allowConversion = false, Conversion* properties = nullptr) const;

    bool isEqual(const UnionRef& value, bool allowConversion = true, Conversion* properties = nullptr) const;

    bool isNull() const;

    UnionType type() const;

    const UnionRef getRef() const;
    UnionRef getRef();

    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const std::string& getCString() const;
    std::string& getString();

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

    template<typename T>
    static UnionType GetType(const T &v);
protected:
    UValue v;
    UnionType t;

    friend class UnionRef;
};

// =============================================================================
// (public)
template<typename T>
UnionType UnionValue::GetType(const T &v)
{
    UnionType type = Union::GetType(v);
    return (type == UnionType::Char) ? UnionType::String : type;
}

// =============================================================================
// (public)
template<typename T>
bool UnionValue::canGet(T &target, bool allowConversion, Conversion *properties) const
{
    UnionRef sourceRef(*this);
    return sourceRef.canGet(target, allowConversion, properties);
}

// =============================================================================
// (public)
template<typename T>
bool UnionValue::get(T &target, bool allowConversion, Conversion *properties) const
{
    UnionRef sourceRef(*this);
    return sourceRef.get(target, allowConversion, properties);
}

// =============================================================================
// (public)
template<typename T>
T UnionValue::value(bool allowConversion, Conversion *properties) const
{
    T v;
    get(v, allowConversion, properties);
    return std::move(v);
}

typedef std::vector<UnionValue> UnionValueList;

} // namespace Oak::Model

