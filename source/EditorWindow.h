//
// Created by gdhsnlvr on 03.07.17.
// Edited by Pyc6eH4uk 3.10.17
//

#ifndef FOALEDITOR_EDITORWINDOW_H
#define FOALEDITOR_EDITORWINDOW_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include "SceneGraphicsView.h"

class EditorWindow : public QMainWindow {
    Q_OBJECT
protected:
    QVBoxLayout *_mainLayout;
    SceneGraphicsView *_sceneGraphicsView;

public:
    EditorWindow();

protected slots:
    // file menu
    void openFileAction();
    void saveFileAction();
    void closeFileAction();
    void generateFileAction();

    // cell menu
    void defaultCellAction();
    void emptyCellAction();

    // objects menu
    void starsAction();
    void treesAction();
    void waterFlowAction();

    void resetCurrentType();

protected:
    void createCellBar();
    void createFoodBar();

    void createFileMenu();
    void createMenus();
    void addAction(QMenu* menu, QToolBar* toolBar, QAction *action);
};


#endif //FOALEDITOR_EDITORWINDOW_H
