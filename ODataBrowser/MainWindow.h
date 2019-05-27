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

#include <QMainWindow>
#include <QDir>

#include "OakModel.h"
#include "NodeDef.h"

#define FILE_NAME "global-settings.xml"
#define PROD_SETTINGS_FILE_PATH "//sc19/CultivationProcess/data/global-settings.xml"

using namespace Oak::Model;

namespace Ui {
    class MainWindow;
}

// =============================================================================
// Class definition
// =============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QByteArray hashFromFile(const QString &file) const;

private slots:
    void on_actionNew_triggered();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();

    void on_actionClose_triggered();


private:
    Ui::MainWindow *ui;
    OakModel* m_oakModel;
};
