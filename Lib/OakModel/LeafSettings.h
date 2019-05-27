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
#include <map>

#include "UnionValue.h"


namespace Oak::Model {

#define OPTION_ONLY     "OptionsOnly"
#define UNIT            "Unit"
#define UNIQUE          "Unique"
#define REQUIRED        "Required"

// =============================================================================
// Class definition
// =============================================================================
class LeafSettings
{
public:
    LeafSettings();

    LeafSettings& operator=(const LeafSettings& copy);

    const UnionValue &value(const std::string &settingName, const UnionValue &defaultValue = UnionValue()) const;
    void setValue(const std::string &settingName, const UnionRef &value);

private:
    // x < 0 => false
    // x > 0 => true
    // x == 0 => undefined (default is false)

    std::map<std::string, UnionValue> m_settingsMap;
};

} // namespace Oak::Model

