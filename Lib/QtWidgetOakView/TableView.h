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

#include <QTableWidget>
#include <QToolBar>

#include "OakModel.h"
#include "TableQuery.h"


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class TableView : public QWidget
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    virtual ~TableView() override;

    void setBaseRef(Model::NodeQueryUPtr baseRef);
    void addValueRef(Model::LeafQuerySPtr valueRef);

    void updateTable();

    void setOakModel(Model::OakModel* model);

protected slots:
    void onSelectionChanged();

    void onActionAdd();
    void onActionDelete();
    void onActionUp();
    void onActionDown();
    void onActionCut();
    void onActionCopy();
    void onActionPaste();

    void onNodeChanged(QTableWidgetItem *node);

protected:
    void onNodeInserteAfter(const Model::NodeIndex &nodeIndex);
    void onNodeMoveAfter(const Model::NodeIndex &sourceNodeIndex, const Model::NodeIndex &targetNodeIndex);
    void onNodeCloneAfter(const Model::NodeIndex &sourceNodeIndex, const Model::NodeIndex &targetNodeIndex);
    void onNodeRemoveBefore(const Model::NodeIndex& tNodeIndex);
    void onEntryChangeAfter(const Model::NodeIndex &nodeIndex, const std::string &valueName);

    virtual bool event(QEvent *event) override;

    void disableAllActions();
    void updateAllActions();

    QList<int> selectedRows() const;

protected:
    Model::OakModel * m_model = nullptr;
    Model::Node m_rootNode;

    Model::TableQuery m_tableQuery;

    QTableWidget *m_tableWidget;
    QToolBar *m_toolBar;

    QAction * m_actionAdd;
    QAction * m_actionDelete;
    QAction * m_actionUp;
    QAction * m_actionDown;
    QAction * m_actionCut;
    QAction * m_actionCopy;
    QAction * m_actionPaste;

    QList<Model::Node> m_cutNodes;
    QList<Model::Node> m_copyNodes;
};

} // namespace Oak::View::QtWidgets

