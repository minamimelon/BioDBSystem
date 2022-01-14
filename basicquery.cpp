#include "basicquery.h"
#include "ui_basicquery.h"

basicQuery::basicQuery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basicQuery)
{
    ui->setupUi(this);
}

basicQuery::~basicQuery()
{
    delete ui;
}


QString basicQuery::kingdomName() const
{
    return ui->lineEditKingdom_2->text();
}

QString basicQuery::divisionName() const
{
    return ui->lineEditDivision_2->text();
}

QString basicQuery::className() const
{
    return ui->lineEditClass_2->text();
}

QString basicQuery::orderName() const
{
    return ui->lineEditOrder_2->text();
}

QString basicQuery::familyName() const
{
    return ui->lineEditFamily_2->text();
}

QString basicQuery::genusName() const
{
    return ui->lineEditGenus_2->text();
}

QString basicQuery::speciesName() const
{
    return ui->lineEditSpecies_2->text();
}

bool basicQuery::ambig() const
{
    return ui->checkBoxAb->isChecked();
}





