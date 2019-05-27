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

#include "ContainerEditor.h"
#include "Node.h"

#include <QObject>

#include <memory>


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class ContainerEditorHandler : public QObject
{
    Q_OBJECT
public:
    ContainerEditorHandler(const Model::Node &node, const std::string &name, QObject *parent = nullptr);

    QString listDisplayName() const;
    int nodeCount() const;
    QStringList nodeIdList() const;

    bool canInsert(int index) const;
    bool canRemove(int index) const;

    QWidget* getEditor();
    bool setNode(const Model::NodeData& nodeData);
    void updateEditor();
    void clearEditor();

protected:
    void createEditor();

protected slots:
    void onEditorDestroyed();
    void onEntryClicked(int index);
    void onEntryInsert(int index);
    void onEntryRemove(int index);

protected:

    Model::Node m_node;
    std::string m_name;
    QWidget* m_editor = nullptr;
};

} // namespace Oak::View::QtWidgets

