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

#include "Conversion.h"


namespace Oak::Model {

// =============================================================================
// (public)
Conversion::Conversion()
{
}

// =============================================================================
// (public)
ConversionSPtr Conversion::globalDefault()
{
    static ConversionSPtr globalDefault(new Conversion());

    // Initialize the global default conversion
    if (globalDefault->m_boolTrue.empty()) {
        globalDefault->m_boolTrue = "true";
        globalDefault->m_boolFalse = "false";
        globalDefault->m_listSeperator = ";";
        globalDefault->m_roundRules = DoubleToInt_Round;
        globalDefault->m_equalTolerance = 1.0e-12;
        globalDefault->m_doubleToStringPrecision = 5;
        globalDefault->m_doubleToStringMode = DoubleToString_Default;
    }
    return globalDefault;
}

// =============================================================================
// (public)
Conversion*Conversion::globalDefault2()
{
    static Conversion* s_default = new Conversion();

    // Initialize the global default conversion
    if (s_default->m_boolTrue.empty()) {
        s_default->m_boolTrue = "true";
        s_default->m_boolFalse = "false";
        s_default->m_listSeperator = ";";
        s_default->m_roundRules = DoubleToInt_Round;
        s_default->m_equalTolerance = 1.0e-12;
        s_default->m_doubleToStringPrecision = 5;
        s_default->m_doubleToStringMode = DoubleToString_Default;
    }

    return s_default;
}

} // namespace Oak::Model

