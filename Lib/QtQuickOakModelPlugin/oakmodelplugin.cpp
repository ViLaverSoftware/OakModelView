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

#include "oakmodelplugin.h"

#include "QOakBaseTypes.h"

#include "QContainerDefBuilderData.h"
#include "QNodeDefBuilderData.h"
#include "QOakModel.h"
#include "QOakNodeProxyModel.h"
#include "QOakModelBuilderData.h"

#include "QLeafDefBuilderData.h"
#include "QValueOptionsBuilderData.h"
#include "QOakToolbarModel.h"
#include "QOakToolButtonAddChild.h"
#include "QOakToolButtonRemove.h"

#include <qqml.h>

void OakModePlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
    qmlRegisterType<QTriState>("Oak.Model", 1, 0, "TriState");

    qmlRegisterType<QContainerDefBuilderData>("Oak.Model", 1, 0, "ContainerDef");
    qmlRegisterType<QNodeDefBuilderData>("Oak.Model", 1, 0, "NodeDef");
    qmlRegisterType<QOakModel>("Oak.Model", 1, 0, "OakModel");
    qmlRegisterType<QOakNodeProxyModel>("Oak.Model", 1, 0, "OakNodeProxyModel");
    qmlRegisterType<QOakModelBuilderData>("Oak.Model", 1, 0, "OakModelBuilder");
    qmlRegisterType<QLeafDefBuilderData>("Oak.Model", 1, 0, "LeafDef");
    qmlRegisterType<QLeafSettingsBuilderData>("Oak.Model", 1, 0, "LeafSettings");
    qmlRegisterType<QValueOptionsBuilderData>("Oak.Model", 1, 0, "ValueOptions");
    qmlRegisterType<QOakToolBarModel>("Oak.Model", 1, 0, "OakToolBarModel");
    qmlRegisterType<QOakToolButton>("Oak.Model", 1, 0, "OakToolButton");
    qmlRegisterType<QOakToolButtonAddChild>("Oak.Model", 1, 0, "OakToolButtonAddChild");
    qmlRegisterType<QOakToolButtonRemove>("Oak.Model", 1, 0, "OakToolButtonRemove");
}
