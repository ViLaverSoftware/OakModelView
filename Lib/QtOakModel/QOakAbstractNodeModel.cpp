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

#include "QOakAbstractNodeModel.h"

#include "../ServiceFunctions/Trace.h"

// =============================================================================
// (public)
QOakAbstractNodeModel::QOakAbstractNodeModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

//// =============================================================================
//// (public)
//QOakAbstractNodeModel::QOakAbstractNodeModel(const QOakAbstractNodeModel &other)
//{
//    if (other.QObject::parent()) {
//        QObject::setParent(other.QObject::parent());
//    }
//    m_node = other.m_node;
//    if (other.m_nodeIndexUPtr) {
//        m_nodeIndexUPtr = std::make_unique<Oak::Model::NodeIndex>(*other.m_nodeIndexUPtr.get());
//    }

//    m_sourceItem = other.m_sourceItem;

//    m_sourceModel = other.m_sourceModel;
//}

// =============================================================================
// (public)
QOakAbstractNodeModel::~QOakAbstractNodeModel()
{
}

// =============================================================================
// (public)
bool QOakAbstractNodeModel::isNull() const
{
    return !m_sourceItem.isValid();
}

// =============================================================================
// (public)
const Oak::Model::Node &QOakAbstractNodeModel::node() const
{
    return m_node;
}

// =============================================================================
// (public)
const Oak::Model::NodeIndex *QOakAbstractNodeModel::nodeIndex() const
{
    return m_nodeIndexUPtr.get();
}

// =============================================================================
// (public)
const QModelIndex &QOakAbstractNodeModel::sourceItem() const
{
    return m_sourceItem;
}

// =============================================================================
// (public)
const QOakModel *QOakAbstractNodeModel::sourceModel() const
{
    return m_sourceModel;
}

// =============================================================================
// (public)
const Oak::Model::OakModel *QOakAbstractNodeModel::sourceOakModel() const
{
    if (m_sourceModel == nullptr) {
        return nullptr;
    } else {
        return m_sourceModel->oakModel();
    }
}

// =============================================================================
// (public)
void QOakAbstractNodeModel::setSourceItem(QModelIndex _sourceItem)
{
    //TRACE("QOakToolBarModel::setSourceItem\n");

    // 1. The model of the index have to be the QOakModel
    const QOakModel *newModel = qobject_cast<const QOakModel*>(_sourceItem.model());

    // 2. Find the node the index refers to
    Oak::Model::Node newNode;
    if (newModel != nullptr) {
        newNode = newModel->toNode(_sourceItem);
    }

    if (newNode == m_node) { return; }

    // 3. Calculate the NodeIndex the process events faster
    Oak::Model::NodeIndexUPtr newNodeIndex = Oak::Model::NodeIndex::create(newNode);

    if (newNode.isNull()) { // If one fail all fail
        _sourceItem = QModelIndex();
        newModel = nullptr;
    }
    if (newNode.isNull() && m_node.isNull()) { return; }

    // The model source have changed and needs to be reset
    beginResetModel();

    // Only disconnect/connect notifiers if model changed
    bool modelChanged = newNode.model() != m_node.model();

    if (modelChanged && sourceOakModel() != nullptr) {
        // Disconnect notifiers from previous connected model
        sourceOakModel()->notifier_destroyed.remove(this);
        sourceModelDisconnect();
    }

    // Change the source model
    m_sourceModel = newModel;
    m_sourceItem = _sourceItem;
    m_node = newNode;
    m_nodeIndexUPtr = std::move(newNodeIndex);
    sourceItemChanged();

    if (modelChanged) {
        // Connect notifiers to the new model
        sourceOakModel()->notifier_destroyed.add(this, &QOakAbstractNodeModel::clearModel);
        sourceModelConnect();
    }

    emit sourceItemChanged(m_sourceItem);
    resetInternalData();
    endResetModel();
}

// =============================================================================
// (public)
void QOakAbstractNodeModel::clearModel()
{
    beginResetModel();

    m_sourceItem = QModelIndex();
    m_sourceModel = nullptr;
    m_node = Oak::Model::Node();
    m_nodeIndexUPtr = Oak::Model::NodeIndexUPtr();

    emit sourceItemChanged(m_sourceItem);
    resetInternalData();
    endResetModel();
}

// =============================================================================
// (public)
void QOakAbstractNodeModel::sourceItemChanged()
{
    // Optional virtual function
}
