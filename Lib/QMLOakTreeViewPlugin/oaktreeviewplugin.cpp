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

#include "oaktreeviewplugin.h"

#include "OakTreeViewInternalModel.h"

#include <qqml.h>

void OakTreeViewPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
    qmlRegisterType<OakTreeViewInternalModel>("Oak.TreeView", 1, 0, "OakTreeViewInternalModel");
}
