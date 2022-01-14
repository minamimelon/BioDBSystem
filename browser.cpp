#include "browser.h"
#include "login.h"
#include "addcreature.h"
#include <QtWidgets>
#include <QtSql>
#include <QDebug>
#include "adddistr.h"
#include "basicquery.h"
#include "basicchange.h"
#include <QSqlQuery>
#include "showbarchart.h"
#include "registerdialog.h"

Browser::Browser(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    table->addAction(insertRowAction);
    table->addAction(deleteRowAction);
    table->addAction(submitAction);
    table->addAction(revertAction);
    while(!openConnectWidget());
    connectionWidget->refresh();
    if(mydb.userName()!="biodbAdmin"&&mydb.userName()!="root"){
        groupBox->setVisible(false);
        connectionWidget->setVisible(false);

    }else{

    }
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(table->model());
    if (tm)
        tm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    emit statusMessage(tr("就绪"));
}

Browser::~Browser()
{
}

void Browser::exec()
{
    QSqlQueryModel *model = new QSqlQueryModel(table);
    model->setQuery(QSqlQuery(sqlEdit->toPlainText(), mydb));
    table->setModel(model);

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    else if (model->query().isSelect())
        emit statusMessage(tr("执行成功"));
    else
        emit statusMessage(tr("执行成功,受影响的行数: %1").arg(
                           model->query().numRowsAffected()));
    updateActions();
}

void Browser::exec(QString sqlstr)
{
    QSqlQueryModel *model = new QSqlQueryModel(table);
    model->setQuery(QSqlQuery(sqlstr, mydb));
    table->setModel(model);

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    else if (model->query().isSelect())
        emit statusMessage(tr("执行成功"));
    else
        emit statusMessage(tr("执行成功,受影响的行数: %1").arg(
                           model->query().numRowsAffected()));
    updateActions();
}

QSqlError Browser::addConnection(const QString &driver, const QString &dbName, const QString &host,
                            const QString &user, const QString &passwd, int port)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("db"));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("db"));
    }

    return err;
}

bool Browser::openConnectWidget()
{
    Login dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return 0;
    if(dialog.userName()==""){
        QMessageBox::warning(this, tr("错误"), tr("用户名不能为空"));
        return 0;
    }
    if(dialog.password()==""){
        QMessageBox::warning(this, tr("错误"), tr("密码不能为空"));
        return 0;
    }
    QSqlError err = addConnection("QMYSQL", dialog.databaseName(), "localhost",
                       dialog.userName(), dialog.password());
    if (err.type() != QSqlError::NoError){
        QMessageBox::warning(this, tr("不能打开数据库"), tr("建立连接时发生错误") + err.text());
        return 0;
    }

    QStringList connectionNames = QSqlDatabase::connectionNames();
    mydb=QSqlDatabase::database(connectionNames.at(0));
    return 1;
}

void Browser::showTable(const QString &t)
{
    QSqlTableModel *model = new CustomModel(table, mydb);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable(mydb.driver()->escapeIdentifier(t, QSqlDriver::TableName));
    model->select();
    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
    connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &Browser::currentChanged);

    updateActions();
}

void Browser::showMetaData(const QString &t)
{
    QSqlRecord rec = mydb.record(t);
    QStandardItemModel *model = new QStandardItemModel(table);

    model->insertRows(0, rec.count());
    model->insertColumns(0, 7);

    model->setHeaderData(0, Qt::Horizontal, "属性名");
    model->setHeaderData(1, Qt::Horizontal, "类型");
    model->setHeaderData(2, Qt::Horizontal, "长度");
    model->setHeaderData(3, Qt::Horizontal, "精度");
    model->setHeaderData(4, Qt::Horizontal, "能否为空");
    model->setHeaderData(5, Qt::Horizontal, "自动值");
    model->setHeaderData(6, Qt::Horizontal, "默认值");

    for (int i = 0; i < rec.count(); ++i) {
        QSqlField fld = rec.field(i);
        model->setData(model->index(i, 0), fld.name());
        model->setData(model->index(i, 1), fld.typeID() == -1
                ? QString(QMetaType::typeName(fld.type()))
                : QString("%1 (%2)").arg(QMetaType::typeName(fld.type())).arg(fld.typeID()));
        model->setData(model->index(i, 2), fld.length());
        model->setData(model->index(i, 3), fld.precision());
        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
                : QVariant(bool(fld.requiredStatus())));
        model->setData(model->index(i, 5), fld.isAutoValue());
        model->setData(model->index(i, 6), fld.defaultValue());
    }

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateActions();
}

void Browser::insertRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(table->model());
    if (!model)
        return;

    QModelIndex insertIndex = table->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    model->insertRow(row);
    insertIndex = model->index(row, 0);
    table->setCurrentIndex(insertIndex);
    table->edit(insertIndex);
}

void Browser::deleteRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(table->model());
    if (!model)
        return;

    QModelIndexList currentSelection = table->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        if (currentSelection.at(i).column() != 0)
            continue;
        model->removeRow(currentSelection.at(i).row());
    }

    updateActions();
}

void Browser::updateActions()
{
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(table->model());
    bool enableIns = tm;
    bool enableDel = enableIns && table->currentIndex().isValid();

    insertRowAction->setEnabled(enableIns);
    deleteRowAction->setEnabled(enableDel);

    submitAction->setEnabled(tm);
    revertAction->setEnabled(tm);
}

void Browser::about()
{
    QMessageBox::about(this, tr("开源代码许可"), tr("demonstration applications of the Qt Toolkit "
                                          "Copyright (C) 2016 The Qt Company Ltd.\n"
                                          "Licensed under BSD\n"
                                           "Redistribution and use in source and binary forms, with or without\n"
                                         " modification, are permitted provided that the following conditions are\n"
                                         " met:\n"
                                         "   * Redistributions of source code must retain the above copyright\n"
                                         "     notice, this list of conditions and the following disclaimer.\n"
                                         "   * Redistributions in binary form must reproduce the above copyright\n"
                                         "     notice, this list of conditions and the following disclaimer in\n"
                                         "     the documentation and/or other materials provided with the\n"
                                         "     distribution.\n"
                                         "   * Neither the name of The Qt Company Ltd nor the names of its\n"
                                         "     contributors may be used to endorse or promote products derived\n"
                                         "     from this software without specific prior written permission.\n"
                                         "\n"
                                         "\n"
                                         " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
                                         " \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
                                         " LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
                                         " A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n"
                                         " OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n"
                                         " SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n"
                                         " LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n"
                                         " DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n"
                                         " THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
                                         " (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n"
                                         " OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\""
                                          "\n\n"

                                        "Qt Toolkit  " "Copyright (C) 2016 The Qt Company Ltd.\n"
                                          " GNU General Public License\n"
                                          " Alternatively, this file may be used under the terms of the GNU\n"
                                          " General Public License version 2.0 or (at your option) the GNU General\n"
                                          " Public license version 3 or any later version approved by the KDE Free\n"
                                          " Qt Foundation. The licenses are as published by the Free Software\n"
                                          " Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3\n"
                                          " included in the packaging of this file. Please review the following\n"
                                          " information to ensure the GNU General Public License requirements will\n"
                                          " be met: https://www.gnu.org/licenses/gpl-2.0.html and\n"
                                              " https://www.gnu.org/licenses/gpl-3.0.html.\n"));
}

void Browser::licence()
{
    QMessageBox::about(this, tr("关于"), tr("Copyright(C) 2021, <minamimelon, chwhc0@outlook.com>\n\n"
                                          "本程序是自由软件：你可以再分发之和/或依照由自由软件基金会发布的 GNU 通用公共许可证修改之，无论是版本 2 许可证，还是（按你的决定）任何以后版都可以。\
                                          发布该程序是希望它能有用，但是并无保障;甚至连可销售和符合某个特定的目的都不保证。请参看 GNU 通用公共许可证，了解详情。\
                                          你应该随程序获得一份 GNU 通用公共许可证的复本。如果没有，请看 <https://www.gnu.org/licenses/>。"));
}


void Browser::on_submitAction_triggered()
{
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(table->model());
    if (tm)
        tm->submitAll();
}

void Browser::on_revertAction_triggered()
{
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(table->model());
    if (tm)
        tm->revertAll();
}


void Browser::on_pushButtonAdd_clicked()
{
    addCreature dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString sql="CALL INS(\""+dialog.kingdomName()+"\",\""+dialog.divisionName()+"\",\""+dialog.className()+"\",\""
            +dialog.orderName()+"\",\""+dialog.familyName()+"\",\""+dialog.genusName()+"\",\""+dialog.speciesName()+"\");";
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonAddDistr_clicked()
{
    addDistr dialog(this);
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="CALL INSD(\""+dialog.speciesName()+"\",\""+dialog.distributionName()+"\");";
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonQspe_clicked()
{
    basicQuery dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString sqlfront="SELECT kingdom 界,division 门,class 纲,ordername 目,family 科,genus 属,species 种 FROM qry",sqlback="";
    if(dialog.ambig()){
        if(dialog.speciesName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" species LIKE \'%"+dialog.speciesName()+"%\'");
        }
        if(dialog.genusName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" genus LIKE \'%"+dialog.genusName()+"%\'");
        }
        if(dialog.familyName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" family LIKE \'%"+dialog.familyName()+"%\'");
        }
        if(dialog.orderName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" ordername LIKE \'%"+dialog.orderName()+"%\'");
        }
        if(dialog.className()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" class LIKE \'%"+dialog.className()+"%\'");
        }
        if(dialog.divisionName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" division LIKE \'%"+dialog.divisionName()+"%\'");
        }
        if(dialog.kingdomName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" kingdom LIKE \'%"+dialog.kingdomName()+"%\'");
        }
    }else{
        if(dialog.speciesName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" species LIKE \'"+dialog.speciesName()+"\'");
        }
        if(dialog.genusName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" genus LIKE \'"+dialog.genusName()+"\'");
        }
        if(dialog.familyName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" family LIKE \'"+dialog.familyName()+"\'");
        }
        if(dialog.orderName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" ordername LIKE \'"+dialog.orderName()+"\'");
        }
        if(dialog.className()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" class LIKE \'"+dialog.className()+"\'");
        }
        if(dialog.divisionName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" division LIKE \'"+dialog.divisionName()+"\'");
        }
        if(dialog.kingdomName()!=""){
            if(sqlback==""){
                sqlback.push_back(" WHERE");
            }else{
                sqlback.push_back(" AND");
            }
            sqlback.push_back(" kingdom LIKE \'"+dialog.kingdomName()+"\'");
        }
    }
    sqlback.push_back(';');
    qDebug().noquote()<<sqlfront+sqlback;
    exec(sqlfront+sqlback);
}

void Browser::on_pushButtonDl_clicked()
{
    basicQuery dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    if(dialog.ambig()){
        if(dialog.speciesName()!=""){
            QString sql="DELETE FROM speciestable WHERE species LIKE \'%"+dialog.speciesName()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.genusName()!=""){
            QString sql="DELETE FROM genustable WHERE genus LIKE \'%"+dialog.genusName()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.familyName()!=""){
            QString sql="DELETE FROM familytable WHERE family LIKE \'%"+dialog.familyName()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.orderName()!=""){
            QString sql="DELETE FROM ordertable WHERE ordername LIKE \'%"+dialog.orderName()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.className()!=""){
            QString sql="DELETE FROM classtable WHERE class LIKE \'%"+dialog.className()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.divisionName()!=""){
            QString sql="DELETE FROM divisiontable WHERE division LIKE \'%"+dialog.divisionName()+"%\'";
            exec(sql);
            return;
        }
        if(dialog.kingdomName()!=""){
            QString sql="DELETE FROM ordertable WHERE ordername LIKE \'%"+dialog.orderName()+"%\'";
            exec(sql);
            return;
        }
    }else{
        if(dialog.speciesName()!=""){
            QString sql="DELETE FROM speciestable WHERE species LIKE \'"+dialog.speciesName()+"\'";
            exec(sql);
            return;
        }
        if(dialog.genusName()!=""){
            QString sql="DELETE FROM genustable WHERE genus LIKE \'"+dialog.genusName()+"\'";
            exec(sql);
            return;
        }
        if(dialog.familyName()!=""){
            QString sql="DELETE FROM familytable WHERE family LIKE \'"+dialog.familyName()+"\'";
            exec(sql);
            return;
        }
        if(dialog.orderName()!=""){
            QString sql="DELETE FROM ordertable WHERE ordername LIKE \'"+dialog.orderName()+"\'";
            exec(sql);
            return;
        }
        if(dialog.className()!=""){
            QString sql="DELETE FROM classtable WHERE class LIKE \'"+dialog.className()+"\'";
            exec(sql);
            return;
        }
        if(dialog.divisionName()!=""){
            QString sql="DELETE FROM divisiontable WHERE division LIKE \'"+dialog.divisionName()+"\'";
            exec(sql);
            return;
        }
        if(dialog.kingdomName()!=""){
            QString sql="DELETE FROM ordertable WHERE ordername LIKE \'"+dialog.orderName()+"\'";
            exec(sql);
            return;
        }
    }
}

void Browser::on_pushButtonChg_clicked()
{
    basicChange dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    if(dialog.speciesName()!=""){
        QString sql="DELETE FROM speciestable WHERE species LIKE \'"+dialog.speciesName()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.genusName()!=""){
        QString sql="DELETE FROM genustable WHERE genus LIKE \'"+dialog.genusName()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.familyName()!=""){
        QString sql="DELETE FROM familytable WHERE family LIKE \'"+dialog.familyName()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.orderName()!=""){
        QString sql="DELETE FROM ordertable WHERE ordername LIKE \'"+dialog.orderName()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.className()!=""){
        QString sql="DELETE FROM classtable WHERE class LIKE \'"+dialog.className()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.divisionName()!=""){
        QString sql="DELETE FROM divisiontable WHERE division LIKE \'"+dialog.divisionName()+"\'";
        exec(sql);
        goto to;
    }
    if(dialog.kingdomName()!=""){
        QString sql="DELETE FROM ordertable WHERE ordername LIKE \'"+dialog.orderName()+"\'";
        exec(sql);
        goto to;
    }
    to:
    QString sql="CALL INS(\""+dialog.kingdomName2()+"\",\""+dialog.divisionName2()+"\",\""+dialog.className2()+"\",\""
            +dialog.orderName2()+"\",\""+dialog.familyName2()+"\",\""+dialog.genusName2()+"\",\""+dialog.speciesName2()+"\");";
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonQdi_clicked()
{
    addDistr dialog(this);
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="";
    if(dialog.distributionName()!=""&&dialog.speciesName()!=""){
        sql.push_back("SELECT distribution 栖息地,species 物种名 FROM vdistri WHERE distribution LIKE \'"+dialog.distributionName()+"%\' AND species LIKE \'"+dialog.speciesName()+"\'");
    }else if(dialog.distributionName()!=""){
        sql.push_back("SELECT distribution 栖息地,species 物种名 FROM vdistri WHERE distribution LIKE \'"+dialog.distributionName()+"%\'");
    }else if(dialog.speciesName()!=""){
        sql.push_back("SELECT species 物种名,distribution 栖息地 FROM vdistri WHERE species LIKE \'"+dialog.speciesName()+"\'");
    }else{
        sql.push_back("SELECT distribution 栖息地,species 物种名 FROM vdistri");
    }
    sql.push_back(';');
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonNm_clicked()
{
    addDistr dialog(this,"别名");
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="INSERT INTO commonnametable(commonName,speciesId) VALUES(\'"+dialog.distributionName()+"\',(SELECT speciesId FROM speciestable WHERE species=\'"+dialog.speciesName()+"\'));";
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonQnm_clicked()
{
    addDistr dialog(this,"别名");
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="";
    if(dialog.distributionName()!=""&&dialog.speciesName()!=""){
        sql.push_back("SELECT species 物种名,commonname 别名 FROM vcname WHERE commonname LIKE \'"+dialog.distributionName()+"\' AND species LIKE \'"+dialog.speciesName()+"\'");
    }else if(dialog.distributionName()!=""){
        sql.push_back("SELECT species 物种名 FROM vcname WHERE commonname LIKE \'"+dialog.distributionName()+"\'");
    }else if(dialog.speciesName()!=""){
        sql.push_back("SELECT commonname 别名 FROM vcname WHERE species LIKE \'"+dialog.speciesName()+"\'");
    }else{
        sql.push_back("SELECT species 物种名,commonname 别名 FROM vcname");
    }
    sql.push_back(';');
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonDld_clicked()
{
    addDistr dialog(this);
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="CALL DELD(\""+dialog.speciesName()+"\",\""+dialog.distributionName()+"\");";
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButtonDln_clicked()
{
    addDistr dialog(this,"别名");
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    QString sql="";
    if(dialog.distributionName()!=""&&dialog.speciesName()!=""){
        sql.push_back("DELETE FROM commonnametable WHERE commonName=\'"+dialog.distributionName()+"\'");
    }else if(dialog.distributionName()!=""){
        sql.push_back("DELETE FROM commonnametable WHERE commonName=\'"+dialog.distributionName()+"\'");
    }else if(dialog.speciesName()!=""){
        sql.push_back("DELETE FROM commonnametable WHERE speciesId=(SELECT speciesId FROM speciestable WHERE species=\'"+dialog.speciesName()+"\')");
    }
    sql.push_back(';');
    qDebug().noquote()<<sql;
    exec(sql);
}

void Browser::on_pushButton_clicked()
{
    QString sql="SELECT distribution 栖息地,COUNT(*) 数量 FROM vdistri GROUP BY distribution;";
    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->exec(sql);
    exec(sql);
    showBarChart disp(this,qry,"地域统计");
    disp.exec();
}

void Browser::on_pushButton_2_clicked()
{
    QString sql="SELECT species 物种,COUNT(*) 别名数量 FROM vcname GROUP BY species;";
    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->exec(sql);
    exec(sql);
    showBarChart disp(this,qry,"别名统计");
    disp.exec();
}

void Browser::on_pushButtonReg_clicked()
{
    loop:
    registerDialog dialog(this);
    if(dialog.exec()!=QDialog::Accepted){
        return;
    }
    if(dialog.password()!=dialog.repassword()){
        QMessageBox::warning(this, tr("错误"), tr("两次输入密码不一致"));
        goto loop;
    }
    QString sql="create user "+dialog.userName()+" identified by \'"+dialog.password()+"\';";
    qDebug().noquote()<<sql;
    exec(sql);
    if(dialog.userType()=="研究者"){
        QString sql="GRANT 'biodbResearcherRole' to "+dialog.userName()+";";
        qDebug().noquote()<<sql;
        exec(sql);
    }else {
        QString sql="GRANT 'biodbUserRole' to "+dialog.userName()+";";
        qDebug().noquote()<<sql;
        exec(sql);
    }
}
