/**
 * oakmodelview - version 0.1.0
 * --------------------------------------------------------
 * Copyright (C) 2017, by Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * Report bugs and download new versions at http://oakmodelview.com/
 *
 * This library is distributed under the MIT License.
 * See accompanying file LICENSE in the root folder.
 */

#pragma once

#include "Union.h"
#include "Conversion.h"
#include "ConvertFunctions.h"

#include <assert.h>

namespace Oak {
namespace Model {

class UnionRef;

// =============================================================================
// Class definition
// =============================================================================
class UnionValue
{
public:
    UnionValue();
    UnionValue(const char *c);
    UnionValue(const bool &b);
    UnionValue(const int &i);
    UnionValue(const double &d);
    UnionValue(const std::string &s);
    UnionValue(UnionType type);

    UnionValue(const UnionRef& uRef);

    UnionValue(const UnionValue& copy);
    UnionValue(UnionValue&& move);

    ~UnionValue();

    UnionValue& operator=(const UnionRef& value);
    UnionValue& operator=(const UnionValue& copy);
    UnionValue& operator=(UnionValue&& move);

    bool operator==(const UnionRef& value) const;
    bool operator!=(const UnionRef& value) const;

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

    bool canGet(UnionValue& target, Conversion* properties = nullptr) const;
    bool get(UnionValue& target, Conversion* properties = nullptr) const;

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

} // namespace Model
} // namespace Oak
