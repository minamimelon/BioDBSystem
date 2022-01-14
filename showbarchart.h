#ifndef SHOWBARCHART_H
#define SHOWBARCHART_H

#include <QDialog>
#include <QSql>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QChart>
#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class showBarChart;
}

class showBarChart : public QDialog
{
    Q_OBJECT

public:
    explicit showBarChart(QWidget *parent = nullptr,QSqlQuery *query=nullptr,QString title="");
    ~showBarChart();
    QChart *createBarChart() const;
private:
    Ui::showBarChart *ui;
};

#endif // SHOWBARCHART_H
