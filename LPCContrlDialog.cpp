#pragma execution_character_set("utf-8")
#include "LPCContrlDialog.h"
#include "ui_LPCContrlDialog.h"
#include <QDebug>
LPCContrlDialog::LPCContrlDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LPCContrlDialog)
{
    ui->setupUi(this);
    setWindowTitle("LPC控制对话框");
//    ui->PLCReturn->hide();
    btnlist.clear();
    btnlist.append(ui->btnSysInitial);
    btnlist.append(ui->btnSysStart);
    btnlist.append(ui->btnSysPause);
    btnlist.append(ui->btnSysStop);
    btnlist.append(ui->btnAlmReset);

    btnlist.append(ui->pushButton_setArray);
    btnlist.append(ui->pushButton_Reset);
    btnlist.append(ui->pushButton_Pause);
    btnlist.append(ui->pushButton_PowerOn);
    btnlist.append(ui->pushButton_setABS);
    btnlist.append(ui->pushButton_setJOG);
    btnlist.append(ui->pushButton_Home);
    btnlist.append(ui->pushButton_JOGMinus);
    btnlist.append(ui->pushButton_JOGPlus);
    btnlist.append(ui->pushButton_setABSLeft);
    btnlist.append(ui->pushButton_setABSRight);
    btnlist.append(ui->pushButton_ABSLeft);
    btnlist.append(ui->pushButton_ABSRight);

    btnlist.append(ui->pushButton_setArray_2);
    btnlist.append(ui->pushButton_Reset_2);
    btnlist.append(ui->pushButton_Pause_2);
    btnlist.append(ui->pushButton_PowerOn_2);
    btnlist.append(ui->pushButton_setABS_2);
    btnlist.append(ui->pushButton_setJOG_2);
    btnlist.append(ui->pushButton_Home_2);
    btnlist.append(ui->pushButton_JOGMinus_2);
    btnlist.append(ui->pushButton_JOGPlus_2);
    btnlist.append(ui->pushButton_setABSLeft_2);
    btnlist.append(ui->pushButton_setABSRight_2);
    btnlist.append(ui->pushButton_ABSLeft_2);
    btnlist.append(ui->pushButton_ABSRight_2);

    btnlist.append(ui->pushButton_setArray_3);
    btnlist.append(ui->pushButton_Reset_3);
    btnlist.append(ui->pushButton_Pause_3);
    btnlist.append(ui->pushButton_PowerOn_3);
    btnlist.append(ui->pushButton_setABS_3);
    btnlist.append(ui->pushButton_setJOG_3);
    btnlist.append(ui->pushButton_Home_3);
    btnlist.append(ui->pushButton_JOGMinus_3);
    btnlist.append(ui->pushButton_JOGPlus_3);
    btnlist.append(ui->pushButton_setABSLeft_3);
    btnlist.append(ui->pushButton_setABSRight_3);
    btnlist.append(ui->pushButton_ABSLeft_3);
    btnlist.append(ui->pushButton_ABSRight_3);

    btnlist.append(ui->btnSystem_Spare1);
    btnlist.append(ui->btnSystem_Spare2);
    btnlist.append(ui->btnRight_Laser);
    btnlist.append(ui->btnLeft_Laser);
    btnlist.append(ui->btnInitial_Sequence);
    btnlist.append(ui->btnAuto_Sequence);
    btnlist.append(ui->btnX_Counter_Rst);
    btnlist.append(ui->btnY_Counter_Rst);
    btnlist.append(ui->btnZ_Counter_Rst);
    btnlist.append(ui->btnTotal_Rst);
//    connect(this,SIGNAL(plcState(PLCState)),this,SLOT(onPLCState(PLCState)));
}

LPCContrlDialog::~LPCContrlDialog()
{
    delete ui;
//    delete plcS7;
//    plcS7 = NULL;
}
void LPCContrlDialog::onPlcLinkChanged(bool isErr){
    qDebug()<<"onPlcLinkChanged"<<isErr;
    if(isErr){
        for(int i = 0;i<btnlist.count();++i){
            btnlist.at(i)->setEnabled(true);
        }
    }else{
        onPLCState(PLCState());
        for(int i = 0;i<btnlist.count();++i){
            btnlist.at(i)->setEnabled(false);
        }
    }
}
void LPCContrlDialog::onPLCState(PLCState state){
    mPlcState = state;
    ui->Z_PowerOn_Status->setText(mPlcState.Z_PowerOn_Status ? "1" : "0");
    ui-> Z_PowerOn_Error->setText( mPlcState.Z_PowerOn_Error? "1" : "0");
    ui-> Z_Reset_Done->setText( mPlcState.Z_Reset_Done? "1" : "0");
    ui-> Z_Reset_Error->setText( mPlcState.Z_Reset_Error? "1" : "0");
    ui-> Z_Home_Done->setText( mPlcState.Z_Home_Done? "1" : "0");
    ui-> Z_Home_Error->setText( mPlcState.Z_Home_Error? "1" : "0");
    ui-> Z_ABS_Done->setText( mPlcState.Z_ABS_Done? "1" : "0");
    ui-> Z_ABS_Error->setText( mPlcState.Z_ABS_Error? "1" : "0");

    ui-> Z_JOG_inVelocity->setText( mPlcState.Z_JOG_inVelocity? "1" : "0");
    ui-> Z_JOG_Error->setText( mPlcState.Z_JOG_Error? "1" : "0");
    ui-> Z_Halt_Done->setText( mPlcState.Z_Halt_Done? "1" : "0");
    ui-> Z_Halt_Err->setText( mPlcState.Z_Halt_Err? "1" : "0");
    ui-> Z_Readparam_Vaild->setText( mPlcState.Z_Readparam_Vaild? "1" : "0");
    ui-> Z_Readparam_Err->setText( mPlcState.Z_Readparam_Err? "1" : "0");
    ui-> Z_Reset_Busy->setText( mPlcState.Z_Reset_Busy? "1" : "0");
    ui-> Z_Home_Busy->setText( mPlcState.Z_Home_Busy? "1" : "0");

    ui-> Z_ABS_Busy->setText( mPlcState.Z_ABS_Busy? "1" : "0");
//    ui-> Z_HomeComplete->setText( mPlcState.Z_HomeComplete? "1" : "0");
    ui-> Z_ABS_Done2->setText( mPlcState.Z_ABS_Done2? "1" : "0");
//    ui-> Z_Spare3->setText( mPlcState.Z_Spare3? "1" : "0");
//    ui-> Z_Spare4->setText( mPlcState.Z_Spare4? "1" : "0");
//    ui-> Z_Spare5->setText( mPlcState.Z_Spare5? "1" : "0");
//    ui-> Z_Spare6->setText( mPlcState.Z_Spare6? "1" : "0");
//    ui-> Z_Spare7->setText( mPlcState.Z_Spare7? "1" : "0");

//    ui-> Z_Spare8->setText( mPlcState.Z_Spare8? "1" : "0");
//    ui-> Z_Spare9->setText( mPlcState.Z_Spare9? "1" : "0");
//    ui-> Z_Spare10->setText( mPlcState.Z_Spare10? "1" : "0");
    ui-> X_PowerOn_Status->setText( mPlcState. X_PowerOn_Status? "1" : "0");
    ui-> X_PowerOn_Error->setText( mPlcState.X_PowerOn_Error? "1" : "0");
    ui-> X_Reset_Done->setText( mPlcState.X_Reset_Done? "1" : "0");
    ui-> X_Reset_Error->setText( mPlcState.X_Reset_Error? "1" : "0");
    ui-> X_Home_Done->setText( mPlcState.X_Home_Done? "1" : "0");

    ui-> X_Home_Error->setText( mPlcState.X_Home_Error? "1" : "0");
    ui-> X_ABS_Done->setText( mPlcState.X_ABS_Done? "1" : "0");
    ui-> X_ABS_Error->setText(mPlcState.X_ABS_Error? "1" : "0");
    ui-> X_JOG_inVelocity->setText( mPlcState.X_JOG_inVelocity? "1" : "0");
    ui-> X_JOG_Error->setText( mPlcState.X_JOG_Error? "1" : "0");
    ui-> X_Halt_Done->setText( mPlcState.X_Halt_Done? "1" : "0");
    ui-> X_Halt_Err->setText( mPlcState.X_Halt_Err? "1" : "0");
    ui-> X_Readparam_Vaild->setText( mPlcState.X_Readparam_Vaild? "1" : "0");

    ui-> X_Readparam_Err->setText( mPlcState.X_Readparam_Err? "1" : "0");
    ui-> X_Reset_Busy->setText( mPlcState.X_Reset_Busy? "1" : "0");
    ui-> X_Home_Busy->setText( mPlcState.X_Home_Busy? "1" : "0");
    ui-> X_ABS_Busy->setText( mPlcState.X_ABS_Busy? "1" : "0");
//    ui-> X_HomeComplete->setText( mPlcState.X_HomeComplete? "1" : "0");
    ui-> X_ABS_Done2 ->setText( mPlcState.X_ABS_Done2? "1" : "0");
//    ui-> X_Spare3->setText( mPlcState.X_Spare3? "1" : "0");
//    ui-> X_Spare4->setText( mPlcState.X_Spare4? "1" : "0");

//    ui-> X_Spare5->setText( mPlcState.X_Spare5? "1" : "0");
//    ui-> X_Spare6->setText( mPlcState.X_Spare6? "1" : "0");
//    ui-> X_Spare7->setText( mPlcState.X_Spare7? "1" : "0");
//    ui-> X_Spare8->setText( mPlcState. X_Spare8? "1" : "0");
//    ui-> X_Spare9->setText( mPlcState.X_Spare9? "1" : "0");
//    ui-> X_Spare10->setText( mPlcState.X_Spare10? "1" : "0");
    ui-> Y_PowerOn_Status->setText( mPlcState.Y_PowerOn_Status? "1" : "0");
    ui-> Y_PowerOn_Error->setText( mPlcState.Y_PowerOn_Error? "1" : "0");

    ui-> Y_Reset_Done->setText( mPlcState.Y_Reset_Done? "1" : "0");
    ui-> Y_Reset_Error->setText( mPlcState.Y_Reset_Error? "1" : "0");
    ui-> Y_Home_Done->setText( mPlcState.Y_Home_Done? "1" : "0");
    ui-> Y_Home_Error->setText( mPlcState.Y_Home_Error? "1" : "0");
    ui-> Y_ABS_Done->setText( mPlcState.Y_ABS_Done? "1" : "0");
    ui-> Y_ABS_Error->setText( mPlcState.Y_ABS_Error? "1" : "0");
    ui-> Y_JOG_inVelocity->setText( mPlcState.Y_JOG_inVelocity? "1" : "0");
    ui-> Y_JOG_Error->setText( mPlcState.Y_JOG_Error? "1" : "0");

    ui-> Y_Halt_Done->setText( mPlcState.Y_Halt_Done? "1" : "0");
    ui-> Y_Halt_Err->setText( mPlcState.Y_Halt_Err? "1" : "0");
    ui-> Y_Readparam_Vaild->setText( mPlcState.Y_Readparam_Vaild? "1" : "0");
    ui-> Y_Readparam_Err->setText( mPlcState.Y_Readparam_Err? "1" : "0");
    ui-> Y_Reset_Busy->setText( mPlcState.Y_Reset_Busy? "1" : "0");
    ui-> Y_Home_Busy->setText( mPlcState.Y_Home_Busy? "1" : "0");
    ui-> Y_ABS_Busy->setText( mPlcState.Y_ABS_Busy? "1" : "0");
//    ui-> Y_HomeComplete->setText( mPlcState.Y_HomeComplete? "1" : "0");

    ui-> Y_ABS_Done2->setText( mPlcState.Y_ABS_Done2? "1" : "0");
//    ui-> Y_Spare3->setText( mPlcState.Y_Spare3? "1" : "0");
//    ui-> Y_Spare4->setText( mPlcState.Y_Spare4? "1" : "0");
//    ui-> Y_Spare5->setText( mPlcState.Y_Spare5? "1" : "0");
//    ui-> Y_Spare6->setText( mPlcState.Y_Spare6? "1" : "0");
//    ui-> Y_Spare7->setText( mPlcState.Y_Spare7? "1" : "0");
//    ui-> Y_Spare8->setText(mPlcState.Y_Spare8? "1" : "0");
//    ui-> Y_Spare9->setText( mPlcState.Y_Spare9? "1" : "0");

//    ui-> Y_Spare10->setText( mPlcState.Y_Spare10? "1" : "0");

    //初始化完成
    ui-> Initial_Complete_Lamp->setText(mPlcState.Initial_Complete_Lamp? "1" : "0");
    //系统运行中
    ui->Auto_Lamp->setText(mPlcState.Sys_Auto_Lamp? "1" : "0");
    //系统暂停中
    ui->System_Pause_Lamp->setText(mPlcState.Sys_Pause_Lamp? "1" : "0");
    //系统停止
    ui->System_Stop_Lamp->setText(mPlcState.Sys_Stop_Lamp? "1" : "0");
    //异常复位
    ui->System_RST_Lamp->setText(mPlcState.Sys_RST_Lamp? "1" : "0");
    ui-> NOKE1->setText(mPlcState.NOKE_1? "1" : "0");
    ui-> NOKE2->setText(mPlcState.NOKE_2? "1" : "0");
    ui-> NOKE3->setText(mPlcState.NOKE_3? "1" : "0");
    ui-> NOKE4->setText(mPlcState.NOKE_4? "1" : "0");
    ui-> NOKE5->setText(mPlcState.NOKE_5? "1" : "0");
    //Z_当前位置
    ui-> Z_ActualPosition ->setText(QString("%1").arg(mPlcState.Z_ActualPosition));
    //X_当前位置
    ui-> X_ActualPosition ->setText(QString("%1").arg(mPlcState.X_ActualPosition));
    //Y_当前位置
    ui-> Y_ActualPosition ->setText(QString("%1").arg(mPlcState.Y_ActualPosition));
    //Z_目标位置
    ui-> Z_TargetPosition->setText(QString("%1").arg(mPlcState.Z_TargetPosition));
    //X_目标位置
    ui-> X_TargetPosition->setText(QString("%1").arg(mPlcState.X_TargetPosition));
    //Y_目标位置
    ui-> Y_TargetPosition->setText(QString("%1").arg(mPlcState.Y_TargetPosition));
    //自动流程
    ui-> Auto_Sequence->setText(QString("%1").arg(mPlcState.Auto_Sequence));
    //初始化流程
    ui-> Initial_Sequence->setText(QString("%1").arg(mPlcState.Initial_Sequence));
    //X_运动次数
    ui-> X_Counter->setText(QString("%1").arg(mPlcState.X_Counter));
    //Y_运动次数
    ui-> Y_Counter->setText(QString("%1").arg(mPlcState.Y_Counter));
    //Z_运动次数
    ui-> Z_Counter->setText(QString("%1").arg(mPlcState.Z_Counter));
    //产品信息
    ui-> Product_Information->setText(QString("%1").arg(mPlcState.Product_Information));
//    QString str1 = QString("Z_PowerOn_Status = %1  Z_PowerOn_Error = %2  Z_Reset_Done = %3  Z_Reset_Error = %4  Z_Home_Done = %5  Z_Home_Error = %6  Z_ABS_Done = %7  Z_ABS_Error = %8\n")
//                .arg(state.Z_PowerOn_Status).arg(state.Z_PowerOn_Error).arg(state.Z_Reset_Done).arg(state.Z_Reset_Error).arg(state.Z_Home_Done).arg(state.Z_Home_Error).arg(state.Z_ABS_Done).arg(state.Z_ABS_Error);
//    QString str2 = QString("Z_JOG_inVelocity = %1  Z_JOG_Error = %2  Z_Halt_Done = %3  Z_Halt_Err = %4  Z_Readparam_Vaild = %5  Z_Readparam_Err = %6  Z_Reset_Busy = %7  Z_Home_Busy = %8\n")
//                .arg(state.Z_JOG_inVelocity).arg(state.Z_JOG_Error).arg(state.Z_Halt_Done).arg(state.Z_Halt_Err).arg(state.Z_Readparam_Vaild).arg(state.Z_Readparam_Err).arg(state.Z_Reset_Busy).arg(state.Z_Home_Busy);
//    QString str3 = QString("Z_ABS_Busy = %1  Z_HomeComplete = %2  Z_ABS_Done2 = %3  Z_Spare3 = %4  Z_Spare4 = %5  Z_Spare5 = %6  Z_Spare6 = %7  Z_Spare7 = %8\n")
//                .arg(state.Z_ABS_Busy).arg(state.Z_HomeComplete).arg(state.Z_ABS_Done2).arg(state.Z_Spare3).arg(state.Z_Spare4).arg(state.Z_Spare5).arg(state.Z_Spare6).arg(state.Z_Spare7);
//    QString str4 = QString("Z_Spare8 = %1  Z_Spare9 = %2  Z_Spare10 = %3  X_PowerOn_Status = %4  X_PowerOn_Error = %5  X_Reset_Done = %6  X_Reset_Error = %7  X_Home_Done = %8\n")
//                .arg(state.Z_Spare8).arg(state.Z_Spare9).arg(state.Z_Spare10).arg(state.X_PowerOn_Status).arg(state.X_PowerOn_Error).arg(state.X_Reset_Done).arg(state.X_Reset_Error).arg(state.X_Home_Done);
//    QString str5 = QString("X_Home_Error = %1  X_ABS_Done = %2  X_ABS_Error = %3  X_JOG_inVelocity = %4  X_JOG_Error = %5  X_Halt_Done = %6  X_Halt_Err = %7  X_Readparam_Vaild = %8\n")
//                .arg(state.X_Home_Error).arg(state.X_ABS_Done).arg(state.X_ABS_Error).arg(state.X_JOG_inVelocity).arg(state.X_JOG_Error).arg(state.X_Halt_Done).arg(state.X_Halt_Err).arg(state.X_Readparam_Vaild);
//    QString str6 = QString("X_Readparam_Err = %1  X_Reset_Busy = %2  X_Home_Busy = %3  X_ABS_Busy = %4  X_HomeComplete = %5  X_ABS_Done2 = %6  X_Spare3 = %7  X_Spare4 = %8\n")
//                .arg(state.X_Readparam_Err).arg(state.X_Reset_Busy).arg(state.X_Home_Busy).arg(state.X_ABS_Busy).arg(state.X_HomeComplete).arg(state.X_ABS_Done2).arg(state.X_Spare3).arg(state.X_Spare4);
//    QString str7 = QString("X_Spare5 = %1  X_Spare6 = %2  X_Spare7 = %3  X_Spare8 = %4  X_Spare9 = %5  X_Spare10 = %6  Y_PowerOn_Status = %7  Y_PowerOn_Error = %8\n")
//                .arg(state.X_Spare5).arg(state.X_Spare6).arg(state.X_Spare7).arg(state.X_Spare8).arg(state.X_Spare9).arg(state.X_Spare10).arg(state.Y_PowerOn_Status).arg(state.Y_PowerOn_Error);
//    QString str8 = QString("Y_Reset_Done = %1  Y_Reset_Error = %2  Y_Home_Done = %3  Y_Home_Error = %4  Y_ABS_Done = %5  Y_ABS_Error = %6  Y_JOG_inVelocity = %7  Y_JOG_Error = %8\n")
//                .arg(state.Y_Reset_Done).arg(state.Y_Reset_Error).arg(state.Y_Home_Done).arg(state.Y_Home_Error).arg(state.Y_ABS_Done).arg(state.Y_ABS_Error).arg(state.Y_JOG_inVelocity).arg(state.Y_JOG_Error);
//    QString str9 = QString("Y_Halt_Done = %1  Y_Halt_Err = %2  Y_Readparam_Vaild = %3  Y_Readparam_Err = %4  Y_Reset_Busy = %5  Y_Home_Busy = %6  Y_ABS_Busy = %7  Y_HomeComplete = %8\n")
//                .arg(state.Y_Halt_Done).arg(state.Y_Halt_Err).arg(state.Y_Readparam_Vaild).arg(state.Y_Readparam_Err).arg(state.Y_Reset_Busy).arg(state.Y_Home_Busy).arg(state.Y_ABS_Busy).arg(state.Y_HomeComplete);
//    QString str10 = QString("Y_ABS_Done2 = %1  Y_Spare3 = %2  Y_Spare4 = %3  Y_Spare5 = %4  Y_Spare6 = %5  Y_Spare7 = %6  Y_Spare8 = %7  Y_Spare9 = %8\n")
//                .arg(state.Y_ABS_Done2).arg(state.Y_Spare3).arg(state.Y_Spare4).arg(state.Y_Spare5).arg(state.Y_Spare6).arg(state.Y_Spare7).arg(state.Y_Spare8).arg(state.Y_Spare9);

//    QString str11 = QString("Y_Spare10 = %1\n").arg(state.Y_Spare10);

//    ui->PLCReturn->clear();
//    ui->PLCReturn->appendPlainText(str1);
//    ui->PLCReturn->appendPlainText(str2);
//    ui->PLCReturn->appendPlainText(str3);
//    ui->PLCReturn->appendPlainText(str4);
//    ui->PLCReturn->appendPlainText(str5);
//    ui->PLCReturn->appendPlainText(str6);
//    ui->PLCReturn->appendPlainText(str7);
//    ui->PLCReturn->appendPlainText(str8);
//    ui->PLCReturn->appendPlainText(str9);
//    ui->PLCReturn->appendPlainText(str10);
//    ui->PLCReturn->appendPlainText(str11);
}
void LPCContrlDialog::on_pushButton_setJOG_clicked(){
    float data = ui->lineEdit_setJOG->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
    //plcS7->onSetJOG1(data);
    emit SetJOG1(data);
}
void LPCContrlDialog::on_pushButton_PowerOn_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onPowerOn1();
    if(mPlcState.X_PowerOn_Status){
        emit PowerOff1();
    }else{
        emit PowerOn1();
    }
}
void LPCContrlDialog::on_pushButton_Reset_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onReset1();
    emit Reset1();
}
void  LPCContrlDialog::on_pushButton_Pause_clicked(){
    qDebug()<<mPlcState.X_Halt_Done;
    if(mPlcState.X_Halt_Done){
        emit Pause1_2();
    }else{
        emit Pause1();
    }
}
void LPCContrlDialog::on_pushButton_Home_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
    emit Home1();
}
void LPCContrlDialog::on_pushButton_setABS_clicked(){
    float data = ui->lineEdit_setABS->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABS1(data);
    emit SetABS1(data);
}
void LPCContrlDialog::on_pushButton_JOGPlus_pressed(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGPlus1();
    emit JOGPlus1_1();
}
void LPCContrlDialog::on_pushButton_JOGPlus_released(){
    emit JOGPlus1_2();
}
//void LPCContrlDialog::on_pushButton_JOGMinus_clicked(){
////    std::function<void()> func;
////    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
////    plcS7->Push(new PLCCommand(func));
////    std::function<void()> func2;
////    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
////    plcS7->Push(new PLCCommand(func2));
////    plcS7->onJOGMinus1();
//    emit JOGMinus1();
//}
void LPCContrlDialog::on_pushButton_JOGMinus_pressed(){
    emit JOGMinus1_1();
}
void LPCContrlDialog::on_pushButton_JOGMinus_released(){
    emit JOGMinus1_2();
}
void LPCContrlDialog::on_pushButton_setArray_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetArray1(vec);
    emit SetArray1(vec);
}
void LPCContrlDialog::on_pushButton_ABSLeft_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSLeft1();
    emit ABSLeft1();
}
void LPCContrlDialog::on_pushButton_ABSRight_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSRight1();
    emit ABSRight1();
}
void LPCContrlDialog::on_pushButton_setABSLeft_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABSLeft1();
    emit SetABSLeft1();
}
void LPCContrlDialog::on_pushButton_setABSRight_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABSRight1();
    emit SetABSRight1();
}
////////////////////////////2//////////////////////////////////
void LPCContrlDialog::on_pushButton_setJOG_2_clicked(){
    float data = ui->lineEdit_setJOG_2->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetJOG2(data);
    emit SetJOG2(data);
}
void LPCContrlDialog::on_pushButton_PowerOn_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onPowerOn2();
    if(mPlcState.Y_PowerOn_Status){
        emit PowerOff2();
    }else{
        emit PowerOn2();
    }
}
void LPCContrlDialog::on_pushButton_Reset_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onReset2();
    emit Reset2();
}
void LPCContrlDialog::on_pushButton_Pause_2_clicked(){    
    if(mPlcState.Y_Halt_Done){
        emit Pause2_2();
    }else{
        emit Pause2();
    }
}
void LPCContrlDialog::on_pushButton_Home_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onHome2();
    emit Home2();
}
void LPCContrlDialog::on_pushButton_setABS_2_clicked(){
    float data = ui->lineEdit_setABS_2->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABS2(data);
    emit SetABS2(data);
}
void LPCContrlDialog::on_pushButton_JOGPlus_2_pressed(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGPlus2();
    emit JOGPlus2_1();
}
void LPCContrlDialog::on_pushButton_JOGPlus_2_released(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGPlus2();
    emit JOGPlus2_2();
}
void LPCContrlDialog::on_pushButton_JOGMinus_2_pressed(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGMinus2();
    emit JOGMinus2_1();
}
void LPCContrlDialog::on_pushButton_JOGMinus_2_released(){
    emit JOGMinus2_2();
}
void LPCContrlDialog::on_pushButton_setArray_2_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetArray2(vec);
    emit SetArray2(vec);
}
void LPCContrlDialog::on_pushButton_ABSLeft_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSLeft2();
    emit ABSLeft2();
}
void LPCContrlDialog::on_pushButton_ABSRight_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSRight2();
    emit ABSRight2();
}
void LPCContrlDialog::on_pushButton_setABSLeft_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//     plcS7->onSetABSLeft2();
    emit SetABSLeft2();
}
void LPCContrlDialog::on_pushButton_setABSRight_2_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABSRight2();
    emit SetABSRight2();
}
///////////////////////////3//////////////////////////
void LPCContrlDialog::on_pushButton_setJOG_3_clicked(){
    float data = ui->lineEdit_setJOG_3->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setJOG,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetJOG3(data);
    emit SetJOG3(data);
}
void LPCContrlDialog::on_pushButton_PowerOn_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::PowerOn,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onPowerOn3();
    if(mPlcState.Z_PowerOn_Status){
        emit PowerOff3();
    }else{
        emit PowerOn3();
    }
}
void LPCContrlDialog::on_pushButton_Reset_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Reset_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Reset_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onReset3();
    emit Reset3();
}
void LPCContrlDialog::on_pushButton_Pause_3_clicked(){
    if(mPlcState.Z_Halt_Done){
        emit Pause3_2();
    }else{
        emit Pause3();
    }
}
void LPCContrlDialog::on_pushButton_Home_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::Home_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Home_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onHome3();
    emit Home3();
}
void LPCContrlDialog::on_pushButton_setABS_3_clicked(){
    float data = ui->lineEdit_setABS_3->text().toFloat();
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABS,plcS7,data);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABS3(data);
    emit SetABS3(data);
}
void LPCContrlDialog::on_pushButton_JOGPlus_3_pressed(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGPlus3();
    emit JOGPlus3_1();
}
void LPCContrlDialog::on_pushButton_JOGPlus_3_released(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGPlus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGPlus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGPlus3();
    emit JOGPlus3_2();
}
void LPCContrlDialog::on_pushButton_JOGMinus_3_pressed(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::JOGMinus_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::JOGMinus_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onJOGMinus3();
    emit JOGMinus3_1();
}
void LPCContrlDialog::on_pushButton_JOGMinus_3_released(){
    emit JOGMinus3_2();
}
void LPCContrlDialog::on_pushButton_setArray_3_clicked(){
    QVector<float> vec;
    float value = 0.123f;
    for(int i = 0;i<21;++i){
        vec.append(value + i);
    }
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setArray,plcS7,vec);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetArray3(vec);
    emit SetArray3(vec);
}
void LPCContrlDialog::on_pushButton_ABSLeft_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSLeft_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSLeft_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSLeft3();
    emit ABSLeft3();
}
void LPCContrlDialog::on_pushButton_ABSRight_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::ABSRight_pressed,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::ABSRight_released,plcS7);
//    plcS7->Push(new PLCCommand(func2));
//    plcS7->onABSRight3();
    emit ABSRight3();
}
void LPCContrlDialog::on_pushButton_setABSLeft_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSLeft_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABSLeft3();
    emit SetABSLeft3();
}
void LPCContrlDialog::on_pushButton_setABSRight_3_clicked(){
//    std::function<void()> func;
//    func = std::bind(&PLC_S7::setABSRight_clicked,plcS7);
//    plcS7->Push(new PLCCommand(func));
//    plcS7->onSetABSRight3();
    emit SetABSRight3();
}
void LPCContrlDialog::on_btnSysInitial_pressed(){
    emit SysInitial1();
}
void LPCContrlDialog::on_btnSysInitial_released(){
    emit SysInitial2();
}
void LPCContrlDialog::on_btnSysStart_pressed(){
    emit SysStart1();
}
void LPCContrlDialog::on_btnSysStart_released(){
    emit SysStart2();
}
void LPCContrlDialog::on_btnSysPause_clicked(){
    emit SysPause();
}
void LPCContrlDialog::on_btnSysStop_pressed(){
    emit SysStop1();
}
void LPCContrlDialog::on_btnSysStop_released(){
    emit SysStop2();
}
void LPCContrlDialog::on_btnAlmReset_pressed(){
    emit SysAlmReset1();
}
void LPCContrlDialog::on_btnAlmReset_released(){
    emit SysAlmReset2();
}

void LPCContrlDialog::on_btnSystem_Spare1_clicked(){
    emit SysSpare1();
}
void LPCContrlDialog::on_btnSystem_Spare2_clicked(){
    emit SysSpare2();
}
void LPCContrlDialog::on_btnRight_Laser_clicked(){
    emit RightLaser();
}
void LPCContrlDialog::on_btnLeft_Laser_clicked(){
    emit LeftLaser();
}
void LPCContrlDialog::on_btnInitial_Sequence_clicked(){
    emit InitialSequenceReset();
}
void LPCContrlDialog::on_btnAuto_Sequence_clicked(){
    emit AutoSequenceReset();
}
void LPCContrlDialog::on_btnX_Counter_Rst_clicked(){
    emit X_Counter_Rst();
}
void LPCContrlDialog::on_btnY_Counter_Rst_clicked(){
    emit Y_Counter_Rst();
}
void LPCContrlDialog::on_btnZ_Counter_Rst_clicked(){
    emit Z_Counter_Rst();
}
void LPCContrlDialog::on_btnTotal_Rst_clicked(){
    emit Total_Rst();
}
