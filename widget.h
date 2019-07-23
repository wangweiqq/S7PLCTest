#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "plc_s7.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void on_pushButton_setJOG_clicked();
    void on_pushButton_PowerOn_clicked();
    void on_pushButton_Reset_clicked();
    void on_pushButton_Home_clicked();
    void on_pushButton_setABS_clicked();
    void on_pushButton_JOGPlus_clicked();
    void on_pushButton_JOGMinus_clicked();
    void on_pushButton_setArray_clicked();
    void on_pushButton_ABSLeft_clicked();
    void on_pushButton_ABSRight_clicked();
    void on_pushButton_setABSLeft_clicked();
    void on_pushButton_setABSRight_clicked();
//////////////////////////2///////////////////////////////
    void on_pushButton_setJOG_2_clicked();
    void on_pushButton_PowerOn_2_clicked();
    void on_pushButton_Reset_2_clicked();
    void on_pushButton_Home_2_clicked();
    void on_pushButton_setABS_2_clicked();
    void on_pushButton_JOGPlus_2_clicked();
    void on_pushButton_JOGMinus_2_clicked();
    void on_pushButton_setArray_2_clicked();
    void on_pushButton_ABSLeft_2_clicked();
    void on_pushButton_ABSRight_2_clicked();
    void on_pushButton_setABSLeft_2_clicked();
    void on_pushButton_setABSRight_2_clicked();
//////////////////////////3///////////////////////////////
    void on_pushButton_setJOG_3_clicked();
    void on_pushButton_PowerOn_3_clicked();
    void on_pushButton_Reset_3_clicked();
    void on_pushButton_Home_3_clicked();
    void on_pushButton_setABS_3_clicked();
    void on_pushButton_JOGPlus_3_clicked();
    void on_pushButton_JOGMinus_3_clicked();
    void on_pushButton_setArray_3_clicked();
    void on_pushButton_ABSLeft_3_clicked();
    void on_pushButton_ABSRight_3_clicked();
    void on_pushButton_setABSLeft_3_clicked();
    void on_pushButton_setABSRight_3_clicked();
private:
    Ui::Widget *ui;
    PLC_S7 *plcS7 = NULL;
};

#endif // WIDGET_H
