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

#include <list>
#include <string>
#include <vector>
#include <memory>
#include <limits>

namespace Oak::XML {

// =============================================================================
// Conversion service functions
// =============================================================================

std::vector<std::string> split(const std::string &str, char seperator = ';', bool ignoreEmpty = false);
std::vector<std::vector<std::string>> doubleSplit(const std::string &str, char outerSeperator = ';', char innerSeperator = ':', bool ignoreEmpty = false);

int toInteger(const std::string &str, bool *ok = nullptr);

template<typename TO, typename FROM>
std::unique_ptr<TO> dynamic_unique_pointer_cast(std::unique_ptr<FROM>&& old)
{
    TO* ptr = dynamic_cast<TO*>(old.get());
    if (ptr) {
        old.release();
        return std::unique_ptr<TO>(ptr);
    }
    assert(false);
    return std::unique_ptr<TO>(nullptr);
}

} // namespace Oak::XML
