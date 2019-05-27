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

#include <QOakModel.h>

// =============================================================================
// Class definition
// =============================================================================
class QOakAbstractNodeModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(QModelIndex sourceItem READ sourceItem WRITE setSourceItem NOTIFY sourceItemChanged)

public:
    QOakAbstractNodeModel(QObject *parent = nullptr);
    //QOakAbstractNodeModel(const QOakAbstractNodeModel &other);
    virtual ~QOakAbstractNodeModel() override;

    virtual bool isNull() const;

    const Oak::Model::Node &node() const;
    const Oak::Model::NodeIndex *nodeIndex() const;
    const QModelIndex &sourceItem() const;

    const QOakModel *sourceModel() const;
    const Oak::Model::OakModel *sourceOakModel() const;

public slots:
    void setSourceItem(QModelIndex _sourceItem);

protected:
    void clearModel();
    virtual void sourceModelConnect() = 0;
    virtual void sourceModelDisconnect() = 0;
    virtual void sourceItemChanged();

signals:
    void sourceItemChanged(QModelIndex sourceItem);

protected:
    Oak::Model::Node m_node;
    Oak::Model::NodeIndexUPtr m_nodeIndexUPtr;
    QModelIndex m_sourceItem;

    const QOakModel * m_sourceModel = nullptr;
};

