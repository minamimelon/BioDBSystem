#include "adddistr.h"
#include "ui_adddistr.h"

addDistr::addDistr(QWidget *parent,QString nm) :
    QDialog(parent),
    ui(new Ui::addDistr)
{
    ui->setupUi(this);
    if(nm!=""){
        ui->label_2->setText(nm);
    }
}

addDistr::~addDistr()
{
    delete ui;
}

QString addDistr::speciesName() const
{
    return ui->lineEditSpecies->text();
}

QString addDistr::distributionName() const
{
    return ui->lineEditDistr->text();
}
