#include "basicchange.h"
#include "ui_basicchange.h"

basicChange::basicChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basicChange)
{
    ui->setupUi(this);
}

basicChange::~basicChange()
{
    delete ui;
}


QString basicChange::kingdomName() const
{
    return ui->lineEditKingdom->text();
}

QString basicChange::divisionName() const
{
    return ui->lineEditDivision->text();
}

QString basicChange::className() const
{
    return ui->lineEditClass->text();
}

QString basicChange::orderName() const
{
    return ui->lineEditOrder->text();
}

QString basicChange::familyName() const
{
    return ui->lineEditFamily->text();
}

QString basicChange::genusName() const
{
    return ui->lineEditGenus->text();
}

QString basicChange::speciesName() const
{
    return ui->lineEditSpecies->text();
}


QString basicChange::kingdomName2() const
{
    return ui->lineEditKingdom_2->text();
}

QString basicChange::divisionName2() const
{
    return ui->lineEditDivision_2->text();
}

QString basicChange::className2() const
{
    return ui->lineEditClass_2->text();
}

QString basicChange::orderName2() const
{
    return ui->lineEditOrder_2->text();
}

QString basicChange::familyName2() const
{
    return ui->lineEditFamily_2->text();
}

QString basicChange::genusName2() const
{
    return ui->lineEditGenus_2->text();
}

QString basicChange::speciesName2() const
{
    return ui->lineEditSpecies_2->text();
}

