#pragma once

#include <QTableWidget>
#include <QToolBar>

#include "OakModel.h"
#include "TableQuery.h"

namespace Oak {
namespace View {

// =============================================================================
// Class definition
// =============================================================================
class TableView : public QWidget
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    virtual ~TableView() override;

    void setBaseRef(Model::ItemQueryUPtr baseRef);
    void addValueRef(Model::EntryQuerySPtr valueRef);

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

    void onItemChanged(QTableWidgetItem *item);

protected:
    void onItemInserteAfter(const Model::ItemIndex &itemIndex);
    void onItemMoveAfter(const Model::ItemIndex &sourceItemIndex, const Model::ItemIndex &targetItemIndex);
    void onItemCloneAfter(const Model::ItemIndex &sourceItemIndex, const Model::ItemIndex &targetItemIndex);
    void onItemRemoveBefore(const Model::ItemIndex& tItemIndex);
    void onEntryChangeAfter(const Model::ItemIndex &itemIndex, const std::string &valueName);

    virtual bool event(QEvent *event) override;

    void disableAllActions();
    void updateAllActions();

    QList<int> selectedRows() const;

protected:
    Model::OakModel * m_model = nullptr;
    Model::Item m_rootItem;

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

    QList<Model::Item> m_cutItems;
    QList<Model::Item> m_copyItems;
};

} // namespace View
} // namespace Oak
