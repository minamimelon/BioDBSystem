#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();
    QString userType() const;
    QString userName() const;
    QString password() const;
    QString repassword() const;

private:
    Ui::registerDialog *ui;
};

#endif // REGISTERDIALOG_H
