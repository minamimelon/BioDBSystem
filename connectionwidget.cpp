#include "connectionwidget.h"

#include <QtWidgets>
#include <QtSql>

ConnectionWidget::ConnectionWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    tree = new QTreeWidget(this);
    tree->setObjectName(QLatin1String("tree"));
    tree->setHeaderLabels(QStringList(tr("基本表")));
    QAction *refreshAction = new QAction(tr("刷新"), this);
    metaDataAction = new QAction(tr("展示设计"), this);
    connect(refreshAction, &QAction::triggered, this, &ConnectionWidget::refresh);
    connect(metaDataAction, &QAction::triggered, this, &ConnectionWidget::showMetaData);
    this->addAction(refreshAction);
    this->addAction(metaDataAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    layout->addWidget(tree);

    QMetaObject::connectSlotsByName(this);
}

ConnectionWidget::~ConnectionWidget()
{
}

void ConnectionWidget::refresh()
{
    tree->clear();
    QStringList connectionNames = QSqlDatabase::connectionNames();
    QSqlDatabase db = QSqlDatabase::database(connectionNames.at(0), false);
    if (db.isOpen()) {
        QStringList tables = db.tables();
        for (int t = 0; t < tables.count(); ++t) {
            QTreeWidgetItem *table = new QTreeWidgetItem(tree);
            table->setText(0, tables.at(t));
        }
    }
    tree->doItemsLayout();
}

void ConnectionWidget::on_tree_itemActivated(QTreeWidgetItem *item, int /* column */)
{
    if (!item)
        return;
    emit tableActivated(item->text(0));
}

void ConnectionWidget::showMetaData()
{
    QTreeWidgetItem *cItem = tree->currentItem();
    emit metaDataRequested(cItem->text(0));
}

void ConnectionWidget::on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{
    metaDataAction->setEnabled(current);
}

