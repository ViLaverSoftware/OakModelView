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

#include "XMLServiceFunctions.h"

#include <cctype>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include <utility>

#include "../ServiceFunctions/Assert.h"

#define BUFFER_SIZE 1000000

namespace Oak::XML {

// =============================================================================
// (public)
std::vector<std::string> split(const std::string &str, char seperator, bool ignoreEmpty)
{
    std::vector<std::string> sList;
    if (str.empty()) { return sList; }

    size_t first = 0, current = 0;
    do {
        if (current == str.size() || str.at(current) == seperator) {
            if (!ignoreEmpty || current-first > 0) {
                sList.push_back(str.substr(first, current-first));
            }
            first = current+1;
        }
        current++;
    } while (current <= str.size());

    return sList;
}

// =============================================================================
// (public)
std::vector<std::vector<std::string>> doubleSplit(const std::string &str, char outerSeperator, char innerSeperator, bool ignoreEmpty)
{
    std::vector<std::vector<std::string>> sMatrix;

    std::vector<std::string> outerList = split(str, outerSeperator, ignoreEmpty);
    for (const std::string& is: outerList) {
        sMatrix.push_back(split(is, innerSeperator, ignoreEmpty));
    }
    return sMatrix;
}

// =============================================================================
// (public)
int toInteger(const std::string &str, bool *ok)
{
    try {
        if (ok) { *ok = true; }
        return std::stoi(str);
    } catch(...) {
        if (ok) { *ok = false; }
        return 0;
    }
}

} // namespace Oak::XML
