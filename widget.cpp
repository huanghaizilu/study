#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include <QKeyEvent>
#include <QSqlQuery>
#include <QDateTimeEdit>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
//    showFullScreen();
//    showMaximized();
//    showNormal();
    setFixedSize(1024,768);
//    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    ui->printPButton_stock->setVisible(false);
    ui->showAllPButton_stock->setVisible(false);
    ui->printTableWidgetPButton->setVisible(false);

    ui->tableWidget_table->setColumnCount(4);
    ui->tableWidget_table->setRowCount(0);
    ui->tableWidget_table->setColumnWidth(0,200);
    ui->tableWidget_table->setColumnWidth(3,200);
    ui->tableWidget_table->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"备注");
    ui->tableWidget_table->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_table->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    ui->tableWidget_import->setColumnCount(6);
    ui->tableWidget_import->setRowCount(0);
    ui->tableWidget_import->setColumnWidth(0,200);
    ui->tableWidget_import->setColumnWidth(5,200);
    ui->tableWidget_import->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_import->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_import->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    ui->tableWidget_export->setColumnCount(6);
    ui->tableWidget_export->setRowCount(0);
    ui->tableWidget_export->setColumnWidth(0,200);
    ui->tableWidget_export->setColumnWidth(5,200);
    ui->tableWidget_export->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_export->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_export->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    ui->tableWidget_statistics->setColumnCount(6);
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setColumnWidth(0,200);
    ui->tableWidget_statistics->setColumnWidth(5,200);
    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    ui->tableWidget_stock->setColumnCount(7);
    ui->tableWidget_stock->setRowCount(0);
    ui->tableWidget_stock->setColumnWidth(0,200);
    ui->tableWidget_stock->setColumnWidth(6,200);
    ui->tableWidget_stock->setHorizontalHeaderLabels(QStringList()<<"StockID"<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_stock->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_stock->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    ui->tableWidget_alart->setColumnCount(9);
    ui->tableWidget_alart->setRowCount(0);
    ui->tableWidget_alart->setColumnWidth(0,200);
//    ui->tableWidget_alart->setColumnWidth(6,200);
    ui->tableWidget_alart->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"统计数量"<<"单位"<<"盘点数量"<<"最小值"<<"最大值"<<"备注");
    ui->tableWidget_alart->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_alart->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->radioButton->setChecked(true);
    ui->checkBox->setChecked(true);

    ui->tableWidget_search->setColumnCount(7);
    ui->tableWidget_search->setRowCount(0);
    ui->tableWidget_search->setColumnWidth(0,200);
    ui->tableWidget_search->setColumnWidth(6,200);
    ui->tableWidget_search->setHorizontalHeaderLabels(QStringList()<<"StockID"<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_search->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_search->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个


    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->search_dateEdit->setDate(QDate::currentDate());
    int stockNumber;
    QString sql_select = "select * from stock ";
    QSqlQuery query ;
    query.prepare(sql_select);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    qDebug() << query.last();
    if(query.last())
    {
        QString   stockDate = query.value(6).toString().mid(0,10);
        if(stockDate == QDate::currentDate().toString("yyyy-MM-dd"))
        {
            QString stockId = query.value(0).toString();
            stockNumber  = stockId.mid(11,3).toInt();
            qDebug() <<"stockNumber" <<stockNumber;
            ui->spinBox->setValue(stockNumber + 1);
        }
    }
    else
    {   stockNumber = 1;
        ui->spinBox->setValue(stockNumber);
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_addPButton_table_clicked()
{
    ui->label_show->text().clear();

    ui->tableWidget_table->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableWidget_table->setShowGrid(true);
    ui->tableWidget_table->setColumnWidth(0,200);
//    ui->tableWidget_table->setRowHeight(3,60);

    if(ui->lineEdit_id->text() == "")
    {
        ui->lineEdit_id->setFocus();
        QMessageBox::information(this,"Title","Please input id!",QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_name->text() == "")
    {
        QMessageBox::information(this,"Title","Please input name!",QMessageBox::Yes,QMessageBox::Yes);
        ui->lineEdit_name->setFocus();
        return;
    }

    QString str_id = ui->lineEdit_id->text();
    QString sql_query = "select * from goods where id = ?";
    QSqlQuery query;
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    if(query.first())
        {
        ui->label_show->setText("该商品已经录入名称！");
        QFont ft;
        ft.setPointSize(12);
        ft.setBold(true);
        ui->label_show->setFont(ft);
        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::red);
        ui->label_show->setPalette(pal);
        ui->lineEdit_id->setFocus();
        return;
        }

    int rowNum = ui->tableWidget_table->rowCount();
    ui->tableWidget_table->insertRow(rowNum);
    ui->tableWidget_table->setItem(rowNum,0,new QTableWidgetItem(ui->lineEdit_id->text()));
    ui->tableWidget_table->setItem(rowNum,1,new QTableWidgetItem(ui->lineEdit_name->text()));
    ui->tableWidget_table->setItem(rowNum,2,new QTableWidgetItem(ui->lineEdit_kind->text()));
    ui->tableWidget_table->setItem(rowNum,3,new QTableWidgetItem(ui->lineEdit_remark->text()));

    for(int i=0;i<rowNum;i++)
    {
        if(ui->tableWidget_table->item(i,0)->text() == ui->lineEdit_id->text())
        {
         qDebug() <<" has same record" ;
        ui->tableWidget_table->removeRow(rowNum);
        ui->tableWidget_table->selectRow(i);
        ui->lineEdit_id->setFocus();
        }
    }

    ui->lineEdit_id->setText("");
    ui->lineEdit_id->setFocus();
    ui->lineEdit_name->setText("");
    ui->lineEdit_kind->setText("");
    ui->lineEdit_remark->setText("");
}

void Widget::on_delPButton_table_clicked()
{
    int curRow = ui->tableWidget_table->currentIndex().row();
    if(curRow == -1) return;
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    }
    else
    {
        ui->tableWidget_table->removeRow(curRow);
    }

    ui->lineEdit_id->setText("");
    ui->lineEdit_id->setFocus();
    ui->lineEdit_name->setText("");
//    ui->lineEdit_kind->setText("");
//    ui->lineEdit_remark->setText("");
}

void Widget::on_showPButton_table_clicked()
{
    ui->tableWidget_table->clear();

    ui->tableWidget_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_table->setColumnWidth(0,200);
    ui->tableWidget_table->setShowGrid(true);
    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    query.prepare("select * from goods");
    query.exec();
    query.last();
    iRow = query.at() + 1;

    ui->tableWidget_table->setRowCount(iRow);
    iColumn = ui->tableWidget_table->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_table->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }
    ui->tableWidget_table->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称");
    ui->tableWidget_table->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
}

void Widget::on_showPButton_import_clicked()
{
    ui->tableWidget_import->clear();

    ui->tableWidget_import->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
//    ui->tableWidget_import->resizeColumnsToContents();
//    ui->tableWidget_import->resizeRowsToContents();

    ui->tableWidget_import->setColumnWidth(0,200);
    ui->tableWidget_import->setColumnWidth(5,200);
    ui->tableWidget_import->setShowGrid(true);
    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    query.prepare("select * from import");
    query.exec();
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_import->setRowCount(iRow);
    iColumn = ui->tableWidget_import->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_import->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_import->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_import->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_import->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_import->rowCount();
    ui->tableWidget_import->selectRow(rowCount-1);
}

void Widget::on_delPButton_import_clicked()
{
//    int rowNum = ui->tableWidget_import->rowCount();
    int curRow = ui->tableWidget_import->currentIndex().row();
    qDebug() << "curRow" << curRow;
    if(curRow == -1) return;

    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    }
    else
    {
        ui->tableWidget_import->removeRow(curRow);
    }
}

void Widget::on_addPButton_import_clicked()
{
    ui->tableWidget_import->setEditTriggers(QAbstractItemView::DoubleClicked);

    ui->tableWidget_import->setColumnWidth(0,200);
    ui->tableWidget_import->setColumnWidth(5,200);
    int rowNum  = ui->tableWidget_import->rowCount();
    ui->tableWidget_import->insertRow(rowNum);
    QModelIndex mdidx = ui->tableWidget_import->model()->index(rowNum,0);
    ui->tableWidget_import->setFocus();
    ui->tableWidget_import->setCurrentIndex(mdidx);
    ui->tableWidget_import->edit(mdidx);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
        if((event->key() == Qt::Key_Return)||(event->key() == Qt::Key_Enter))
//            setWindowState(Qt::WindowMaximized);
            qDebug() << "key enter return event" ;
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(ui->tabWidget->currentIndex()==0)
    {
    if((event->key() == Qt::Key_Return)||(event->key() == Qt::Key_Enter))
   {
    qDebug() << "key release event  import" ;
    int rowNum = ui->tableWidget_import->rowCount();
    QString str_id = ui->lineEdit_import->text();
    if(str_id == "") return;
          QSqlQuery query ;
          QString sql_query = "select * from goods where id = ? ";
          query.prepare(sql_query);
          query.addBindValue(str_id);
          if(!query.exec())
          {
              query.lastError();
          }
          query.first();

          QString name1 = query.value(1).toString();
          qDebug() <<"name1 import" <<name1;
          if(name1 == "")
          {
              ui->lineEdit_import->setText("");
              return;
          }

          QString kind1 = query.value(2).toString();
          qDebug() <<"kind1 import" <<kind1;
//          if(kind1 == "")
//          {
//              ui->lineEdit_import->setText("");
//              return;
//          }

          QTableWidgetItem *id          = new QTableWidgetItem();
          QTableWidgetItem *name        = new QTableWidgetItem();
          QTableWidgetItem *kind        = new QTableWidgetItem();
          QTableWidgetItem *number      = new QTableWidgetItem();
          QTableWidgetItem *unit        = new QTableWidgetItem();
          QTableWidgetItem *dateTime    = new QTableWidgetItem();
          id->setText(str_id);
          name->setText(name1);
          kind->setText(kind1);
          number->setText("1");
          unit->setText("份");
          QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss zzz");
          dateTime->setText(strDateTime);
          ui->tableWidget_import->insertRow(rowNum);
          ui->tableWidget_import->setItem(rowNum,0,id);
          ui->tableWidget_import->setItem(rowNum,1,name);
          ui->tableWidget_import->setItem(rowNum,2,kind);
          ui->tableWidget_import->setItem(rowNum,3,number);
          ui->tableWidget_import->setItem(rowNum,4,unit);
          ui->tableWidget_import->setItem(rowNum,5,dateTime);

          int rowNum1 = ui->tableWidget_import->rowCount();
          for(int i=0;i<rowNum1-1;i++)
          {
              if(ui->lineEdit_import->text() == ui->tableWidget_import->item(i,0)->text() )
              {
                qDebug() <<"import has same record!";
                int n = ui->tableWidget_import->item(i,3)->text().toInt();
                n= n + 1;
                QString str_n = QString::number(n,10);
                QTableWidgetItem *number1 = new QTableWidgetItem();
                number1->setText(str_n);
                ui->tableWidget_import->setItem(i,3,number1);
                int rowNum2 = ui->tableWidget_import->rowCount();
                ui->tableWidget_import->removeRow(rowNum2-1);
                break;
              }
          }
          ui->lineEdit_import->setText("");
    }
    }
    if(ui->tabWidget->currentIndex()==1)
    {
    if((event->key() == Qt::Key_Return)||(event->key() == Qt::Key_Enter))
       {
        qDebug() << "key release event  export" ;
        int rowNum = ui->tableWidget_export->rowCount();
        QString str_id = ui->lineEdit_export->text();
        if(str_id == "") return;
              QSqlQuery query ;
              QString sql_query = "select * from goods where id = ? ";
              query.prepare(sql_query);
              query.addBindValue(str_id);
              if(!query.exec())
              {
                  query.lastError();
              }
              query.first();

              QString name1 = query.value(1).toString();
              qDebug() <<"name1 import" <<name1;
              if(name1 == "")
              {
                  ui->lineEdit_export->setText("");
                  return;
              }

              QString kind1 = query.value(2).toString();
              qDebug() <<"kind1 import" <<kind1;
//              if(kind1 == "")
//              {
//                  ui->lineEdit_import->setText("");
//                  return;
//              }

              QTableWidgetItem *id          = new QTableWidgetItem();
              QTableWidgetItem *name        = new QTableWidgetItem();
              QTableWidgetItem *kind        = new QTableWidgetItem();
              QTableWidgetItem *number      = new QTableWidgetItem();
              QTableWidgetItem *unit        = new QTableWidgetItem();
              QTableWidgetItem *dateTime    = new QTableWidgetItem();
              id->setText(str_id);
              name->setText(name1);
              kind->setText(kind1);
              number->setText("1");
              unit->setText("份");
              QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss zzz");
              dateTime->setText(strDateTime);
              ui->tableWidget_export->insertRow(rowNum);
              ui->tableWidget_export->setItem(rowNum,0,id);
              ui->tableWidget_export->setItem(rowNum,1,name);
              ui->tableWidget_export->setItem(rowNum,2,kind);
              ui->tableWidget_export->setItem(rowNum,3,number);
              ui->tableWidget_export->setItem(rowNum,4,unit);
              ui->tableWidget_export->setItem(rowNum,5,dateTime);

              int rowNum1 = ui->tableWidget_export->rowCount();
              for(int i=0;i<rowNum1-1;i++)
              {
                  if(ui->lineEdit_export->text() == ui->tableWidget_export->item(i,0)->text() )
                  {
                    qDebug() <<"import has same record!";
                    int n = ui->tableWidget_export->item(i,3)->text().toInt();
                    n= n + 1;
                    QString str_n = QString::number(n,10);
                    QTableWidgetItem *number1 = new QTableWidgetItem();
                    number1->setText(str_n);
                    ui->tableWidget_export->setItem(i,3,number1);
                    int rowNum2 = ui->tableWidget_export->rowCount();
                    ui->tableWidget_export->removeRow(rowNum2-1);
                    break;
                  }
              }
              ui->lineEdit_export->setText("");
        }
    }
    if(ui->tabWidget->currentIndex()==4)
    {
    if((event->key() == Qt::Key_Return)||(event->key() == Qt::Key_Enter))
    {
    qDebug() << "key release event  table" ;
    ui->lineEdit_id->text() = "";
    ui->lineEdit_name->text() = "";
    ui->lineEdit_kind->text() = "";
    ui->lineEdit_remark->text() = "";
    QString str_id = ui->lineEdit_id->text();
    if(str_id == "") return;
    QString sql_query = "select * from goods where id = ?";
    QSqlQuery query;
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    if(query.first())
    {
    ui->label_show->setText("该商品已经录入名称！");
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    ui->label_show->setFont(ft);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::red);
    ui->label_show->setPalette(pal);
    QString name = query.value(1).toString();
    ui->lineEdit_name->setText(name);
    QString kind = query.value(2).toString();
    ui->lineEdit_kind->setText(kind);
    QString remark = query.value(3).toString();
    ui->lineEdit_remark->setText(remark);
    }
    else
    {
        ui->label_show->setText("该商品还没有录入名称！");
        QFont ft;
        ft.setPointSize(12);
        ft.setBold(true);
        ui->label_show->setFont(ft);
        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::red);
        ui->label_show->setPalette(pal);
        ui->lineEdit_name->setText("");
        ui->lineEdit_name->setFocus();
        ui->lineEdit_kind->setText("");
        ui->lineEdit_remark->setText("");
    }
    }
    }
    if(ui->tabWidget->currentIndex()==5)
    {
    if((event->key() == Qt::Key_Return)||(event->key() == Qt::Key_Enter))
       {
        qDebug() << "key release event  stock" ;
        int rowNum = ui->tableWidget_stock->rowCount();
        QString str_id = ui->lineEdit_ID->text();
                if(str_id == "") return;
          QSqlQuery query ;
          QString sql_query = "select * from goods where id = ? ";
          query.prepare(sql_query);
          query.addBindValue(str_id);
          if(!query.exec())
          {
              query.lastError();
          }
          query.first();
          QString name1 = query.value(1).toString();
          qDebug() <<"name1 stock" <<name1;
          if(name1 == "")
          {
              ui->lineEdit_ID->setText("");
              ui->lineEdit_ID->setFocus();
//              QMessageBox::setText("Please input the name");
              return;
          }

          QString kind1 = query.value(2).toString();
          qDebug() <<"kind1 stock" <<kind1;
          if(kind1 == "")
          {
//              ui->lineEdit_import->setText("");
//              QMessageBox::setText("Please input the kind  ");
              return;
          }
          QString stock,stock1,stock2,stock3,stock4;
          stock1 = "S";//means stock
          stock2 = QDate::currentDate().toString("yyyy-MM-dd");
//          stock3 = "xxx";//999条表单
//          stock3 = ui->lineEdit_number->text();
          QString buling = "0";
          int stockNumber = ui->spinBox->value();
          if((0<stockNumber)&&(stockNumber<10))
          {
          stock3 = buling + buling + QString::number(stockNumber,10);
          } else if(((9<stockNumber)&&(stockNumber<100)))
          {
          stock3 = buling + QString::number(stockNumber,10);
          }else  {
          stock3 = QString::number(stockNumber,10);
          }

          int stockListnumber = ui->tableWidget_stock->rowCount() + 1;
          if((0<stockListnumber)&&(stockListnumber<10))
          {
          stock4 = buling + buling + buling + buling + QString::number(stockListnumber,10);
          }else if(((9<stockListnumber)&&(stockListnumber<100)))
          {
          stock4 = buling + buling + buling + QString::number(stockListnumber,10);
          }else if(((99<stockListnumber)&&(stockListnumber<1000))){
          stock4 = buling + buling + QString::number(stockListnumber,10);
          }else if(((999<stockListnumber)&&(stockListnumber<10000))){
              stock4 = buling + QString::number(stockListnumber,10);
          }else if(((9999<stockListnumber)&&(stockListnumber<100000))){
              stock4 = QString::number(stockListnumber,10);
          }
//          stock4 = "xxxxx";//99999记录
          stock = stock1 +stock2 +stock3 + stock4;

          QTableWidgetItem *stockID     = new QTableWidgetItem();
          QTableWidgetItem *id          = new QTableWidgetItem();
          QTableWidgetItem *name        = new QTableWidgetItem();
          QTableWidgetItem *kind        = new QTableWidgetItem();
          QTableWidgetItem *number      = new QTableWidgetItem();
          QTableWidgetItem *unit        = new QTableWidgetItem();
          QTableWidgetItem *dateTime    = new QTableWidgetItem();
          stockID->setText(stock);
          id->setText(str_id);
          name->setText(name1);
          kind->setText(kind1);
          number->setText("1");
          unit->setText("份");
          QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss zzz");
          dateTime->setText(strDateTime);
          ui->tableWidget_stock->insertRow(rowNum);
          ui->tableWidget_stock->setItem(rowNum,0,stockID);
          ui->tableWidget_stock->setItem(rowNum,1,id);
          ui->tableWidget_stock->setItem(rowNum,2,name);
          ui->tableWidget_stock->setItem(rowNum,3,kind);
          ui->tableWidget_stock->setItem(rowNum,4,number);
          ui->tableWidget_stock->setItem(rowNum,5,unit);
          ui->tableWidget_stock->setItem(rowNum,6,dateTime);

          for(int i=0;i<rowNum;i++)
          {
              if(ui->lineEdit_ID->text() == ui->tableWidget_stock->item(i,1)->text() )
              {
                qDebug() <<"stock has same record!";
                int n = ui->tableWidget_stock->item(i,4)->text().toInt();
                n= n + 1;
                QString str_n = QString::number(n,10);
                QTableWidgetItem *number1 = new QTableWidgetItem();
                number1->setText(str_n);
                ui->tableWidget_stock->setItem(i,4,number1);
                ui->tableWidget_stock->removeRow(rowNum);
                break;
              }
          }
          ui->lineEdit_ID->setText("");
    }
    }
}

void Widget::on_commitPButton_table_clicked()
{
    ui->tableWidget_table->setEditTriggers(QAbstractItemView::DoubleClicked);
    int rowNum = ui->tableWidget_table->rowCount();
    if(rowNum == 0) return;
    for(int i=0;i<rowNum;i++)
    {
//        int     id;
        QString  id,name,kind,remark;
        id       = ui->tableWidget_table->item(i,0)->text();
        name     = ui->tableWidget_table->item(i,1)->text();
        kind     = ui->tableWidget_table->item(i,2)->text();
        remark   = ui->tableWidget_table->item(i,3)->text();
        QString sql_insert;
        sql_insert = "insert into goods values (?,?,?,?)";
        QSqlQuery query;
        query.prepare(sql_insert);
        query.addBindValue(id);
        query.addBindValue(name);
        query.addBindValue(kind);
        query.addBindValue(remark);
        if(!query.exec())
        {
            qDebug() << query.lastError();
//            QString error = query.lastError().text();
//            QMessageBox::critical(this,"title",error,QMessageBox::Yes);
        }
    }
    ui->tableWidget_table->setRowCount(0);

    ui->lineEdit_id->setText("");
    ui->lineEdit_id->setFocus();
    ui->lineEdit_name->setText("");
    ui->lineEdit_kind->setText("");
    ui->lineEdit_remark->setText("");
}

void Widget::on_commitPButton_import_clicked()
{
    ui->tableWidget_import->setEditTriggers(QAbstractItemView::DoubleClicked);

    int rowNum;
    rowNum  = ui->tableWidget_import->rowCount();

    for(int i=0;i<rowNum;i++)
    {
        int     id,number;
        QString name,kind,unit,strDateTime;

        id          = ui->tableWidget_import->item(i,0)->text().toInt();
        name        = ui->tableWidget_import->item(i,1)->text();
        kind        = ui->tableWidget_import->item(i,2)->text();
        number      = ui->tableWidget_import->item(i,3)->text().toInt();
        unit        = ui->tableWidget_import->item(i,4)->text();
        strDateTime = ui->tableWidget_import->item(i,5)->text();

        QString sql_insert;
        sql_insert = "insert into import values (?,?,?,?,?,?)";
        QSqlQuery query;
        query.prepare(sql_insert);
        query.addBindValue(id);
        query.addBindValue(name);
        query.addBindValue(kind);
        query.addBindValue(number);
        query.addBindValue(unit);
        query.addBindValue(strDateTime);
        if(!query.exec())
        {
            qDebug() << query.lastError();
        }
    }

    ui->tableWidget_import->clear();
    ui->tableWidget_import->setRowCount(0);
    ui->tableWidget_import->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_import->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_import->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
}

void Widget::on_addPButton_export_clicked()
{
    ui->tableWidget_export->setEditTriggers(QAbstractItemView::DoubleClicked);
//    ui->tableWidget_import->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget_export->setColumnWidth(0,200);
    ui->tableWidget_export->setColumnWidth(5,200);
    int rowNum ;
    rowNum  = ui->tableWidget_export->rowCount();

    ui->tableWidget_export->insertRow(rowNum);
    QModelIndex mdidx = ui->tableWidget_export->model()->index(rowNum,0);
    ui->tableWidget_export->setFocus();
    ui->tableWidget_export->setCurrentIndex(mdidx);
    ui->tableWidget_export->edit(mdidx);
}

void Widget::on_delPButton_export_clicked()
{
    int rowNum = ui->tableWidget_export->rowCount();
    int curRow = ui->tableWidget_export->currentIndex().row();
    if(curRow == rowNum -1 )
    {
        qDebug() << "select the last record , no delete ！";
        int rowNum1 = ui->tableWidget_export->rowCount();
        QModelIndex mdidx = ui->tableWidget_export->model()->index(rowNum1-1,0);
        ui->tableWidget_export->setFocus();
        ui->tableWidget_export->setCurrentIndex(mdidx);
        ui->tableWidget_export->edit(mdidx);
        return;
    }
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    }
    else
    {
        ui->tableWidget_export->removeRow(curRow);
    }
}

void Widget::on_showPButton_export_clicked()
{
        ui->tableWidget_export->clear();
        ui->tableWidget_export->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_export->setColumnWidth(0,200);
        ui->tableWidget_export->setColumnWidth(5,200);
        ui->tableWidget_export->setShowGrid(true);
        QSqlQuery query;
        int i = 0, j = 0, iColumn, iRow;
        query.prepare("select * from export");
        query.exec();
        query.last();
        iRow = query.at() + 1;
        ui->tableWidget_export->setRowCount(iRow);
        iColumn = ui->tableWidget_export->columnCount();
        query.first();
        while(i<iRow)
        {
        for (j = 0; j<iColumn; j++)
        ui->tableWidget_export->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        i++;
        query.next();
        }

        ui->tableWidget_export->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"数量"<<"单位"<<"日期和时间");
        ui->tableWidget_export->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget_export->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
        int rowCount = ui->tableWidget_export->rowCount();
        ui->tableWidget_export->selectRow(rowCount-1);
}

void Widget::on_commitPButton_export_clicked()
{
    ui->tableWidget_export->setEditTriggers(QAbstractItemView::DoubleClicked);
    int rowNum = ui->tableWidget_export->rowCount();

    if(rowNum == 0) return;
    for(int i=0;i<rowNum;i++)
    {
        int     id,number;
        QString name,kind,unit,strDateTime;
        id          = ui->tableWidget_export->item(i,0)->text().toInt();
        name        = ui->tableWidget_export->item(i,1)->text();
        kind        = ui->tableWidget_export->item(i,2)->text();
        number      = ui->tableWidget_export->item(i,3)->text().toInt();
        unit        = ui->tableWidget_export->item(i,4)->text();
        strDateTime = ui->tableWidget_export->item(i,5)->text();

        QString sql_insert;
        sql_insert = "insert into export values (?,?,?,?,?,?)";
        QSqlQuery query;
        query.prepare(sql_insert);
        query.addBindValue(id);
        query.addBindValue(name);
        query.addBindValue(kind);
        query.addBindValue(number);
        query.addBindValue(unit);
        query.addBindValue(strDateTime);
        if(!query.exec())
        {
            qDebug() << query.lastError();
        }
    }
    ui->tableWidget_export->clear();
    ui->tableWidget_export->setRowCount(0);
    ui->tableWidget_export->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_export->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_export->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
}

void Widget::on_import_day_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;    
    QString sql_select ="select importId,name,kind,sum(number),unit,importTime from import where importTime between ? and ?  group by importId";

    QDateTime startDateTime,endDateTime;
    QDate startDate,endDate;
    startDate = ui->calendarWidget->selectedDate().addDays(-1);
    endDate   = ui->calendarWidget->selectedDate();
    QString str_startDateTime,str_endDateTime,str_startDate,str_endDate;
    str_startDate = startDate.toString("yyyy-MM-dd");
    str_startDateTime = str_startDate + " 00:00:00 000";
    startDateTime =QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    str_endDate = endDate.toString("yyyy-MM-dd");
    str_endDateTime = str_endDate + " 00:00:00 000";
    endDateTime = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    int i = 0, j = 0, iColumn, iRow;
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
//    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_import_week_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int dayOfWeek = ui->calendarWidget->selectedDate().dayOfWeek();
    QDate startDate,endDate;
    QDateTime startDateTime,endDateTime;
    startDate = ui->calendarWidget->selectedDate().addDays(-dayOfWeek);
    endDate   = ui->calendarWidget->selectedDate().addDays(+7-dayOfWeek);
    QString str_startDateTime,str_endDateTime,str_startDate,str_endDate;
    str_startDate = startDate.toString("yyyy-MM-dd");
    str_startDateTime = str_startDate + " 00:00:00 000";
    startDateTime =QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    str_endDate = endDate.toString("yyyy-MM-dd");
    str_endDateTime = str_endDate + " 00:00:00 000";
    endDateTime = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    qDebug() << "startDateTime" << startDateTime << "endDateTime" << endDateTime;

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select importId,name,kind,sum(number),unit,importTime from import where importTime between ? and ?  group by importId";
    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_import_month_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int daysInMonth = ui->calendarWidget->selectedDate().daysInMonth();
    qDebug() << "daysInMonth" <<daysInMonth;
    int day = ui->calendarWidget->selectedDate().day();
    qDebug() << "day" <<day;
    QDate startDate,endDate;
    startDate = ui->calendarWidget->selectedDate().addDays(-day);
    endDate   = ui->calendarWidget->selectedDate().addDays(daysInMonth-day);
    qDebug() << "startDate" <<startDate;
    qDebug() << "endDate"   <<endDate;
    QString str_startDateTime,str_endDateTime;
    str_startDateTime = startDate.toString("yyyy-MM-dd") + " 00:00:00 000";
    str_endDateTime   = endDate.toString("yyyy-MM-dd")   + " 00:00:00 000";
    qDebug() << "str_startDateTime" <<str_startDateTime;
    qDebug() << "str_endDateTime"   <<str_endDateTime;
    QDateTime startDateTime,endDateTime;
    startDateTime = QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    endDateTime   = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    qDebug() << "startDateTime" <<startDateTime;
    qDebug() << "endDateTime"   <<endDateTime;

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select importId,name,kind,sum(number),unit,importTime from import where importTime between ? and ?  group by importId";
    qDebug() <<"sql_select" <<sql_select;

//    bool runNian;
//    if(((year%4 == 0 )&&(year%100 != 0))||(year%400 == 0))
//        runNian = true;
//    else
//        runNian = false;
//    int daysOfMonth;
//    switch (month) {
//    case 1:daysOfMonth = 31;
//        break;
//    case 2:
//        if(runNian)
//            daysOfMonth = 29;
//        else
//            daysOfMonth =28;
//        break;
//    case 3:daysOfMonth = 31;
//        break;
//    case 4:daysOfMonth = 30;
//        break;
//    case 5:daysOfMonth = 31;
//        break;
//    case 6:daysOfMonth = 30;
//        break;
//    case 7:daysOfMonth = 31;
//        break;
//    case 8:daysOfMonth = 31;
//        break;
//    case 9:daysOfMonth = 30;
//        break;
//    case 10:daysOfMonth = 31;
//        break;
//    case 11:daysOfMonth = 30;
//        break;
//    case 12:daysOfMonth = 31;
//        break;
//    default:
//        break;
//    }

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
//    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_import_season_Button_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);

    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->tableWidget_statistics->setColumnWidth(0,200);
    ui->tableWidget_statistics->setColumnWidth(5,200);
    ui->tableWidget_statistics->setShowGrid(true);
    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    query.prepare("select * from import");
    query.exec();
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
//    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_import_year_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select importId,name,kind,sum(number),unit,importTime from import where importTime between ? and ?  group by importId";
    int daysInYear = ui->calendarWidget->selectedDate().daysInYear();
    int dayOfYear = ui->calendarWidget->selectedDate().dayOfYear();
    QDate startDate,endDate;
    QDateTime startDateTime,endDateTime;
    startDate = ui->calendarWidget->selectedDate().addDays(-dayOfYear);
    endDate   = ui->calendarWidget->selectedDate().addDays(daysInYear-dayOfYear);
    QString str_startDateTime,str_endDateTime;
    str_startDateTime = startDate.toString("yyyy-MM-dd") + " 00:00:00 000";
    str_endDateTime   = endDate.toString("yyyy-MM-dd")   + " 00:00:00 000";
    startDateTime     = QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    endDateTime       = QDateTime::fromString(str_endDateTime  ,"yyyy-MM-dd HH:mm:ss zzz");

    qDebug() <<"startDateTime" <<startDateTime;
    qDebug() <<"endDateTime" <<endDateTime;
    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
//    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_export_season_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select exportId,name,kind,sum(number),unit,exportTime from export where exportTime between ? and ?  group by exportId";
    qDebug() << sql_select;

    QDateTime startDateTime,endDateTime;
    QDate startDate,endDate;
    startDate = ui->calendarWidget->selectedDate().addDays(-1);
    endDate   = ui->calendarWidget->selectedDate();
    QString str_startDateTime,str_endDateTime,str_startDate,str_endDate;
    str_startDate = startDate.toString("yyyy-MM-dd");
    str_startDateTime = str_startDate + " " + "00:00:00 000";
    startDateTime =QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    str_endDate = endDate.toString("yyyy-MM-dd");
    str_endDateTime = str_endDate + " " + "00:00:00 000";
    endDateTime = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
//    iColumn = 3;
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_statistics->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_export_day_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    QString sql_select ="select exportId,name,kind,sum(number),unit,exportTime   from export where exportTime   between ? and ?  group by exportId";

    QDateTime startDateTime,endDateTime;
    QDate startDate,endDate;
    startDate = ui->calendarWidget->selectedDate().addDays(-1);
    endDate   = ui->calendarWidget->selectedDate();
    QString str_startDateTime,str_endDateTime,str_startDate,str_endDate;
    str_startDate = startDate.toString("yyyy-MM-dd");
    str_startDateTime = str_startDate + " 00:00:00 000";
    startDateTime =QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    str_endDate = endDate.toString("yyyy-MM-dd");
    str_endDateTime = str_endDate + " 00:00:00 000";
    endDateTime = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    int i = 0, j = 0, iColumn, iRow;
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_export_week_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int dayOfWeek = ui->calendarWidget->selectedDate().dayOfWeek();
    QDate startDate,endDate;
    QDateTime startDateTime,endDateTime;
    startDate = ui->calendarWidget->selectedDate().addDays(-dayOfWeek);
    endDate   = ui->calendarWidget->selectedDate().addDays(+7-dayOfWeek);
    QString str_startDateTime,str_endDateTime,str_startDate,str_endDate;
    str_startDate = startDate.toString("yyyy-MM-dd");
    str_startDateTime = str_startDate + " 00:00:00 000";
    startDateTime =QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    str_endDate = endDate.toString("yyyy-MM-dd");
    str_endDateTime = str_endDate + " 00:00:00 000";
    endDateTime = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select exportId,name,kind,sum(number),unit,exportTime  from export where exportTime  between ? and ?  group by exportId";
    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_export_month_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int daysInMonth = ui->calendarWidget->selectedDate().daysInMonth();
    int day = ui->calendarWidget->selectedDate().day();
    QDate startDate,endDate;
    startDate = ui->calendarWidget->selectedDate().addDays(-day);
    endDate   = ui->calendarWidget->selectedDate().addDays(daysInMonth-day);
    QString str_startDateTime,str_endDateTime;
    str_startDateTime = startDate.toString("yyyy-MM-dd") + " 00:00:00 000";
    str_endDateTime   = endDate.toString("yyyy-MM-dd")   + " 00:00:00 000";
    QDateTime startDateTime,endDateTime;
    startDateTime = QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    endDateTime   = QDateTime::fromString(str_endDateTime,"yyyy-MM-dd HH:mm:ss zzz");

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select exportId,name,kind,sum(number),unit,exportTime from export where exportTime between ? and ?  group by exportId";

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_export_year_PButton_clicked()
{
    ui->tableWidget_statistics->clear();
    ui->tableWidget_statistics->setRowCount(0);
    ui->tableWidget_statistics->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    QString sql_select ="select exportId,name,kind,sum(number),unit,exportTime from export where exportTime between ? and ?  group by exportId";
    int daysInYear = ui->calendarWidget->selectedDate().daysInYear();
    int dayOfYear = ui->calendarWidget->selectedDate().dayOfYear();
    QDate startDate,endDate;
    QDateTime startDateTime,endDateTime;
    startDate = ui->calendarWidget->selectedDate().addDays(-dayOfYear);
    endDate   = ui->calendarWidget->selectedDate().addDays(daysInYear-dayOfYear);
    QString str_startDateTime,str_endDateTime;
    str_startDateTime = startDate.toString("yyyy-MM-dd") + " 00:00:00 000";
    str_endDateTime   = endDate.toString("yyyy-MM-dd")   + " 00:00:00 000";
    startDateTime     = QDateTime::fromString(str_startDateTime,"yyyy-MM-dd HH:mm:ss zzz");
    endDateTime       = QDateTime::fromString(str_endDateTime  ,"yyyy-MM-dd HH:mm:ss zzz");

    query.prepare(sql_select);
    query.addBindValue(startDateTime);
    query.addBindValue(endDateTime);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_statistics->setRowCount(iRow);
    iColumn = ui->tableWidget_statistics->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_statistics->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_statistics->setHorizontalHeaderLabels(QStringList()<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_statistics->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    int rowCount = ui->tableWidget_statistics->rowCount();
    ui->tableWidget_statistics->selectRow(rowCount-1);
}

void Widget::on_modPButton_table_clicked()
{
    ui->label_show->clear();

    if(ui->lineEdit_id->text() == "") return;
    if(ui->lineEdit_name->text() == "") return;
    QSqlQuery query;
    QString sql_search;
    sql_search = "select * from goods where id = ?";
    query.prepare(sql_search);
    QString idValue = ui->lineEdit_id->text();
    query.addBindValue(idValue);
    if(!query.exec())
    {
        qDebug() <<query.lastError();
    }
    if(!query.first())
    {
        ui->lineEdit_name->setFocus();
        ui->label_show->setText("没有该商品信息！");
        QFont ft;
        ft.setPointSize(12);
        ft.setBold(true);
        ui->label_show->setFont(ft);
        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::red);
        ui->label_show->setPalette(pal);
        return;
    }

    QString sql_update;
    sql_update = "update goods set name = ?,kind = ?,remark = ? where id = ?";
    query.prepare(sql_update);
    QString nameValue = ui->lineEdit_name->text();
    query.addBindValue(nameValue);
    QString kindValue = ui->lineEdit_kind->text();
    query.addBindValue(kindValue);
    QString remarkValue = ui->lineEdit_remark->text();
    query.addBindValue(remarkValue);
    query.addBindValue(idValue);
    if(!query.exec())
    {
        qDebug() <<query.lastError();
    }
    ui->label_show->setText("更新成功！");
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    ui->label_show->setFont(ft);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::red);
    ui->label_show->setPalette(pal);
    ui->lineEdit_id->setFocus();
}

void Widget::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"),
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
//        ui->widget->render(&printer);
        ui->widget->render(&printer);
//        ui->textEdit->print(&printer);
        }
}

void Widget::on_delPButton_stock_clicked()
{
    int curRow = ui->tableWidget_stock->currentIndex().row();
    if(curRow == -1) return;
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    }
    else
    {
        ui->tableWidget_stock->removeRow(curRow);
    }
}

void Widget::on_commitPButton_stock_clicked()
{
    ui->tableWidget_stock->setEditTriggers(QAbstractItemView::DoubleClicked);
    int rowNum = ui->tableWidget_stock->rowCount();
    if(rowNum == 0) return;
    for(int i=0;i<rowNum;i++)
    {
        int     number;
        QString  stockId,id,name,kind,unit,stockTime;
        stockId  = ui->tableWidget_stock->item(i,0)->text();
        id       = ui->tableWidget_stock->item(i,1)->text();
        name     = ui->tableWidget_stock->item(i,2)->text();
        kind     = ui->tableWidget_stock->item(i,3)->text();
        number   = ui->tableWidget_stock->item(i,4)->text().toInt();
        unit     = ui->tableWidget_stock->item(i,5)->text();
        stockTime= ui->tableWidget_stock->item(i,6)->text();
        QString sql_insert;
        sql_insert = "insert into stock values (?,?,?,?,?,?,?)";
        QSqlQuery query;
        query.prepare(sql_insert);
        query.addBindValue(stockId);
        query.addBindValue(id);
        query.addBindValue(name);
        query.addBindValue(kind);
        query.addBindValue(number);
        query.addBindValue(unit);
        query.addBindValue(stockTime);
        if(!query.exec())
        {
            qDebug() << query.lastError();
//            QString error = query.lastError().text();
//            QMessageBox::critical(this,"title",error,QMessageBox::Yes);
        }
    }
    ui->tableWidget_stock->setRowCount(0);
    ui->lineEdit_ID->setText("");
    ui->lineEdit_ID->setFocus();

    int stockNumber = ui->spinBox->value() + 1;
    ui->spinBox->setValue(stockNumber);
}

void Widget::on_printPButton_stock_clicked()
{
     createPdf();
}

void Widget::on_showAllPButton_stock_clicked()
{
    ui->tableWidget_stock->clear();
    ui->tableWidget_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_stock->setColumnWidth(0,200);
    ui->tableWidget_stock->setColumnWidth(6,200);
    ui->tableWidget_stock->setShowGrid(true);
    QSqlQuery query;
    int i = 0, j = 0, iColumn, iRow;
    query.prepare("select * from stock");
    query.exec();
    query.last();
    iRow = query.at() + 1;
    ui->tableWidget_stock->setRowCount(iRow);
    iColumn = ui->tableWidget_stock->columnCount();
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_stock->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }

    ui->tableWidget_stock->setHorizontalHeaderLabels(QStringList()<<"StockID"<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");
    ui->tableWidget_stock->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget_stock->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    int rowCount = ui->tableWidget_stock->rowCount();
    ui->tableWidget_stock->selectRow(rowCount-1);
}

void Widget::on_printTableWidgetPButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"),
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {

        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->tableWidget_stock->render(&printer);
    }
}

void Widget::on_searchPButton_stock_clicked()
{
    ui->tableWidget_search->clear();
    ui->tableWidget_search->setRowCount(0);
    ui->tableWidget_search->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_search->setHorizontalHeaderLabels(QStringList()<<"StockID"<<"ID"<<"名称"<<"种类"<<"数量"<<"单位"<<"日期和时间");

    QString stock,stock1,stock2,stock3;
    stock1 = "S";//means stock
//    stock2 = ui->search_dateEdit.toString("yyyy-MM-dd");
    stock2 = ui->search_dateEdit->text();
    qDebug() <<stock2;
    QString buling = "0";
    int stockNumber = ui->search_spinBox->value();
    if((0<stockNumber)&&(stockNumber<10))
    {
    stock3 = buling + buling + QString::number(stockNumber,10);
    } else if(((9<stockNumber)&&(stockNumber<100)))
    {
    stock3 = buling + QString::number(stockNumber,10);
    }else  {
    stock3 = QString::number(stockNumber,10);
    }
    stock = stock1 + stock2 +stock3 + "%";
    qDebug() <<"stock" <<stock;

//    QString sql_search = "select * from stock where stockId like '" + stock + "%'";
        QString sql_search = "select * from stock where stockId like :stock ";
    qDebug() << sql_search;
    QSqlQuery query ;
    query.prepare(sql_search);
    query. addBindValue(stock);
    if(!query.exec())
    {
        query.lastError();
    }
    qDebug() << query.first();
    query.last();

    int i = 0, j = 0, iColumn, iRow;
    iRow = query.at() + 1;
    qDebug() <<"iRow" <<iRow;
    ui->tableWidget_search->setRowCount(iRow);
    iColumn = ui->tableWidget_search->columnCount();
    qDebug() <<"iColumn" <<iColumn;
    query.first();
    while(i<iRow)
    {
    for (j = 0; j<iColumn; j++)
    ui->tableWidget_search->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
    i++;
    query.next();
    }
}

void Widget::on_clear_sta_PButton_clicked()
{
    ui->tableWidget_statistics->setRowCount(0);
}

void Widget::on_search_PButton_alart_clicked()
{
    if((ui->radioButton->isChecked())&&(ui->checkBox->isChecked()))
        qDebug() <<"radioButton checkbox";

    QString str_id = ui->lineEdit_alart->text();
    QString sql_query = "select * from goods where id = ?";
    QSqlQuery query;
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    query.first();

    int rowNum = ui->tableWidget_alart->rowCount();
    ui->tableWidget_alart->insertRow(rowNum);
    ui->tableWidget_alart->setItem(rowNum,0,new QTableWidgetItem(str_id));
    ui->tableWidget_alart->setItem(rowNum,1,new QTableWidgetItem(query.value(1).toString()));
    ui->tableWidget_alart->setItem(rowNum,2,new QTableWidgetItem(query.value(2).toString()));

    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    query.first();

    sql_query = "select sum(number) from import where importId = ?";
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    query.first();
    int import_Number,export_Number;
    import_Number = query.value(0).toInt();
    qDebug() <<"import_Number"  <<import_Number;

    sql_query = "select sum(number) from export where exportId = ?";
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    query.first();
    export_Number = query.value(0).toInt();
    qDebug() <<"export_Number"  <<export_Number;
    QString str_number = QString::number(import_Number-export_Number);
    ui->tableWidget_alart->setItem(rowNum,3,new QTableWidgetItem(str_number));

    sql_query = "select * from number where id = ?";
    query.prepare(sql_query);
    query.addBindValue(str_id);
    if(!query.exec())
    {
        query.lastError();
    }
    query.first();
    QString str_minNumber = query.value(1).toString();
    QString str_maxNumber = query.value(2).toString();
    ui->tableWidget_alart->setItem(rowNum,6,new QTableWidgetItem(str_minNumber));
    ui->tableWidget_alart->setItem(rowNum,7,new QTableWidgetItem(str_maxNumber));
}
