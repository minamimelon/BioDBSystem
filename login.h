#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>

#include "ui_login.h"

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString databaseName() const;
    QString userName() const;
    QString password() const;

private slots:
    void on_buttonOK_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::Login ui;
};

#endif // LOGIN_H
