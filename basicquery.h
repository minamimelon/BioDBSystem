#ifndef BASICQUERY_H
#define BASICQUERY_H

#include <QDialog>

namespace Ui {
class basicQuery;
}

class basicQuery : public QDialog
{
    Q_OBJECT

public:
    explicit basicQuery(QWidget *parent = nullptr);
    ~basicQuery();

    QString kingdomName() const;

    QString divisionName() const;

    QString className() const;

    QString orderName() const;

    QString familyName() const;

    QString genusName() const;

    QString speciesName() const;

    bool ambig() const;

private:
    Ui::basicQuery *ui;
};

#endif // BASICQUERY_H
