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

#include "NodeDataView.h"

#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QDebug>


namespace Oak::View::QtWidgets {

// =============================================================================
// (public)
NodeDataView::NodeDataView(QWidget* parent)
    : QWidget(parent)
{
    //qDebug() << "NodeDataView()";
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    m_stackedWidget = new QStackedWidget();

    QLabel* emptyLabel = new QLabel("Oak Model not Loaded");
    emptyLabel->setAlignment(Qt::AlignCenter);

    m_stackedWidget->addWidget(emptyLabel);
    // remove all other widgets
    while (m_stackedWidget->count() > 1) {
        m_stackedWidget->removeWidget(m_stackedWidget->widget(0));
    }

    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    m_initialWidgetCount = m_stackedWidget->count();
}

// =============================================================================
// (public)
NodeDataView::~NodeDataView()
{
    //qDebug() << "~NodeDataView()";
    setModel(nullptr);
}

// =============================================================================
// (public)
void NodeDataView::setModel(Model::OakModel* model)
{
    if (m_model == model) { return; }

    if (m_model) {
        // Disconnect the old model
        m_model->notifier_currentNodeChanged.remove(this);
        m_model->notifier_rootNodeDefChanged.remove(this);

        m_model->notifier_destroyed.remove(this);

        m_model->notifier_leafChangeAfter.remove(this);
    }

    // Change the model
    m_model = model;

    if (m_model) {
        // connect the new mobel
        m_model->notifier_currentNodeChanged.add(this, &NodeDataView::currentNodeChanged);
        m_model->notifier_rootNodeDefChanged.add(this, &NodeDataView::clearEditorCash);

        m_model->notifier_destroyed.add(this, &NodeDataView::modelDestroyed);
        m_model->notifier_leafChangeAfter.add(this, &NodeDataView::onLeafChangeAfter);

        if (!m_model->currentNode().isNull()) {
            currentNodeChanged();
        }
    }

    // todo: Reload widget if loaded
}

// =============================================================================
// (public)
void NodeDataView::clearEditorCash()
{
    setCurrentWidget(0);
    m_editorList.clear();
    for(int i = m_stackedWidget->count()-1; i >= m_initialWidgetCount; i--)
    {
        QWidget* widget = m_stackedWidget->widget(i);
        m_stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }
}

// =============================================================================
// (public)
void NodeDataView::currentNodeChanged()
{
    setCurrentNode(m_model->currentNode());
}

// =============================================================================
// (public)
void NodeDataView::setCurrentNode(const Model::Node& node)
{
    if (node.isNull()) {
        setCurrentWidget(0);
        return;
    }

    NodeEditorHandler* eHandler = getEditorHandler(node);
    if (eHandler == nullptr) { return; }

    eHandler->setNode(node.nodeData());
    QWidget* editor = eHandler->getEditor();
    setCurrentEditor(editor);
}

// =============================================================================
// (public)
NodeEditorHandler* NodeDataView::getEditorHandler(const Model::Node& node)
{
    if (node.isDefNull()) { return nullptr; }

    for (const auto& eHandler: m_editorList) {
        if (eHandler->nodeDef() == node.def()) {
            return eHandler.get();
        }
    }
    m_editorList.push_back(std::make_unique<NodeEditorHandler>(this, node));
    NodeEditorHandler* nHandler = m_editorList.back().get();
    return nHandler;
}

// =============================================================================
// (protected)
void NodeDataView::modelDestroyed()
{
    m_model = nullptr;
}

// =============================================================================
// (protected)
void NodeDataView::setCurrentEditor(QWidget* editor)
{
    for (int i = 0; i < m_stackedWidget->count(); i++) {
        if (m_stackedWidget->widget(i) == editor) {
            setCurrentWidget(i);
            return;
        }
    }
    int index = m_stackedWidget->count();
    m_stackedWidget->addWidget(editor);
    setCurrentWidget(index);
}

// =============================================================================
// (protected)
void NodeDataView::setCurrentWidget(int index)
{
    if (m_stackedWidget->currentIndex() != index) {
        m_stackedWidget->currentWidget()->hide();
        m_stackedWidget->setCurrentIndex(index);
        m_stackedWidget->currentWidget()->show();
    }
}

// =============================================================================
// (protected)
void NodeDataView::onLeafChangeAfter(const Model::NodeIndex &nodeIndex, const std::string &valueName)
{

    if (m_model->currentNodeIndex().equal(nodeIndex)) {
        // Pass on the event to the current editor
        getEditorHandler(m_model->currentNode())->updateEditorValue(valueName);
    }
}

} // namespace Oak::View::QtWidgets

