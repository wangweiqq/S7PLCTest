#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    plcS7 = new PLC_S7("192.168.0.1");
    plcS7->start();
}

Widget::~Widget()
{
    delete ui;
    delete plcS7;
    plcS7 = NULL;
}
void Widget::on_pushButton_setJOG_clicked(){
    float data = ui->lineEdit_setJOG->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetJOG1(data);
}
void Widget::on_pushButton_PowerOn_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onPowerOn1();
}
void Widget::on_pushButton_Reset_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onReset1();
}
void Widget::on_pushButton_Home_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
}
void Widget::on_pushButton_setABS_clicked(){
    float data = ui->lineEdit_setABS->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABS1(data);
}
void Widget::on_pushButton_JOGPlus_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGPlus1();
}
void Widget::on_pushButton_JOGMinus_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGMinus1();
}
void Widget::on_pushButton_setArray_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetArray1(vec);
}
void Widget::on_pushButton_ABSLeft_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSLeft1();
}
void Widget::on_pushButton_ABSRight_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSRight1();
}
void Widget::on_pushButton_setABSLeft_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABSLeft1();
}
void Widget::on_pushButton_setABSRight_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABSRight1();
}
////////////////////////////2//////////////////////////////////
void Widget::on_pushButton_setJOG_2_clicked(){
    float data = ui->lineEdit_setJOG_2->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetJOG2(data);
}
void Widget::on_pushButton_PowerOn_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onPowerOn2();
}
void Widget::on_pushButton_Reset_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onReset2();
}
void Widget::on_pushButton_Home_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onHome2();
}
void Widget::on_pushButton_setABS_2_clicked(){
    float data = ui->lineEdit_setABS_2->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABS2(data);
}
void Widget::on_pushButton_JOGPlus_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGPlus2();
}
void Widget::on_pushButton_JOGMinus_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGMinus2();
}
void Widget::on_pushButton_setArray_2_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetArray2(vec);
}
void Widget::on_pushButton_ABSLeft_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSLeft2();
}
void Widget::on_pushButton_ABSRight_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSRight2();
}
void Widget::on_pushButton_setABSLeft_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
     plcS7->onSetABSLeft2();
}
void Widget::on_pushButton_setABSRight_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABSRight2();
}
///////////////////////////3//////////////////////////
void Widget::on_pushButton_setJOG_3_clicked(){
    float data = ui->lineEdit_setJOG_3->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetJOG3(data);
}
void Widget::on_pushButton_PowerOn_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onPowerOn3();
}
void Widget::on_pushButton_Reset_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onReset3();
}
void Widget::on_pushButton_Home_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onHome3();
}
void Widget::on_pushButton_setABS_3_clicked(){
    float data = ui->lineEdit_setABS_3->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABS3(data);
}
void Widget::on_pushButton_JOGPlus_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGPlus3();
}
void Widget::on_pushButton_JOGMinus_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onJOGMinus3();
}
void Widget::on_pushButton_setArray_3_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetArray3(vec);
}
void Widget::on_pushButton_ABSLeft_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSLeft3();
}
void Widget::on_pushButton_ABSRight_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    plcS7->onABSRight3();
}
void Widget::on_pushButton_setABSLeft_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABSLeft3();
}
void Widget::on_pushButton_setABSRight_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
    plcS7->onSetABSRight3();
}
