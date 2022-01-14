#ifndef ADDCREATURE_H
#define ADDCREATURE_H

#include <QDialog>

namespace Ui {
class addCreature;
}

class addCreature : public QDialog
{
    Q_OBJECT

public:
    explicit addCreature(QWidget *parent = nullptr);
    ~addCreature();
    QString kingdomName() const;

    QString divisionName() const;

    QString className() const;

    QString orderName() const;

    QString familyName() const;

    QString genusName() const;

    QString speciesName() const;
private:
    Ui::addCreature *ui;
};

#endif // ADDCREATURE_H
