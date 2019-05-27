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

#include "NodeData.h"
#include "Leaf.h"
#include "LeafDef.h"

#include <QObject>


namespace Oak::View::QtWidgets {

// =============================================================================
// Class definition
// =============================================================================
class ValueEditorHandler : public QObject
{
    Q_OBJECT
public:
    ValueEditorHandler(QObject *parent, Model::Leaf leaf);
    virtual ~ValueEditorHandler();

    ValueEditorHandler& operator=(const ValueEditorHandler& copy) = delete;

    QWidget* getLabel();
    QWidget* getEditor();

    void setNode(const Model::NodeData& nodeData);

    void updateLabelValue();
    void updateEditorValue();
    void getEditorValue();

    void clearWidgets();
    void clearLabel();
    void clearEditor();

protected:
    virtual void createLabel();
    virtual void createEditor();
    void setValue(const Model::UnionRef& value);

protected slots:
    void onValueEdited();
    void onEditingFinished();

    void onLabelDestroyed();
    void onEditorDestroyed();

signals:
    void valueEditedFinished();

protected:
    Model::Leaf m_leaf;
    QWidget* m_label = nullptr;
    QWidget* m_editor = nullptr;
};

} // namespace Oak::View::QtWidgets

