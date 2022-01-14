#include "showbarchart.h"
#include "ui_showbarchart.h"
#include <QSql>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QChart>
#include <QtCharts>
#include <QDebug>
using namespace QtCharts;

showBarChart::showBarChart(QWidget *parent,QSqlQuery *query,QString title) :
    QDialog(parent),
    ui(new Ui::showBarChart)
{
    ui->setupUi(this);

    QChart *chart = new QChart();
    chart->setTitle(title);
    int maxValue=1;
    QBarSeries *series = new QBarSeries(chart);
    while(query->next()) {
        QBarSet *set = new QBarSet(query->value(0).toString());
        int val=query->value(1).toFloat();
        *set << val;
        maxValue=val > maxValue ? val : maxValue;
        series->append(set);
        qDebug()<<query->value(0);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, maxValue+1);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    axisY->setLabelFormat("%.1f  ");

    QChartView *chartView;

    chartView = new QChartView(chart);
    ui->verticalLayout->addWidget(chartView);
}

showBarChart::~showBarChart()
{
    delete ui;
}
