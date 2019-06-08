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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
#include <QCryptographicHash>
#include <QMessageBox>

#include "NodeDefBuilder.h"
#include "ContainerDefBuilder.h"
#include "ODataMetadataDef.h"

using namespace Oak::Model;

// =============================================================================
// (public)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->OakView->setColumnCount(2);
    ui->OakView->setHeaderLabels(QStringList() << "Type" << "Name");

    m_oakModel2 = new QOakModel(this);
    m_oakModel = m_oakModel2->oakModel();
    //m_oakModel = new OakModel();

    ui->treeView->setModel(m_oakModel2);

    ui->NodeDataView->setModel(m_oakModel);
    ui->OakView->setOakModel(m_oakModel);
    ui->toolBar_ModelActions->setModel(m_oakModel);

    ui->splitter->setSizes(QList<int>() << 350 << 650 << 0);

    //m_oakModel->setRootNodeDef(createModel());
    m_oakModel->setRootNodeDef(Oak::Model::ODataMetadataDef::MakeSPtr());
}

// =============================================================================
// (public)
MainWindow::~MainWindow()
{
    delete ui;
}

// =============================================================================
// (private)
QByteArray MainWindow::hashFromFile(const QString &filePath) const
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)) {
        hash.addData(file.readAll());
    } else {
        qDebug() << "Faild to create hash of file: " << filePath;
        return QByteArray();
        // Handle "cannot open file" error
    }

    // Retrieve the SHA1 signature of the file
    return hash.result();
}

// =============================================================================
// (private slots)
void MainWindow::on_actionNew_triggered()
{
    m_oakModel->createNewRootDocument(NodeData::Type::XML);
    m_oakModel->setRootNode(m_oakModel->rootNode());
    ui->OakView->expandAll();
    m_oakModel->setCurrentNode(m_oakModel->rootNode());
}

// =============================================================================
// (private slots)
void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load From Archive", QString::fromStdString(m_oakModel->docFilePathXML()));
    if (filePath.isEmpty()) { return; }
    if (m_oakModel2->loadModel(filePath)) {
        ui->OakView->expandAll();
        setWindowTitle("OData Browser - " + filePath);
        ui->OakView->resizeColumnToContents(0);
    }
}

// =============================================================================
// (private slots)
void MainWindow::on_actionSave_triggered()
{
    if (m_oakModel->docFilePathXML().empty()) {
        on_actionSaveAs_triggered();
        return;
    }
    if (!m_oakModel->saveRootNodeXML()) {
        QMessageBox::warning(this, "Save failed", "Could not save file");
    }
    return;
}

// =============================================================================
// (private slots)
void MainWindow::on_actionSaveAs_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", QString::fromStdString(m_oakModel->docFilePathXML()));
    if (!m_oakModel->saveRootNodeXML(filePath.toStdString())) {
        QMessageBox::warning(this, "Save Failed", "Faild to save file to:\n\n" + filePath);
    }
}

// =============================================================================
// (private slots)
void MainWindow::on_actionClose_triggered()
{
    m_oakModel->clearRoot();
}
