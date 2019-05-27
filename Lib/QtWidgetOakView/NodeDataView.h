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

#include "OakModel.h"
#include "NodeEditorHandler.h"

#include <QStackedWidget>
#include <QMap>


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class NodeDataView : public QWidget
{
    Q_OBJECT
public:
    NodeDataView(QWidget* parent = nullptr);
    virtual ~NodeDataView();

    void setModel(Model::OakModel* model);

    void clearEditorCash();

    void currentNodeChanged();

    void setCurrentNode(const Model::Node& node);

    NodeEditorHandler* getEditorHandler(const Model::Node& node);

protected:
    void modelDestroyed();
    void setCurrentEditor(QWidget* editor);
    void setCurrentWidget(int index);

    void onLeafChangeAfter(const Model::NodeIndex &nodeIndex, const std::string &valueName);

protected:
    Model::OakModel* m_model = nullptr;

    QStackedWidget* m_stackedWidget;
    int m_initialWidgetCount;

    std::vector<NodeEditorHandlerUPtr> m_editorList;
};

} // namespace Oak::View::QtWidgets

