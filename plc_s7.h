#ifndef PLC_S7_H
#define PLC_S7_H

#include "snap7.h"
#include <QThread>
#include <QDebug>
#include <QString>
#include <QMutex>
#include <QQueue>
#include <QVector>
#include "cplcstate.h"
union byteToFloat{
     byte b[4];
     float f;
};
union byteToInt16 {
     byte b[2];
     quint16 i;
};
class PLC_S7 : public QThread
{
    Q_OBJECT
public:
    PLC_S7(QString ipAddress);
    ~PLC_S7();
    void StopThread();
    void Push(PLCCommand* func);

    bool Connect();
    int ReadRecipe(float** fxdata,float** fydata,float** fzdata );
    //void WriteRecope(byte* data);
//    MyClass myclass;
signals:
    void plcState(PLCState state);
    /*PLC IP 连接失败*/
    void plcLinkChanged(bool isLinkOk);
//    void myPlCState(PLCState);
//    void myTest(MyClass);
public slots:
//    void onPLCState(PLCState state);
//    void onMyTest(MyClass);

    void onSetJOG1(float data);
    void onPowerOn1();
    void onReset1();
    //暂停
    void onPause1();
    //取消暂停
    void onPause1_2();
    void onPowerOff1();
    void onHome1();
    //读PLC后主动关闭操作
    void onHome1_2();
    void onSetABS1(float data);
    void onJOGPlus1_1();
    void onJOGPlus1_2();
    void onJOGMinus1_1();
    void onJOGMinus1_2();
    void onSetArray1(QVector<float> vec);
    void onX_ABS3_Manul();
    void onABSLeft1();
    void onABSLeft1_2();
    void onABSRight1();
    //读PLC后主动关闭操作
    void onABSRight1_2();
    void onSetABSLeft1();
    void onSetABSRight1();
//////////////////////////2///////////////////////////////
    void onSetJOG2(float data);
    void onPowerOn2();
    void onReset2();
    void onPause2();
    void onPause2_2();
    void onPowerOff2();
    void onHome2();
    //读PLC后主动关闭操作
    void onHome2_2();
    void onSetABS2(float data);
    void onJOGPlus2_1();
    void onJOGPlus2_2();
    void onJOGMinus2_1();
    void onJOGMinus2_2();
    void onSetArray2(QVector<float> vec);
    void onY_ABS3_Manul();
    void onABSLeft2();
    void onABSLeft2_2();
    void onABSRight2();
    //读PLC后主动关闭操作
    void onABSRight2_2();
    void onSetABSLeft2();
    void onSetABSRight2();
//////////////////////////3///////////////////////////////
    void onSetJOG3(float data);
    void onPowerOn3();
    void onReset3();
    void onPause3();
    void onPause3_2();
    void onPowerOff3();
    void onHome3();
    //读PLC后主动关闭操作
    void onHome3_2();
    void onSetABS3(float data);
    void onJOGPlus3_1();
    void onJOGPlus3_2();
    void onJOGMinus3_1();
    void onJOGMinus3_2();
    void onSetArray3(QVector<float> vec);
    void onZ_ABS3_Manul();
    void onABSLeft3();
    void onABSLeft3_2();
    void onABSRight3();
    //读PLC后主动关闭操作
    void onABSRight3_2();
    void onSetABSLeft3();
    void onSetABSRight3();
    /////////////////////////////////////////////////////
    void onSysInitial1();
    void onSysInitial2();
    void onSysStart1();
    void onSysStart2();
    void onSysPause();
    void onSysStop1();
    void onSysStop2();
    void onSysAlmReset1();
    void onSysAlmReset2();

    void onSysSpare1();
    void onSysSpare2();
    void onRightLaser();
    void onLeftLaser();
    void onInitialSequenceReset();
    void onAutoSequenceReset();
    void onX_Counter_Rst();
    void onY_Counter_Rst();
    void onZ_Counter_Rst();
    void onTotal_Rst();

    void onReadRecipe(QString path);
    void onWriteRecope(int No, QVector<float> xvec, QVector<float> yvec, QVector<float> zvec);

    void onType_1_Select();
    void onType_2_Select();
    //手动到目标位，要执行3个命令
    void onManul_X_Y_Z(uint16_t);
    //本地远程
    void onLocalOnLine();
    //测试
    void onTest_Button();
    //手动X，Y,Z目标值
    void onX_HMI_WritePosition(float val);
    void onY_HMI_WritePosition(float val);
    void onZ_HMI_WritePosition(float val);
private:
    inline void ParsePLC();
    inline int ReadData(int dbNum, int offset, int size, void* val);
    inline int WriteData(int dbNum, int offset, int size, void* val);

    inline void X_PowerOn();
    inline void Y_PowerOn();
    inline void Z_PowerOn();

    inline void X_PowerOff();
    inline void Y_PowerOff();
    inline void Z_PowerOff();

    inline void X_Reset_1();
    inline void X_Reset_2();
    inline void Y_Reset_1();
    inline void Y_Reset_2();
    inline void Z_Reset_1();
    inline void Z_Reset_2();

    inline void X_Home_1();
    inline void X_Home_2();
    inline void Y_Home_1();
    inline void Y_Home_2();
    inline void Z_Home_1();
    inline void Z_Home_2();

    inline void X_ABS3_Manul_1();
    inline void X_ABS3_Manul_2();
    inline void Y_ABS3_Manul_1();
    inline void Y_ABS3_Manul_2();
    inline void Z_ABS3_Manul_1();
    inline void Z_ABS3_Manul_2();

    inline void X_ABSLeft_1();
    inline void X_ABSLeft_2();
    inline void Y_ABSLeft_1();
    inline void Y_ABSLeft_2();
    inline void Z_ABSLeft_1();
    inline void Z_ABSLeft_2();

    inline void X_JOGMinus_1();
    inline void X_JOGMinus_2();
    inline void Y_JOGMinus_1();
    inline void Y_JOGMinus_2();
    inline void Z_JOGMinus_1();
    inline void Z_JOGMinus_2();

    inline void X_JOGPlus_1();
    inline void X_JOGPlus_2();
    inline void Y_JOGPlus_1();
    inline void Y_JOGPlus_2();
    inline void Z_JOGPlus_1();
    inline void Z_JOGPlus_2();

    inline void X_ABSRight_1();
    inline void X_ABSRight_2();
    inline void Y_ABSRight_1();
    inline void Y_ABSRight_2();
    inline void Z_ABSRight_1();
    inline void Z_ABSRight_2();

    inline void X_ABS_Speed(float data);
    inline void Y_ABS_Speed(float data);
    inline void Z_ABS_Speed(float data);

    inline void X_JOG_Speed(float data);
    inline void Y_JOG_Speed(float data);
    inline void Z_JOG_Speed(float data);

    inline void X_SetCurPosLeft();
    inline void X_SetCurPosRight();
    inline void Y_SetCurPosLeft();
    inline void Y_SetCurPosRight();
    inline void Z_SetCurPosLeft();
    inline void Z_SetCurPosRight();
    //暂停
    inline void X_Pause_1();
    //取消暂停
    inline void X_Pause_2();
    inline void Y_Pause_1();
    inline void Y_Pause_2();
    inline void Z_Pause_1();
    inline void Z_Pause_2();

    inline void Sys_Initial_1();
    inline void Sys_Initial_2();
    inline void Sys_Start_1();
    inline void Sys_Start_2();
    inline void Sys_Pause_1();
    inline void Sys_Pause_2();
    inline void Sys_Stop_1();
    inline void Sys_Stop_2();
    inline void Sys_AlmReset_1();
    inline void Sys_AlmReset_2();

    inline void Sys_Spare1_1();
    inline void Sys_Spare1_2();
    inline void Sys_Spare2_1();
    inline void Sys_Spare2_2();
    //左激光
    inline void RightLaser_1();
    inline void RightLaser_2();
    //右激光
    inline void LeftLaser_1();
    inline void LeftLaser_2();
    //初始化流程复位
    inline void Initial_Sequence_1();
    inline void Initial_Sequence_2();
    //自动流程复位
    inline void Auto_Sequence_1();
    inline void Auto_Sequence_2();
    //X轴运动次数复位
    inline void X_Counter_Rst_1();
    inline void X_Counter_Rst_2();
    //Y轴运动次数复位
    inline void Y_Counter_Rst_1();
    inline void Y_Counter_Rst_2();
    //Z轴运动次数复位
    inline void Z_Counter_Rst_1();
    inline void Z_Counter_Rst_2();
    //已检测产品数量复位
    inline void Total_Rst_1();
    inline void Total_Rst_2();

    inline void X_WriteTargetPosition(uint16_t data);
    inline void Type_1_Select_1();
    inline void Type_1_Select_2();
    inline void Type_2_Select_1();
    inline void Type_2_Select_2();
    //手动置1
    inline void Manul_X_Y_Z_1();
    //手动置0
    inline void Manul_X_Y_Z_2();

    inline void LocalOnLine_1();
    inline void LocalOnLine_2();

    //测试
    inline void Test_Button_1();
    inline void Test_Button_2();
    //手动X，Y,Z值
    inline void X_HMI_WritePosition(float val);
    inline void Y_HMI_WritePosition(float val);
    inline void Z_HMI_WritePosition(float val);
//    void setABS(float data);
//    void setJOG(float data);



    inline void setArray(QVector<float> vec);
//    void Home_pressed();
//    void Home_released();
//    void Reset_pressed();
//    void Reset_released();
//    void JOGPlus_pressed();
//    void JOGPlus_released();
//    void JOGMinus_pressed();
//    void JOGMinus_released();
//    void ABSLeft_pressed();
//    void ABSLeft_released();
//    void setABSLeft_clicked();
//    void setABSRight_clicked();
//    void ABSRight_pressed();
//    void ABSRight_released();
    //////////////////////////////////////////////////////////////

protected:
    void run();
private:
    //是否允许加入PLC命令
    inline bool AllowCmdPLC();
    inline void SetLinkState(bool isOk);
private:
    /*PLC IP链接成功*/
    bool IsLinkOk = true;
    QString ipAddress;

    TS7Client *S7Client;
    byte DB_Buffer[256];

    QMutex mutex;
    /*停止线程使用*/
    bool mStop = false;
    QQueue<PLCCommand*> listCommand;
    PLCState state;
};

#endif // PLC_S7_H
