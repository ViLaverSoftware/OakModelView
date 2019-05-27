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

#include "QServiceFunctions.h"

// =============================================================================
// (global)
Oak::Model::Color toOakColor(const QColor& v1)
{
    return Oak::Model::Color(v1.red(), v1.green(), v1.blue(), v1.alpha());
}

// =============================================================================
// (global)
QColor toQColor(const Oak::Model::Color& v1)
{
    return QColor(v1.red(), v1.green(), v1.blue(), v1.alpha());
}

// =============================================================================
// (global)
std::vector<std::string> toStdStringList(const QStringList& list1)
{
    std::vector<std::string> list2;
    list2.reserve(static_cast<size_t>(list1.size()));
    foreach (const QString& str, list1) {
        list2.push_back(str.toStdString());
    }

    return list2;
}

// =============================================================================
// (global)
QStringList toQStringList(const std::vector<std::string>& list1)
{
    QStringList list2;
    list2.reserve(static_cast<int>(list1.size()));
    for (const std::string& str: list1) {
        list2.push_back(QString::fromStdString(str));
    }

    return list2;
}

// =============================================================================
// (global)
Oak::Model::UnionValue toUnionValue(const QVariant& v1)
{
    switch (v1.type()) {
    case QVariant::Type::Invalid: {
        return Oak::Model::UnionValue();
    }
    case QVariant::Type::Bool: {
        return Oak::Model::UnionValue(v1.toBool());
    }
    case QVariant::Type::Int: {
        return Oak::Model::UnionValue(v1.toInt());
    }
    case QVariant::Type::Double: {
        return Oak::Model::UnionValue(v1.toDouble());
    }
    case QVariant::Type::String: {
        return Oak::Model::UnionValue(v1.toString().toStdString());
    }
    case QVariant::Type::DateTime: {
        Oak::Model::DateTime dt;
        dt.setMSecsSinceEpoch(v1.toDateTime().toMSecsSinceEpoch());
        return Oak::Model::UnionValue(dt);
    }
    default: {
        assert(true);
        return Oak::Model::UnionValue();
    }
    }
}

// =============================================================================
// (global)
QVariant toQVariant(const Oak::Model::UnionValue& v1)
{
    QVariant v2;
    switch (v1.type()) {
    case Oak::Model::UnionType::Undefined:{
        return QVariant();
    }
    case Oak::Model::UnionType::Char:{
        return QVariant(v1.value<char*>());
    }
    case Oak::Model::UnionType::Bool:{
        return QVariant(v1.value<bool>());
    }
    case Oak::Model::UnionType::Integer:{
        return QVariant(v1.value<int>());
    }
    case Oak::Model::UnionType::Double:{
        return QVariant(v1.value<double>());
    }
    case Oak::Model::UnionType::String:{
        return QVariant(QString::fromStdString(v1.value<std::string>()));
    }
    case Oak::Model::UnionType::DateTime:{
        QDateTime dt;
        dt.setMSecsSinceEpoch(v1.value<Oak::Model::DateTime>().mSecsSinceEpoch());
        return QVariant::fromValue(dt);
    }
    default: {
        assert(false);
        return QVariant();
    }
    }
}

// =============================================================================
// (global)
Oak::Model::UnionValueList toUnionValueList(const QVariantList& vList)
{
    Oak::Model::UnionValueList list;
    list.reserve(static_cast<size_t>(vList.size()));
    foreach (const QVariant& v, vList) {
        list.push_back(toUnionValue(v));
    }

    return list;
}

// =============================================================================
// (global)
QVariantList toQVariantList(const Oak::Model::UnionValueList& sList)
{
    QVariantList list;
    list.reserve(static_cast<int>(sList.size()));
    for (const Oak::Model::UnionValue& v: sList) {
        list.push_back(toQVariant(v));
    }

    return list;
}
