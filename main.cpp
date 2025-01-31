#include "snippingwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Starting SnippingTool...";
    SnippingTool snippingTool;
    snippingTool.show();
    qDebug() << "SnippingTool should be visible now.";

    return a.exec();
}
