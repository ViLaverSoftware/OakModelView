/**
 * oakmodelview - version 0.1.0
 * --------------------------------------------------------
 * Copyright (C) 2017, by Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * Report bugs and download new versions at http://oakmodelview.com/
 *
 * This library is distributed under the MIT License.
 * See accompanying file LICENSE in the root folder.
 */

#pragma once

#include <QWidget>

#include "Item.h"


class QVBoxLayout;
class QPushButton;
class QFrame;
class QLabel;

namespace Oak {
namespace View {

class ListView;

// =============================================================================
// Class definition
// =============================================================================

class ListViewItem : public QWidget
{
    Q_OBJECT
public:
    ListViewItem(ListView * listView, const Model::Item &item, int depth);

    const Model::Item& item() const;

    ListViewItem * child(const Model::Item &item);
    int childViewItemIndex(const ListViewItem * childViewItem);

    bool isExspanded() const;
    void setExspanded(bool value);

    virtual QSize sizeHint() const override;

    void onItemInserted(int index);
    void onItemRemoved(int index);

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    void clearCurrent();
    void setCurrent();

    void updateLabel();

protected:
    QString currentStylesheet(QColor color);
    void updateFixedheight();

protected slots:
    void onHeightChanged(int change);
    void onExspandChanged();

signals:
    void heightChanged(int change);

protected:
    int m_height;
    int m_depth;
    int m_childCount = 0;

    ListView * m_listView;
    Model::Item m_item;

    QFrame * m_itemFrame = nullptr;
    QLabel * m_label = nullptr;
    QPushButton * m_exspandbuttom = nullptr;

    QWidget * m_childItemWidget = nullptr;
    QVBoxLayout * m_childItemLayout = nullptr;

};

} // namespace View
} // namespace Oak
