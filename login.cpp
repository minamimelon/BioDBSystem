#include "login.h"
#include "ui_login.h"
#include <QSqlDatabase>

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

Login::~Login()
{
}


QString Login::databaseName() const
{
    return ui.comboBoxDatabase->currentText();
}

QString Login::userName() const
{
    return ui.editUser->text();
}

QString Login::password() const
{
    return ui.editPasswd->text();
}

void Login::on_buttonOK_clicked()
{
    QStringList drivers = QSqlDatabase::drivers();
    if (!drivers.contains("QMYSQL")){
        QMessageBox::information(this, tr("Mysql驱动错误"),
                                 tr("请检查Mysql驱动"));
    } else {
        accept();
    }
}

void Login::on_buttonCancel_clicked()
{
    reject();
}
