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

#include "QOakToolButton.h"

#include "QOakToolbarModel.h"
#include "QServiceFunctions.h"

#include "../ServiceFunctions/Trace.h"

#include <QIcon>

// =============================================================================
// (public)
QOakToolButton::QOakToolButton(QObject *parent)
    : QObject(parent)
{

}

// =============================================================================
// (public)
QOakToolButton::~QOakToolButton()
{

}

// =============================================================================
// (public)
int QOakToolButton::count() const
{
    return 1;
}

// =============================================================================
// (public)
QVariant QOakToolButton::data(int index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
}

// =============================================================================
// (public)
void QOakToolButton::sourceModelConnect()
{
}

// =============================================================================
// (public)
void QOakToolButton::sourceModelDisconnect()
{
}

// =============================================================================
// (public)
void QOakToolButton::setToolBarModel(const QOakToolBarModel *toolBarModel)
{
    m_toolBarModel = toolBarModel;
}

// =============================================================================
// (public)
void QOakToolButton::trigger(int index)
{
    Q_UNUSED(index)
    TRACE("Remember to implement the trigger function in your QOakToolButton\n");
}
