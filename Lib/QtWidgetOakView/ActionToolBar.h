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

#include <QToolBar>

#include "OakModel.h"

class QAction;


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class ActionToolBar : public QToolBar
{
    Q_OBJECT
public:
    ActionToolBar(QWidget * parent = nullptr);

    void setModel(Model::OakModel* model);

protected:
    void currentNodeChanged();
    void nodeRemoveBefore(const Model::NodeIndex &nodeIndex);

    void disableAllActions();

protected slots:
    void onActionInsert();
    void onActionDelete();
    void onActionUp();
    void onActionDown();
    void onActionCut();
    void onActionCopy();
    void onActionPaste();

protected:
    Model::OakModel* m_model = nullptr;

    Model::Node m_cutNode;
    Model::Node m_copyNode;

    QAction * m_actionInsert;
    QAction * m_actionDelete;
    QAction * m_actionUp;
    QAction * m_actionDown;
    QAction * m_actionCut;
    QAction * m_actionCopy;
    QAction * m_actionPaste;
};

} // namespace Oak::View::QtWidgets

