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

#include "NodeServiceFunctions.h"

#include "../ServiceFunctions/Trace.h"


namespace Oak::Model {

// =============================================================================
// (public)
void findOptionQueries(const NodeDef *def, std::vector<NodeLeafDefPair> &queryList, std::vector<NodeLeafDefPair> &queryExcludedList, bool recursive)
{
    std::vector<const LeafDef *> leafDefList = def->valueList(true, true);

    for (const LeafDef *vDef: leafDefList) {
        //TRACE(L"Searching %S:%S", def->displayName().c_str(), vDef->displayName().c_str());
        if (vDef->options().hasQuery()) {
            queryList.push_back({ def, vDef });
        }
        if (vDef->options().hasQueryExcluded()) {
            queryExcludedList.push_back({ def, vDef });
        }
    }

    if (recursive) {
        std::vector<const NodeDef *> childNodeDefList = def->childDefList(true, true);
        def->removeParentDefs(childNodeDefList, true);

        for (const NodeDef *cDef: childNodeDefList)
        {
            findOptionQueries(cDef, queryList, queryExcludedList, recursive);
        }
    }
}

} // namespace Oak::Model

