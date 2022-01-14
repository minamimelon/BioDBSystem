#include "registerdialog.h"
#include "ui_registerdialog.h"

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}

QString registerDialog::userType() const
{
    return ui->comboBoxType->currentText();
}

QString registerDialog::userName() const
{
    return ui->editUser->text();
}

QString registerDialog::password() const
{
    return ui->editPasswd->text();
}

QString registerDialog::repassword() const
{
    return ui->editPasswd_2->text();
}
