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

#include <QtQml/QQmlListProperty>

#include "QOakAbstractNodeModel.h"
#include "QOakModel.h"
#include "QOakToolButton.h"

// =============================================================================
// Class definition
// =============================================================================
class QOakToolBarModel : public QOakAbstractNodeModel
{
    Q_OBJECT

    AUTO_PROPERTY_OBJECT_LIST(QOakToolBarModel, QOakToolButton, buttons, button)

public:
    enum Roles  {
        ImagePath = Qt::UserRole + 11,
        Color = Qt::UserRole + 12,
        Enabled = Qt::UserRole + 13
    };
    Q_ENUM(Roles)

    QOakToolBarModel(QObject *parent = nullptr);

public slots:
    void trigger(int index);

protected:
    virtual void sourceModelConnect() override;
    virtual void sourceModelDisconnect() override;
    virtual void sourceItemChanged() override;

protected slots:
    void onToolButtonChange(int index, QVector<int> roles);

public:
    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual int columnCount(const QModelIndex& parent) const override;
    virtual bool hasChildren(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;


    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

};



