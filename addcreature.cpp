#include "addcreature.h"
#include "ui_addcreature.h"

addCreature::addCreature(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCreature)
{
    ui->setupUi(this);

}

addCreature::~addCreature()
{
    delete ui;
}

QString addCreature::kingdomName() const
{
    return ui->lineEditKingdom->text();
}

QString addCreature::divisionName() const
{
    return ui->lineEditDivision->text();
}

QString addCreature::className() const
{
    return ui->lineEditClass->text();
}

QString addCreature::orderName() const
{
    return ui->lineEditOrder->text();
}

QString addCreature::familyName() const
{
    return ui->lineEditFamily->text();
}

QString addCreature::genusName() const
{
    return ui->lineEditGenus->text();
}

QString addCreature::speciesName() const
{
    return ui->lineEditSpecies->text();
}





