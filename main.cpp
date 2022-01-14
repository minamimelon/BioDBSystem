#include "login.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>
#include <QtSql>

#include "browser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWin;
    mainWin.setWindowTitle(QObject::tr("基于林奈生物分类法的生物信息管理系统"));

    Browser browser(&mainWin);
    mainWin.setCentralWidget(&browser);

/*    QMenu *funcMenu = mainWin.menuBar()->addMenu(QObject::tr("功能"));
    funcMenu->addAction(QObject::tr("新增生物信息"), [&]() { browser.creatureAdd(); });*/

    QMenu *helpMenu = mainWin.menuBar()->addMenu(QObject::tr("帮助"));
    helpMenu->addAction(QObject::tr("开放源代码许可"), [&]() { browser.about(); });
    QObject::connect(&browser, &Browser::statusMessage, [&mainWin](const QString &text) {
        mainWin.statusBar()->showMessage(text);
    });

    helpMenu->addAction(QObject::tr("关于"), [&]() { browser.licence(); });
    QObject::connect(&browser, &Browser::statusMessage, [&mainWin](const QString &text) {
        mainWin.statusBar()->showMessage(text);
    });

    mainWin.show();

    return a.exec();
}
