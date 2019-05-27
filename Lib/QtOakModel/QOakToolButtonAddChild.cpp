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

#include "QOakToolButtonAddChild.h"

#include "QOakToolbarModel.h"

#include <QIcon>

// =============================================================================
// (public)
QOakToolButtonAddChild::QOakToolButtonAddChild(QObject *parent)
    : QOakToolButton(parent)
{

}

// =============================================================================
// (public)
int QOakToolButtonAddChild::count() const
{
    if (m_toolBarModel->node().isNull()) { return 0; }
    return m_toolBarModel->node().def()->containerCount();
}

// =============================================================================
// (public)
QVariant QOakToolButtonAddChild::data(int index, int role) const
{
    const Oak::Model::NodeDef * cDef = m_toolBarModel->node().def()->childDef(index);

    switch(role)
    {
    case Qt::DisplayRole:
        return QString::fromStdString(cDef->name());
    case Qt::ToolTipRole: {
        QString toolTip = tr("Add child ") + cDef->displayName().c_str();
        return toolTip;
    }
    case QOakToolBarModel::ImagePath:
        return "add_32.png";
    case QOakToolBarModel::Color:
        if (cDef->hasColor()) {
            Oak::Model::Color color = cDef->color();
            return toQColor(color);
        }
        break;
    case QOakToolBarModel::Enabled:
        int i = -1;
        return m_toolBarModel->node().canInsertChild(cDef->name(), i);
    }
    return QVariant();
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::sourceModelConnect()
{
    const auto *model = m_toolBarModel->sourceOakModel();
    model->notifier_nodeInserteAfter.add(this, &QOakToolButtonAddChild::onNodeInserteAfter);
    model->notifier_nodeRemoveAfter.add(this, &QOakToolButtonAddChild::onNodeRemoveAfter);
    model->notifier_nodeMoveAfter.add(this, &QOakToolButtonAddChild::onNodeMoveAfter);
    model->notifier_nodeCloneAfter.add(this, &QOakToolButtonAddChild::onNodeCloneAfter);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::sourceModelDisconnect()
{
    const auto *model = m_toolBarModel->sourceOakModel();
    model->notifier_nodeInserteAfter.remove(this);
    model->notifier_nodeRemoveAfter.remove(this);
    model->notifier_nodeMoveAfter.remove(this);
    model->notifier_nodeCloneAfter.remove(this);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::trigger(int index)
{
    const std::string &name = m_toolBarModel->node().def()->container(index).containerDef()->name();
    int i = -1;
    m_toolBarModel->node().insertChild(name, i);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::onNodeInserteAfter(const Oak::Model::NodeIndex &nodeIndex)
{
    // Node index not set
    if (!m_toolBarModel || !m_toolBarModel->nodeIndex()) { return; }
    // Do nothing if the change is not related to the child of the node
    if (m_toolBarModel->nodeIndex()->depth()+1 != nodeIndex.depth()) { return; }
    if (!nodeIndex.contains(*m_toolBarModel->nodeIndex())) { return; }

    // Find the button that might have changed
    int index = m_toolBarModel->node().def()->containerIndex(nodeIndex.lastNodeIndex().name());
    if (index == -1) { return; }

    // Emit the signal that the button have changed(it might not have...)
    emit buttonChanged(index, QVector<int>() << QOakToolBarModel::Enabled);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::onNodeRemoveAfter(const Oak::Model::NodeIndex &nodeIndex)
{
    // Node index not set
    if (!m_toolBarModel || !m_toolBarModel->nodeIndex()) { return; }
    // Do nothing if the change is not related to the child of the node
    if (m_toolBarModel->nodeIndex()->depth()+1 != nodeIndex.depth()) { return; }
    if (!nodeIndex.contains(*m_toolBarModel->nodeIndex())) { return; }

    // Find the button that might have changed
    int index = m_toolBarModel->node().def()->containerIndex(nodeIndex.lastNodeIndex().name());
    if (index == -1) { return; }

    // Emit the signal that the button have changed(it might not have...)
    emit buttonChanged(index, QVector<int>() << QOakToolBarModel::Enabled);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::onNodeMoveAfter(const Oak::Model::NodeIndex &sourceNodeIndex, const Oak::Model::NodeIndex &targetNodeIndex)
{
   // Node index not set
   if (!m_toolBarModel || !m_toolBarModel->nodeIndex()) { return; }
   // Ignore move if source and target parents are equal
   if (sourceNodeIndex.depthWhereEqual(targetNodeIndex) + 1 == sourceNodeIndex.depth())
   // Do nothing if the change is not related to the child of the node
   if (m_toolBarModel->nodeIndex()->depth()+1 != targetNodeIndex.depth()) { return; }
   if (!targetNodeIndex.contains(*m_toolBarModel->nodeIndex())) { return; }

   // Find the button that might have changed
   int index = m_toolBarModel->node().def()->containerIndex(targetNodeIndex.lastNodeIndex().name());
   if (index == -1) { return; }

   // Emit the signal that the button have changed(it might not have...)
   emit buttonChanged(index, QVector<int>() << QOakToolBarModel::Enabled);
}

// =============================================================================
// (public)
void QOakToolButtonAddChild::onNodeCloneAfter(const Oak::Model::NodeIndex &sourceNodeIndex, const Oak::Model::NodeIndex &targetNodeIndex)
{
    Q_UNUSED(sourceNodeIndex)

    // Node index not set
   if (!m_toolBarModel || !m_toolBarModel->nodeIndex()) { return; }
   // Do nothing if the change is not related to the child of the node
   if (m_toolBarModel->nodeIndex()->depth()+1 != targetNodeIndex.depth()) { return; }
   if (!targetNodeIndex.contains(*m_toolBarModel->nodeIndex())) { return; }

   // Find the button that might have changed
   int index = m_toolBarModel->node().def()->containerIndex(targetNodeIndex.lastNodeIndex().name());
   if (index == -1) { return; }

   // Emit the signal that the button have changed(it might not have...)
   emit buttonChanged(index, QVector<int>() << QOakToolBarModel::Enabled);
}
