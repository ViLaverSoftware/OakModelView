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

#include "QOakToolButton.h"
#include "NodeIndex.h"

// =============================================================================
// Class definition
// =============================================================================
class QOakToolButtonRemove : public QOakToolButton
{
    Q_OBJECT
public:
    QOakToolButtonRemove(QObject *parent = nullptr);

    virtual int count() const override;

    virtual QVariant data(int index, int role) const override;

    virtual void sourceModelConnect() override;
    virtual void sourceModelDisconnect() override;

    virtual void trigger(int index) override;

protected:
    void onNodeInserteAfter(const Oak::Model::NodeIndex& nodeIndex);
    void onNodeRemoveAfter(const Oak::Model::NodeIndex& nodeIndex);
    void onNodeMoveAfter(const Oak::Model::NodeIndex& sourceNodeIndex, const Oak::Model::NodeIndex& targetNodeIndex);
    void onNodeCloneAfter(const Oak::Model::NodeIndex& sourceNodeIndex, const Oak::Model::NodeIndex& targetNodeIndex);

};

