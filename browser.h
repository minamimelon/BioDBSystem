#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include <QSqlTableModel>
#include "ui_browserwidget.h"

class ConnectionWidget;
QT_FORWARD_DECLARE_CLASS(QTableView)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QSqlError)

class Browser: public QWidget, private Ui::Browser
{
    Q_OBJECT
public:
    Browser(QWidget *parent = nullptr);
    virtual ~Browser();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1);

    void insertRow();
    void deleteRow();
    void updateActions();
    QSqlDatabase mydb;

public slots:
    void exec();
    void exec(QString sqlstr);
    void showTable(const QString &table);
    void showMetaData(const QString &table);
    bool openConnectWidget();
    void currentChanged() { updateActions(); }
    void about();
    void licence();
    void creatureAdd(){on_pushButtonAdd_clicked();}

    void on_insertRowAction_triggered()
    { insertRow(); }
    void on_deleteRowAction_triggered()
    { deleteRow(); }
    void on_submitAction_triggered();
    void on_revertAction_triggered();
//    void on_selectAction_triggered();
    void on_connectionWidget_tableActivated(const QString &table)
    { showTable(table); }
    void on_connectionWidget_metaDataRequested(const QString &table)
    { showMetaData(table); }
    void on_submitButton_clicked()
    {
        exec();
        sqlEdit->setFocus();
    }
    void on_clearButton_clicked()
    {
        sqlEdit->clear();
        sqlEdit->setFocus();
    }

signals:
    void statusMessage(const QString &message);
private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonAddDistr_clicked();
    void on_pushButtonQspe_clicked();
    void on_pushButtonDl_clicked();
    void on_pushButtonChg_clicked();
    void on_pushButtonQdi_clicked();
    void on_pushButtonNm_clicked();
    void on_pushButtonQnm_clicked();
    void on_pushButtonDld_clicked();
    void on_pushButtonDln_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButtonReg_clicked();
};

class CustomModel: public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db) {}

    QVariant data(const QModelIndex &idx, int role) const override
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::yellow));
        return QSqlTableModel::data(idx, role);
    }
};

#endif
