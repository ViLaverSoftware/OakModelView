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

#include "OakModel.h"
#include "NodeEditorHandler.h"

#include <QStackedWidget>
#include <QMap>
#include <QTreeWidget>


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class OakView : public QTreeWidget
{
    Q_OBJECT
public:
    OakView(QWidget* parent = nullptr);
    virtual ~OakView() override;

    void setOakModel(Model::OakModel* model);

    void currentNodeChanged();

    void setCurrentNode(const Model::NodeIndex &nodeIndex);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent * event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent * event) override;
    virtual void dragMoveEvent(QDragMoveEvent * event) override;
    virtual void dropEvent(QDropEvent * event) override;
    virtual void startDrag(Qt::DropActions supportedActions) override;

protected:
    void modelDestroyed();
    void clearTreeStructure();
    void updateTreeStructure();

    QTreeWidgetItem * getTreeNodes(const Model::Node &node, QTreeWidgetItem *parentNode = nullptr);

    void onNodeInserteAfter(const Model::NodeIndex& nodeIndex);
    void onNodeMoveAfter(const Model::NodeIndex& sourceNodeIndex, const Model::NodeIndex& targetNodeIndex);
    void onNodeCloneAfter(const Model::NodeIndex& sourceNodeIndex, const Model::NodeIndex& targetNodeIndex);
    void onNodeRemoveBefore(const Model::NodeIndex& nodeIndex);

    void onVariantLeafChangeAfter(const Model::NodeIndex& nodeIndex);
    void onKeyLeafChangeAfter(const Model::NodeIndex& nodeIndex);

    QTreeWidgetItem * widgetFromIndex(const Model::NodeIndex &nodeIndex, bool parentWidget = false);
    Model::NodeIndexUPtr indexFromWidget(QTreeWidgetItem *nodeWidget);

protected slots:
    void createTreeStructure();
    void onCurrentQNodeChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);

protected:
    Model::OakModel* m_model = nullptr;

    // Drag & drop
    QStringList m_acceptedDropNames;
    //XMLElementAbstractPtr m_dragSource;
    QPoint m_mousePressedPosition;
    Model::Node m_dragNode;
};

} // namespace Oak::View::QtWidgets

