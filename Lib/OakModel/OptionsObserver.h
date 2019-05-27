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

#include "ObserverInterface.h"
#include "UnionValue.h"


namespace Oak::Model {

class NodeDef;
class LeafDef;
class NodeIndex;

class LeafQuery;
typedef std::shared_ptr<LeafQuery> LeafQuerySPtr;

// =============================================================================
// Class definition
// =============================================================================
class OptionsObserver : public ObserverInterface
{
public:
    OptionsObserver(OakModel * model, const NodeDef *optionsNodeDef, const LeafDef *optionsLeafDef);

    virtual void connect() override;
    virtual void disconnect() override;

protected:
    void onNodeInserteAfter(const NodeIndex& nodeIndex);
    void onNodeMoveAfter(const NodeIndex& sourceNodeIndex, const NodeIndex& targetNodeIndex);
    void onNodeMoveBefore(const NodeIndex& sourceNodeIndex, const NodeIndex& targetNodeIndex);
    void onNodeCloneAfter(const NodeIndex& sourceNodeIndex, const NodeIndex& targetNodeIndex);

    void onNodeRemoveBefore(const NodeIndex& nodeIndex);

    void onLeafChangeBefore(const NodeIndex& nodeIndex, const std::string &valueName);
    void onLeafChangeAfter(const NodeIndex& nodeIndex, const std::string &valueName);

protected:
    const NodeDef *m_optionsNodeDef;
    const LeafDef *m_optionsLeafDef;
    LeafQuerySPtr m_inverseQuery;

    const NodeDef *m_sourceNodeDef;
    std::string m_sourceValueName;

    UnionValue m_valueBeforeChange;
};


typedef std::unique_ptr<OptionsObserver> OptionsObserverUPtr;

} // namespace Oak::Model

