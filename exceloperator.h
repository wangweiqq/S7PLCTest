﻿#ifndef EXCELOPERATOR_H
#define EXCELOPERATOR_H

#include <QObject>
#include <ActiveQt/QAxObject>
#include <QDebug>
#include <QDir>
#include <QColor>
#include <QThread>
class ExcelOperator : public QObject
{
    Q_OBJECT

public:
    explicit ExcelOperator(QObject *parent = nullptr);
    //static ExcelOperator* Instance();
    ~ExcelOperator();
    //打开文件isNew = 是否新建Excel表（注意Excel文件不存在）
    bool open(QString path,bool isNew = true);
    /*保存关闭文件*/
    bool save();
    //关闭文件
    bool close();
    //获取工作表数量
    int getSheetsCount();
    //根据名称创建工作表
    QAxObject* addSheet(QString name);
    //根据名称删除工作表
    bool delSheet(QString name);
    //根据编号删除工作表
    bool delSheet(int index);
    //根据名称获取工作表
    QAxObject* getSheet(QString name);
    //根据编号获取工作表
    QAxObject* getSheet(int index);
    //获取行对象
    QAxObject* getRows(QAxObject* pSheet);
    //获取行数
    int getRowsCount(QAxObject* pSheet);
    //获取列对象
    QAxObject* getColumns(QAxObject* pSheet);
    //获取列数
    int getColumnsCount(QAxObject* pSheet);
    //根据行列值获取单元格值, 如: 3行，5列
    QString getCell(QAxObject* pSheet, int row, int column);
    //根据行列编号获取单元格值, 如: "F6"
    QString getCell(QAxObject* pSheet, QString number);
    //根据行列值设置单元格值
    bool setCell(QAxObject* pSheet, int row, int column, QString value);
    //根据行列编号设置单元格值
    bool setCell(QAxObject* pSheet, QString number, QString value);
    /*获取单元格对象返回pRange*/
    QAxObject * getCellItem(QAxObject* pSheet, int row, int column);
    /*设置单元格值*/
    bool setItemValue(QAxObject* pRange,QString value);
    /*设置单元格背景色*/
    bool setItemBkColor(QAxObject* pRange,QColor c);
    bool setItemCenter(QAxObject* pRange);
    /*获取单元格字体*/
    QAxObject* getItemFont(QAxObject* pRange);
signals:
public slots:
private:
    QAxObject*      m_pExcel;
    QAxObject*      m_pWorksheets;
    QAxObject*      m_pWorkbook;
    QString         m_strPath;
};

#endif // EXCELOPERATOR_H
