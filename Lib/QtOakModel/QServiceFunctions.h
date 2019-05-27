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

#include <QStringList>
#include <QVariantList>
#include <vector>
#include <string>
#include <QDateTime>
#include <QColor>

#include "UnionValue.h"
#include "Color.h"

Oak::Model::Color toOakColor(const QColor& v1);
QColor toQColor(const Oak::Model::Color& v1);

std::vector<std::string> toStdStringList(const QStringList& list1);
QStringList toQStringList(const std::vector<std::string>& list1);

Oak::Model::UnionValue toUnionValue(const QVariant& v1);
QVariant toQVariant(const Oak::Model::UnionValue& v1);

Oak::Model::UnionValueList toUnionValueList(const QVariantList& vList);
QVariantList toQVariantList(const Oak::Model::UnionValueList& sList);
