#include <QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QVBoxLayout>
#include <source/EditorWindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    EditorWindow editorWindow;
    editorWindow.show();

    return a.exec();
}