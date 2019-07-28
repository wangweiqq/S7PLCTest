#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cplcstate.h"
#include <QList>
class QPushButton;
namespace Ui {
class LPCContrlDialog;
}

class LPCContrlDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LPCContrlDialog(QWidget *parent = 0);
    ~LPCContrlDialog();
signals:
//    void plcState(PLCState state);

    void SetJOG1(float data);
    void PowerOn1();
    void PowerOff1();
    void Reset1();
    //暂停
    void Pause1();
    //取消暂停
    void Pause1_2();
    void Home1();
    void SetABS1(float data);
    void JOGPlus1_1();
    void JOGPlus1_2();
    void JOGMinus1_1();
    void JOGMinus1_2();
    void SetArray1(QVector<float> vec);
    void ABSLeft1();
    void ABSRight1();
    void SetABSLeft1();
    void SetABSRight1();
//////////////////////////2///////////////////////////////
    void SetJOG2(float data);
    void PowerOn2();
    void PowerOff2();
    void Reset2();
    void Pause2();
    //取消暂停
    void Pause2_2();
    void Home2();
    void SetABS2(float data);
    void JOGPlus2_1();
    void JOGPlus2_2();
    void JOGMinus2_1();
    void JOGMinus2_2();
    void SetArray2(QVector<float> vec);
    void ABSLeft2();
    void ABSRight2();
    void SetABSLeft2();
    void SetABSRight2();
//////////////////////////3///////////////////////////////
    void SetJOG3(float data);
    void PowerOn3();
    void PowerOff3();
    void Reset3();
    void Pause3();
    void Pause3_2();
    void Home3();
    void SetABS3(float data);
    void JOGPlus3_1();
    void JOGPlus3_2();
    void JOGMinus3_1();
    void JOGMinus3_2();
    void SetArray3(QVector<float> vec);
    void ABSLeft3();
    void ABSRight3();
    void SetABSLeft3();
    void SetABSRight3();
    ////////////////////////////////////
    void SysInitial1();
    void SysInitial2();
    void SysStart1();
    void SysStart2();
    void SysPause();
    void SysStop1();
    void SysStop2();
    void SysAlmReset1();
    void SysAlmReset2();

    void SysSpare1();
    void SysSpare2();
    void RightLaser();
    void LeftLaser();
    void InitialSequenceReset();
    void AutoSequenceReset();
    void X_Counter_Rst();
    void Y_Counter_Rst();
    void Z_Counter_Rst();
    void Total_Rst();


    void ReadRecipe(QString);
    //No:工单号，xvec：x轴坐标集合
    void WriteRecipe(int No, QVector<float> xvec, QVector<float> yvec, QVector<float> zvec);

    void Type_1_Select();
    void Type_2_Select();
    void Manul_X_Y_Z(uint16_t);
    void LocalOnLine();
public slots:
    /*PLC ip地址链接失败*/
    void onPlcLinkChanged(bool IsOk);
    /*读取PLC状态信息*/
    void onPLCState(PLCState state);


    void on_pushButton_setJOG_clicked();
    void on_pushButton_PowerOn_clicked();
    void on_pushButton_Reset_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Home_clicked();
    void on_pushButton_setABS_clicked();
    void on_pushButton_JOGPlus_pressed();
    void on_pushButton_JOGPlus_released();
    void on_pushButton_JOGMinus_pressed();
    void on_pushButton_JOGMinus_released();
    void on_pushButton_setArray_clicked();
    void on_pushButton_ABSLeft_clicked();
    void on_pushButton_ABSRight_clicked();
    void on_pushButton_setABSLeft_clicked();
    void on_pushButton_setABSRight_clicked();
//////////////////////////2///////////////////////////////
    void on_pushButton_setJOG_2_clicked();
    void on_pushButton_PowerOn_2_clicked();
    void on_pushButton_Reset_2_clicked();
    void on_pushButton_Pause_2_clicked();
    void on_pushButton_Home_2_clicked();
    void on_pushButton_setABS_2_clicked();
    void on_pushButton_JOGPlus_2_pressed();
    void on_pushButton_JOGPlus_2_released();
    void on_pushButton_JOGMinus_2_pressed();
    void on_pushButton_JOGMinus_2_released();
    void on_pushButton_setArray_2_clicked();
    void on_pushButton_ABSLeft_2_clicked();
    void on_pushButton_ABSRight_2_clicked();
    void on_pushButton_setABSLeft_2_clicked();
    void on_pushButton_setABSRight_2_clicked();
//////////////////////////3///////////////////////////////
    void on_pushButton_setJOG_3_clicked();
    void on_pushButton_PowerOn_3_clicked();
    void on_pushButton_Reset_3_clicked();
    void on_pushButton_Pause_3_clicked();
    void on_pushButton_Home_3_clicked();
    void on_pushButton_setABS_3_clicked();
    void on_pushButton_JOGPlus_3_pressed();
    void on_pushButton_JOGPlus_3_released();
    void on_pushButton_JOGMinus_3_pressed();
    void on_pushButton_JOGMinus_3_released();
    void on_pushButton_setArray_3_clicked();
    void on_pushButton_ABSLeft_3_clicked();
    void on_pushButton_ABSRight_3_clicked();
    void on_pushButton_setABSLeft_3_clicked();
    void on_pushButton_setABSRight_3_clicked();
    ////////////////////////////////////////////////////////
    void on_btnSysInitial_pressed();
    void on_btnSysInitial_released();
    void on_btnSysStart_pressed();
    void on_btnSysStart_released();
    void on_btnSysPause_clicked();
    void on_btnSysStop_pressed();
    void on_btnSysStop_released();
    void on_btnAlmReset_pressed();
    void on_btnAlmReset_released();

    void on_btnSystem_Spare1_clicked();
    void on_btnSystem_Spare2_clicked();
    void on_btnRight_Laser_clicked();
    void on_btnLeft_Laser_clicked();
    void on_btnInitial_Sequence_clicked();
    void on_btnAuto_Sequence_clicked();
    void on_btnX_Counter_Rst_clicked();
    void on_btnY_Counter_Rst_clicked();
    void on_btnZ_Counter_Rst_clicked();
    void on_btnTotal_Rst_clicked();

    //读写工单的X，Y,z集合
    void on_btnRRecipe_clicked();
    void on_btnWRecipe_clicked();
    //切换工单编号
    void on_btnType_1_Select_clicked();
    void on_btnType_2_Select_clicked();
    //手动到目标位，要执行3个命令
    void on_btnManul_X_Y_Z_clicked();
    //本地远程
    void on_btnLocalOnLine_clicked();
private:    
    Ui::LPCContrlDialog *ui;
    PLCState mPlcState;
    /*控制PLC button的数组*/
    QList<QPushButton* > btnlist;
};

#endif // WIDGET_H
