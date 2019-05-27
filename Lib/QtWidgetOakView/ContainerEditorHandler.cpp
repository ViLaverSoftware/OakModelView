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

#include "ContainerEditorHandler.h"

#include "NodeDef.h"

#include <QPushButton>


namespace Oak::View::QtWidgets {

// =============================================================================
// (public)
ContainerEditorHandler::ContainerEditorHandler(const Model::Node &node, const std::string &name, QObject* parent)
    : QObject(parent), m_node(node), m_name(name)
{

}

// =============================================================================
// (public)
QString ContainerEditorHandler::listDisplayName() const
{
    return QString::fromStdString(m_node.def()->childDef(m_name)->displayName(true));
}

// =============================================================================
// (public)
int ContainerEditorHandler::nodeCount() const
{
    return m_node.childCount(m_name);
}

// =============================================================================
// (public)
QStringList ContainerEditorHandler::nodeIdList() const
{
    int count = m_node.childCount(m_name);
    QStringList nIdList;
    std::string keyValue;
    QString lName = listDisplayName();
    QString nodeId;
    for (int i = 0; i < count; i++)
    {
        Model::Node cNode = m_node.childAt(m_name, i);
        if (cNode.hasKey()) {
            cNode.keyLeaf().value().get(keyValue);
            nodeId = QString::fromStdString(keyValue);
        } else {
            nodeId = QString::number(i+1);
        }
        //eList.append(QString("%1[%2]").arg(lName).arg(entryId));
        nIdList.append(QString("%1").arg(nodeId));
    }

    return nIdList;
}

// =============================================================================
// (public)
bool ContainerEditorHandler::canInsert(int index) const
{
    return m_node.canInsertChild(m_name, index);
}

// =============================================================================
// (public)
bool ContainerEditorHandler::canRemove(int index) const
{
    return m_node.canRemoveChild(m_name, index);
}

// =============================================================================
// (public)
QWidget* ContainerEditorHandler::getEditor()
{
    createEditor();
    return m_editor;
}

// =============================================================================
// (public)
bool ContainerEditorHandler::setNode(const Model::NodeData& nodeData)
{
    if (!m_node.def()->validate(nodeData)) { return false; }

    m_node = Model::Node(m_node.def(), nodeData, m_node.model());

    updateEditor();

    return true;
}

// =============================================================================
// (public)
void ContainerEditorHandler::updateEditor()
{
    if (m_editor == nullptr) { return; }

    // Todo: Update the Editor...
    ContainerEditor* cEditor = dynamic_cast<ContainerEditor*>(m_editor);
    if (cEditor != nullptr) {
        cEditor->updateEditor();
    }
}

// =============================================================================
// (public)
void ContainerEditorHandler::clearEditor()
{
    if (m_editor) {
        if (m_editor->parent() == nullptr) {
            // Delete the editor if it has no parent
            delete m_editor;
        } else {
            // Disconnect any signal from the m_editor to this object
            disconnect(m_editor, nullptr, this, nullptr);
        }
        m_editor = nullptr;
    }
}

// =============================================================================
// (protected)
void ContainerEditorHandler::createEditor()
{
    if (m_editor != nullptr) { return; }

    ContainerEditor* cEditor = new ContainerEditor(this);
    connect(cEditor, SIGNAL(destroyed(QObject*)), this, SLOT(onEditorDestroyed()));
    connect(cEditor, SIGNAL(entryClicked(int)), this, SLOT(onEntryClicked(int)));
    connect(cEditor, SIGNAL(entryInserted(int)), this, SLOT(onEntryInsert(int)));
    connect(cEditor, SIGNAL(entryRemoved(int)), this, SLOT(onEntryRemove(int)));

    m_editor = cEditor;
    updateEditor();
}

// =============================================================================
// (protected slots)
void ContainerEditorHandler::onEditorDestroyed()
{
    m_editor = nullptr;
}

// =============================================================================
// (protected slots)
void ContainerEditorHandler::onEntryClicked(int index)
{
    m_node.childAt(m_name, index).setCurrent();
}

// =============================================================================
// (protected slots)
void ContainerEditorHandler::onEntryInsert(int index)
{
    m_node.insertChild(m_name, index);
    updateEditor();
}

// =============================================================================
// (protected slots)
void ContainerEditorHandler::onEntryRemove(int index)
{
    m_node.removeChild(m_name, index);
    updateEditor();
}

} // namespace Oak::View::QtWidgets

