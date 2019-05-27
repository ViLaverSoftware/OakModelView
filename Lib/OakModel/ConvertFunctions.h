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
#include <vector>

#include "Conversion.h"
#include "DateTime.h"

#include "../ServiceFunctions/Assert.h"

namespace Oak::Model {

// =============================================================================
// convert()
// =============================================================================
bool convert(bool& dest, int src, Conversion* properties = nullptr);
bool convert(int& dest, bool src, Conversion* properties = nullptr);

bool convert(bool&, double, Conversion* properties = nullptr);
bool convert(double&, bool, Conversion* properties = nullptr);

bool convert(bool& dest, const std::string& src, Conversion* properties = nullptr);
bool convert(std::string& dest, bool src, Conversion* properties = nullptr);

bool convert(int& dest, double src, Conversion* properties = nullptr);
bool convert(double& dest, int src, Conversion* properties = nullptr);

bool convert(int& dest, const std::string& src, Conversion* properties = nullptr);
bool convert(std::string& dest, int src, Conversion* properties = nullptr);

bool convert(double& dest, const std::string& src, Conversion* properties = nullptr);
bool convert(std::string& dest, double src, Conversion* properties = nullptr);

bool convert(std::string& dest, const char * source, Conversion* properties = nullptr);

bool convert(std::string& dest, const DateTime &src, Conversion* properties = nullptr);
bool convert(DateTime &dest, const std::string &src, Conversion* properties = nullptr);

template<typename T>
bool convert(T& dest, const T& source, Conversion* properties = nullptr)
{
    UNUSED(properties);
    dest = source;
    return true;
}

template<typename T>
bool convert(T& dest, const char * source, Conversion* properties = nullptr)
{
    if (source == nullptr) { return false; }
    return convert(dest, std::string(source), properties);
}

template<typename T1, typename T2>
bool convert(std::vector<T1>&, const T2&, Conversion* properties = nullptr)
{
    UNUSED(properties);
    return false;
}

template<typename T1, typename T2>
bool convert(T1&, const std::vector<T2>&, Conversion* properties = nullptr)
{
    UNUSED(properties);
    return false;
}

template<typename T1, typename T2>
bool convert(std::vector<T1>& dest, const std::vector<T2>& src, Conversion* properties = nullptr)
{
    const int size = static_cast<int>(src.size());
    dest.resize(size);
    if (size == 0) { return true; }
    bool success = true;
    T1* destPtr = dest.data();
    const T2* srcPtr = src.data();
    for (int i = 0; i < size; ++i)
    {
        if (!convert(*destPtr++, *srcPtr++, properties)) {
            success = false;
        }
    }
    return success;
}

template<typename T1, typename T2>
bool convert(T1 &dest, const T2 &source, Conversion* properties = nullptr)
{
    UNUSED(dest);
    UNUSED(source);
    UNUSED(properties);
    ASSERT(false);
    return false;
}

// =============================================================================
// canConvert()
// =============================================================================
bool canConvert(bool& dest, int& src, Conversion* properties = nullptr);
bool canConvert(int& dest, const bool& src, Conversion* properties = nullptr);

bool canConvert(bool& dest, double src, Conversion* properties = nullptr);
bool canConvert(double& dest, bool src, Conversion* properties = nullptr);

bool canConvert(std::string& dest, bool src, Conversion* properties = nullptr);

bool canConvert(int& dest, double src, Conversion* properties = nullptr);
bool canConvert(double& dest, int src, Conversion* properties = nullptr);

bool canConvert(std::string& dest, const int& src, Conversion* properties = nullptr);
bool canConvert(std::string& dest, const double& src, Conversion* properties = nullptr);

bool canConvert(std::string& dest, const char * source, Conversion* properties = nullptr);

bool canConvert(std::string &dest, const DateTime &src, Conversion *properties);
bool canConvert(DateTime &dest, const std::string &src, Conversion *properties);

template<typename T>
bool canConvert(T& dest, const char * source, Conversion* properties = nullptr)
{
    if (source == nullptr) { return false; }
    return canConvert(dest, std::string(source), properties);
}

template<typename T1, typename T2>
bool canConvert(T1&, const T2& src, Conversion* properties = nullptr)
{
    T1 tempDest;
    return convert(tempDest, src, properties);
}

// =============================================================================
// compare typeid
// =============================================================================

template<typename T1, typename T2>
bool isTypeIdBaseEqual(const T1&, const T2&)
{
    if (typeid(T1) == typeid(T2)) { return true; }
    if (typeid(T1) == typeid(std::vector<T2>)) { return true; }
    if (typeid(std::vector<T1>) == typeid(T2)) { return true; }
    return false;
}

} // namespace Oak::Model

