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

#include <QFrame>

#include "OakModel.h"
#include "NodeIndex.h"

class QScrollArea;
class QGridLayout;
class QVBoxLayout;


namespace Oak::View::QtWidgets {

class ListViewNode;

// =============================================================================
// Class definition
// =============================================================================
class ListView : public QFrame
{
    Q_OBJECT

public:
    ListView(QWidget *parent = nullptr);
    virtual ~ListView() override;

    void setOakModel(Model::OakModel* model);
    void setRootNode(const Model::Node& node);

    void currentNodeChanged();

    int maxDepth() const;
    void setMaxDepth(int maxDepth);

    void resizeEvent(QResizeEvent *event) override;

protected:
    ListViewNode * getViewNode(const Model::NodeIndex &nodeIndex);

    void createDragNodes() const;
    void clearDragNodes() const;

    void onNodeInserteAfter(const Model::NodeIndex &nodeIndex);
    void onNodeMoveAfter(const Model::NodeIndex &sourceNodeIndex, const Model::NodeIndex &targetNodeIndex);
    void onNodeMoveBefore(const Model::NodeIndex &sourceNodeIndex, const Model::NodeIndex &targetNodeIndex);
    void onNodeCloneAfter(const Model::NodeIndex &sourceNodeIndex, const Model::NodeIndex &targetNodeIndex);
    void onNodeRemoveBefore(const Model::NodeIndex &nodeIndex);
    void onVariantLeafChangeAfter(const Model::NodeIndex &nodeIndex);
    void onKeyLeafChangeAfter(const Model::NodeIndex &nodeIndex);

protected slots:
    void adjustNodeWidth();
    void onCurrentNodeViewDestoyed();

protected:
    Model::OakModel * m_model = nullptr;
    ListViewNode * m_rootNode = nullptr;
    Model::NodeIndexUPtr m_rootNodeIndex;

    ListViewNode * m_currentViewNode = nullptr;

    int m_maxDepth = 2;

    QScrollArea * m_scrollArea;
    QGridLayout * m_dragLayout;
};

} // namespace Oak::View::QtWidgets

