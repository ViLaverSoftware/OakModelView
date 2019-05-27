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

#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>

#include "ContainerDef.h"


namespace Oak::View::QtWidgets {

class ContainerEditorHandler;

// =============================================================================
// Class definition
// =============================================================================
class ContainerEditor : public QWidget
{
    Q_OBJECT
public:
    ContainerEditor(ContainerEditorHandler* eHandler, QWidget *parent = nullptr);

    void updateEditor();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

    void addEntry(const QString& text);
    void removeLastEntry();
    int entryIndex(QObject* obj) const;
    void createContextMenu(const QPoint& globalPos, int index);

protected slots:
    void onEntryAdded();

signals:
    void entryClicked(int index);
    void entryInserted(int index);
    void entryRemoved(int index);
    void entryAdded();

protected:
    ContainerEditorHandler* m_eHandler;
    QWidget* m_listWidget;
    QPushButton* m_addButton;
    QGridLayout* m_listLayout;
    QGroupBox* m_groupBox;

    int m_count;
};

} // namespace Oak::View::QtWidgets

