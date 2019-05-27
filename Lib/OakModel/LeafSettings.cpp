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

#include "../ServiceFunctions/Assert.h"

#include "LeafSettings.h"
#include "UnionRef.h"


namespace Oak::Model {

// =============================================================================
// (public)
LeafSettings::LeafSettings()
{
    m_settingsMap[OPTION_ONLY] = false;
    m_settingsMap[UNIT] = "";
    m_settingsMap[UNIQUE] = -1;
    m_settingsMap[REQUIRED] = -1;
}

// =============================================================================
// (public)
LeafSettings& LeafSettings::operator=(const LeafSettings& copy)
{
    m_settingsMap = copy.m_settingsMap;
    return *this;
}

// =============================================================================
// (public)
const UnionValue &LeafSettings::value(const std::string &settingName, const UnionValue &defaultValue) const
{
    auto it = m_settingsMap.find(settingName);
    if (it != m_settingsMap.end()) {
        return it->second;
    }
    ASSERT(!defaultValue.isNull());
    return defaultValue;
}

// =============================================================================
// (public)
void LeafSettings::setValue(const std::string &settingName, const UnionRef &value)
{
    m_settingsMap[settingName] = value;
}

} // namespace Oak::Model

