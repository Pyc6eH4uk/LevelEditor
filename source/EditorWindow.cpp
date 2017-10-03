//
// Created by gdhsnlvr on 03.07.17.
// Edited by Pyc6eH4uk on 3.10.17
//

#include "EditorWindow.h"
#include "LevelSettingDialog.h"

#include <QMenuBar>
#include <QToolBar>
#include <QString>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QJsonDocument>
#include <QDebug>

EditorWindow::EditorWindow() : QMainWindow() {

    _mainLayout = new QVBoxLayout();
    _sceneGraphicsView = new SceneGraphicsView();
    _mainLayout->addWidget(_sceneGraphicsView);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(_mainLayout);
    setCentralWidget(centralWidget);

    createMenus();
}

void EditorWindow::resetCurrentType() {
    _sceneGraphicsView->set_current_cell_type(COUNT_CELL);
    _sceneGraphicsView->set_current_bonus_type(COUNT_BONUS);
    _sceneGraphicsView->set_current_food_type(COUNT_OBJECTS);
}

void EditorWindow::openFileAction() {
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Save level"), "", tr("Level format json (*.json)")
    );

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QString str = file.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8());
        _sceneGraphicsView->load(document.object());
    }
}

void EditorWindow::saveFileAction() {
    QString fileName = QFileDialog::getSaveFileName(
            this, tr("Save level"), "", tr("Level format json (*.json)")
    );

    if (fileName.isEmpty())
        return;
    else {
        if (!fileName.contains(".json")) {
            fileName += ".json";
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QJsonDocument document = QJsonDocument(_sceneGraphicsView->save());
        file.write(document.toJson());
        file.close();
    }
}

void EditorWindow::closeFileAction() {

}

void EditorWindow::generateFileAction() {
    LevelSettingDialog levelSettingDialog;

    if (levelSettingDialog.exec() == QDialog::Accepted) {
        _sceneGraphicsView->set_width(levelSettingDialog.width());
        _sceneGraphicsView->set_height(levelSettingDialog.height());
        _sceneGraphicsView->generate();
    }
}

void EditorWindow::defaultCellAction() {
    resetCurrentType();
    _sceneGraphicsView->set_current_cell_type(DEFAULT_CELL);
}

void EditorWindow::emptyCellAction() {
    resetCurrentType();
    _sceneGraphicsView->set_current_cell_type(EMPTY_CELL);
}

void EditorWindow::createFileMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    QToolBar *fileToolBar = new QToolBar("File");
    addToolBar(fileToolBar);

    QAction *generateAction = new QAction("New", this);
    QAction *openAction = new QAction("Open", this);
    QAction *saveAction = new QAction("Save", this);
    QAction *closeAction = new QAction("Close", this);

    connect(generateAction, SIGNAL(triggered()), this, SLOT(generateFileAction()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFileAction()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFileAction()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeFileAction()));

    addAction(fileMenu, fileToolBar, generateAction);
    addAction(fileMenu, fileToolBar, openAction);
    addAction(fileMenu, fileToolBar, saveAction);
    addAction(fileMenu, fileToolBar, closeAction);
}

void EditorWindow::starsAction() {
    resetCurrentType();
    _sceneGraphicsView->set_current_food_type(STARS);
}

void EditorWindow::treesAction() {
    resetCurrentType();
    _sceneGraphicsView->set_current_food_type(TREES);
}

void EditorWindow::waterFlowAction() {
    resetCurrentType();
    _sceneGraphicsView->set_current_food_type(WATERFLOW);
}

void EditorWindow::createFoodBar() {
    QMenu *bonusesMenu = menuBar()->addMenu("Objects");
    QToolBar *bonusesToolBar = new QToolBar("Objects");
    bonusesToolBar->setOrientation(Qt::Vertical);
    addToolBar(Qt::LeftToolBarArea, bonusesToolBar);

    QIcon food1Icon = QIcon(":/resource/star.png");
    QIcon food2Icon = QIcon(":/resource/tree.png");
    QIcon waterFallIcon = QIcon(":/resource/waterfall.png");

    QAction *food1Action = new QAction(food1Icon, "Star", this);
    QAction *food2Action = new QAction(food2Icon, "Tree", this);
    QAction *waterfallAction = new QAction(waterFallIcon, "Waterfall", this);

    connect(food1Action, SIGNAL(triggered()), this, SLOT(starsAction()));
    connect(food2Action, SIGNAL(triggered()), this, SLOT(treesAction()));
    connect(waterfallAction, SIGNAL(triggered()), this, SLOT(waterFlowAction()));

    addAction(bonusesMenu, bonusesToolBar, food1Action);
    addAction(bonusesMenu, bonusesToolBar, food2Action);
    addAction(bonusesMenu, bonusesToolBar, waterfallAction);

}

void EditorWindow::createMenus() {
    createFileMenu();
    createCellBar();
    createFoodBar();
}

void EditorWindow::createCellBar() {
    QMenu *cellMenu = menuBar()->addMenu("Cells");
    QToolBar *cellToolBar = new QToolBar("Cells");
    cellToolBar->setOrientation(Qt::Vertical);
    addToolBar(Qt::LeftToolBarArea, cellToolBar);

    QIcon emptyIcon = QIcon(":/resource/empty_cell.png");
    QIcon defaultIcon = QIcon(":/resource/grass_cell.png");

    QAction *emptyAction = new QAction(emptyIcon, "Empty cell", this);
    QAction *defaultAction = new QAction(defaultIcon, "Default cell", this);

    connect(emptyAction, SIGNAL(triggered()), this, SLOT(emptyCellAction()));
    connect(defaultAction, SIGNAL(triggered()), this, SLOT(defaultCellAction()));

    addAction(cellMenu, cellToolBar, emptyAction);
    addAction(cellMenu, cellToolBar, defaultAction);
}

void EditorWindow::addAction(QMenu *menu, QToolBar *toolBar, QAction *action) {
    menu->addAction(action);
    toolBar->addAction(action);
}
