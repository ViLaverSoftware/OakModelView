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
#include <memory>
#include <vector>

#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif


namespace Oak::Model {

typedef std::vector<int>::size_type vSize;

class Conversion;
typedef std::shared_ptr<Conversion> ConversionSPtr;

// =============================================================================
// Class definition
// =============================================================================
class Conversion
{
public:
    enum DoubleToInt {
        DoubleToInt_Round = 0,
        DoubleToInt_Floor,
        DoubleToInt_Ceil,
        DoubleToInt_Trunc
    };

    enum DoubleToString {
        DoubleToString_Default = 0,
        DoubleToString_Fixed,
        DoubleToString_Scientific
    };

public:
    Conversion();

    const std::string &boolTrue() const { return m_boolTrue; }
    const std::string &boolFalse() const { return m_boolFalse; }

    double equalTolerance() const { return m_equalTolerance; }

    static ConversionSPtr globalDefault();
    static Conversion* globalDefault2();

    DoubleToInt roundRules() const { return m_roundRules; }

    int doubleToStringPrecision() const { return m_doubleToStringPrecision; }
    DoubleToString doubleToStringMode() const { return m_doubleToStringMode; }
private:
    // Bool to string and back
    std::string m_boolTrue;
    std::string m_boolFalse;

    int m_doubleToStringPrecision;
    DoubleToString m_doubleToStringMode = DoubleToString_Default;

    // Double to integer
    DoubleToInt m_roundRules;

    //ToDo: Double to string rules

    std::string m_listSeperator;

    double m_equalTolerance;
};

} // namespace Oak::Model

