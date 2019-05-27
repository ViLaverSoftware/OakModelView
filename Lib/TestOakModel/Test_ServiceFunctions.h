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

#include "NodeDefinition.h"

using namespace Oak::Model;

static std::string nodeId_oakModel("oakModel");
static std::string nodeId_model("model");
static std::string nodeId_data("data");
static std::string nodeId_nodeDef("nodeDefinition");
static std::string nodeId_valueDef("valueDefinition");
static std::string nodeId_node("node");

static std::string valueId_name("name");
static std::string valueId_idName("idName");
static std::string valueId_type("type");
static std::string valueId_value("value");

NodeDefSPtr createNodeDefinition();

