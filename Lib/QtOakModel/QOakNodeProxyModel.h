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

#include "QOakAbstractNodeModel.h"

// =============================================================================
// Class definition
// =============================================================================
class QOakNodeProxyModel : public QOakAbstractNodeModel
{
    Q_OBJECT

public:
    enum Roles  {
        DisplayName = Qt::UserRole + 10,
        LeafValidator = Qt::UserRole + 11,
        HasOptions = Qt::UserRole + 12,
        OptionsOnly = Qt::UserRole + 13,
        Options = Qt::UserRole +14,
        Unit = Qt::UserRole +15,
        Required = Qt::UserRole + 16
    };

    QOakNodeProxyModel(QObject *parent = nullptr);
    virtual ~QOakNodeProxyModel() override;

    // Basic functiona6lity:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    virtual QModelIndex sibling(int row, int column, const QModelIndex& index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool hasChildren(const QModelIndex& parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    const Oak::Model::Leaf& toLeaf(const QModelIndex &index) const;

protected:
    virtual void sourceModelConnect() override;
    virtual void sourceModelDisconnect() override;
    virtual void sourceItemChanged() override;

    void onLeafValueChanged(const Oak::Model::NodeIndex& nIndex, const std::string &str);
    void onVariantLeafChanged(const Oak::Model::NodeIndex& nIndex);
};
