#ifndef BASICCHANGE_H
#define BASICCHANGE_H

#include <QDialog>

namespace Ui {
class basicChange;
}

class basicChange : public QDialog
{
    Q_OBJECT

public:
    explicit basicChange(QWidget *parent = nullptr);
    ~basicChange();
    QString kingdomName() const;

    QString divisionName() const;

    QString className() const;

    QString orderName() const;

    QString familyName() const;

    QString genusName() const;

    QString speciesName() const;

    QString kingdomName2() const;

    QString divisionName2() const;

    QString className2() const;

    QString orderName2() const;

    QString familyName2() const;

    QString genusName2() const;

    QString speciesName2() const;

private:
    Ui::basicChange *ui;
};

#endif // BASICCHANGE_H
