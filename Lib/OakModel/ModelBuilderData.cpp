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

#include "ModelBuilderData.h"

#include "../ServiceFunctions/Trace.h"

#include "NodeDef.h"

namespace Oak::Model {

// =============================================================================
// (public)
ModelBuilderData::ModelBuilderData()
{
    //TRACE("ModelBuilderData");
}

// =============================================================================
// (public)
bool ModelBuilderData::validateModel()
{
    for (const NodeDefBuilderDataUPtr &ndb: nodeDefs)
    {
        ndb->validate(errorMessages);
    }
    return errorMessages.empty();
}

// =============================================================================
// (public)
NodeDefSPtr ModelBuilderData::createModel()
{
    if (validateModel()) {
        //TRACE("OakModel is valid");
    } else {
        TRACE("OakModel is NOT valid");
        for (const std::string &errorMessage: errorMessages)
        {
            TRACE(errorMessage.c_str());
        }

        return NodeDefSPtr();
    }

    std::vector<Oak::Model::NodeDefSPtr> nodeDefList;

    for (const NodeDefBuilderDataUPtr &ndb: nodeDefs) {
        nodeDefList.push_back(ndb->create());
    }

    // All node definitions have to be created before the containers can be
    for (size_t i = 0; i < nodeDefs.size(); i++)
    {
        nodeDefs[i]->createContainers(nodeDefList[i], nodeDefList);
    }

    return nodeDefList[0];
}

} // namespace Oak::Model
