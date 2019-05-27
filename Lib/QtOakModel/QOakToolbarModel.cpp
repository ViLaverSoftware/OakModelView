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

#include "QOakToolbarModel.h"

#include "../ServiceFunctions/Trace.h"

// =============================================================================
// (public)
QOakToolBarModel::QOakToolBarModel(QObject *parent)
    : QOakAbstractNodeModel(parent)
{

}
// =============================================================================
// (public slots)
void QOakToolBarModel::trigger(int index)
{
    //TRACE("ToolButton triggered: %i\n", index);
    for (QOakToolButton *button: a_buttons)
    {
        if (index < button->count()) {
            button->trigger(index);
            return;
        }
        index -= button->count();
    }
}

// =============================================================================
// (public)
void QOakToolBarModel::sourceModelConnect()
{
    for (QOakToolButton *button: a_buttons)
    {
        connect(button, SIGNAL(buttonChanged(int, QVector<int>)), this, SLOT(onToolButtonChange(int, QVector<int>)));
        button->sourceModelConnect();
    }
}

// =============================================================================
// (public)
void QOakToolBarModel::sourceModelDisconnect()
{
    for (QOakToolButton *button: a_buttons)
    {
        button->sourceModelDisconnect();
        disconnect(button, SIGNAL(buttonChanged(int, QVector<int>)), this, SLOT(onToolButtonChange(int, QVector<int>)));
    }
}

// =============================================================================
// (public)
void QOakToolBarModel::sourceItemChanged()
{
    for (QOakToolButton *button: a_buttons)
    {
        button->setToolBarModel(this);
    }
}

// =============================================================================
// (public)
QModelIndex QOakToolBarModel::index(int row, int column, const QModelIndex &parent) const
{
    if (isNull()) { return QModelIndex(); }
    if (parent.isValid()) { return QModelIndex(); }

    return createIndex(row, column);
}

// =============================================================================
// (public)
QModelIndex QOakToolBarModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

// =============================================================================
// (public)
int QOakToolBarModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (isNull()) { return 0; }

    int count = 0;
    for(const QOakToolButton *button: a_buttons)
    {
        count += button->count();
    }
    return count;
}

// =============================================================================
// (public)
int QOakToolBarModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (isNull()) { return 0; }
    return 1;
}

// =============================================================================
// (public)
bool QOakToolBarModel::hasChildren(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return false;
}

// =============================================================================
// (public)
QVariant QOakToolBarModel::data(const QModelIndex &index, int role) const
{
    //TRACE("data(%i, %i)\n", index.row(), role);
    if (isNull()) { return QVariant(); }
    if (!index.isValid()) { return QVariant(); }

    int i = index.row();
    for(const auto& button: a_buttons)
    {
        if (i < button->count())
        {
            return button->data(i, role);
        }
        i -= button->count();
    }

    return QVariant();
}

// =============================================================================
// (public)
Qt::ItemFlags QOakToolBarModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::NoItemFlags;
}

// =============================================================================
// (public)
QHash<int, QByteArray> QOakToolBarModel::roleNames() const
{
    QHash<int, QByteArray> result = QAbstractItemModel::roleNames();
    result.insert(QOakToolBarModel::ImagePath, QByteArrayLiteral("imagePath"));
    result.insert(QOakToolBarModel::Color, QByteArrayLiteral("color"));
    result.insert(QOakToolBarModel::Enabled, QByteArrayLiteral("enabled"));
    return result;
}

// =============================================================================
// (protected)
void QOakToolBarModel::onToolButtonChange(int index, QVector<int> roles)
{
    QOakToolButton *button = qobject_cast<QOakToolButton*>(sender());
    if (button == nullptr) { return; }

    // Find the model row from the local button index
    for(const auto& b: a_buttons) {
        if (b == button) { break; }
        index += b->count();
    }

    QModelIndex mIndex = createIndex(index, 0);
    dataChanged(mIndex, mIndex, roles);
}
