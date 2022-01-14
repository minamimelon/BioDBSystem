#ifndef ADDDISTR_H
#define ADDDISTR_H

#include <QDialog>

namespace Ui {
class addDistr;
}

class addDistr : public QDialog
{
    Q_OBJECT

public:
    explicit addDistr(QWidget *parent = nullptr,QString nm="");
    ~addDistr();

    QString distributionName() const;

    QString speciesName() const;

private:
    Ui::addDistr *ui;
};

#endif // ADDDISTR_H
