#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
//#pragma execution_character_set("utf-8")

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    query.exec(QString("create table goods (id varchar primary key, name varchar ,kind varchar,remark varchar)"));
    query.exec(QString("insert into goods values('123456789012', '天地玄黄','小瓶','')"));
    query.exec(QString("insert into goods values('23456789012',  '宇宙洪荒','大瓶','')"));
    query.exec(QString("insert into goods values('323456789012', '日月盈昃','250g','')"));
    query.exec(QString("insert into goods values(1, '星宿列张','100ml','')"));
    query.exec(QString("insert into goods values(2, '寒来暑往' ,'仿制','')"));
    query.exec(QString("insert into goods values(3, '秋收冬藏' ,'红色包装','')"));
    query.exec(QString("insert into goods values('4', '闰余成岁' ,'红色包装','')"));

    query.exec(QString("create table supplier (id int primary key, name varchar ,address varchar,person varchar,phone varchar,remark varchar)"));
    query.exec(QString("create table customer (id int primary key, name varchar ,address varchar,person varchar,phone varchar,remark varchar)"));
    query.exec(QString("create table shop     (id int primary key, name varchar ,address varchar,person varchar,phone varchar,remark varchar)"));


    query.exec(QString("create table import (importId varchar , name varchar,kind varchar, number int,unit varchar,importTime datetime primary key)"));
    query.exec(QString("insert into import values(10, '入库感冒药','小瓶',1,'份','2018-02-21 11:11:11 111' )"));
    query.exec(QString("insert into import values(11, '入库感冒药','小瓶',1,'份','2017-02-21 11:11:11 111' )"));
    query.exec(QString("insert into import values(12, '入库感冒药','小瓶',1,'份','2019-02-21 11:11:11 111' )"));
    query.exec(QString("insert into import values(13, '入库感冒药','小瓶',1,'份','2018-01-21 11:11:11 111' )"));
    query.exec(QString("insert into import values(14, '入库感冒药','小瓶',1,'份','2018-12-21 11:11:11 111' )"));

    query.exec(QString("create table export (exportId varchar , name varchar, kind varchar,number int,unit varchar,exportTime datetime primary key)"));
    query.exec(QString("insert into export values(100, '出库感冒药','小瓶', 1,'份','2018-02-21 22:22:22 222' )"));

    query.exec(QString("create table stock (stockId varchar ,Id varchar, name varchar,kind varchar, number int,unit varchar,stockTime datetime primary key)"));
    query.exec(QString("insert into stock values(100, '出库感冒药', '小瓶',1,'份','2018-06-28 11:11:11 111' )"));

    query.exec(QString("create table number (id varchar primary key,minNumber int,maxNumber int)"));
    query.exec(QString("insert into number values(1,9,99)"));

    return true;
}

#endif // CONNECTION_H
