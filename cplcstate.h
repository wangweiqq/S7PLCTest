#ifndef CPLCSTATE_H
#define CPLCSTATE_H
#include <QObject>
#include <QMetaType>
#include <functional>
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
//class MyClass:public QObject
//{
//    Q_OBJECT
//public:
//    MyClass() {}
//    MyClass(const MyClass& other){
//        this->isflag = other.isflag;
//    }
//    bool isflag = false;
//};
//struct MyClass
//{
//    bool isflag = false;
//};
//Q_DECLARE_METATYPE(MyClass)

struct PLCState
{
public:
    bool Z_PowerOn_Status = false;
    bool Z_PowerOn_Error = false;
    bool Z_Reset_Done = false;
    bool Z_Reset_Error = false;
    bool Z_Home_Done = false;
    bool Z_Home_Error = false;
    bool Z_ABS_Done = false;
    bool Z_ABS_Error = false;

    bool Z_JOG_inVelocity = false;
    bool Z_JOG_Error = false;
    bool Z_Halt_Done = false;
    bool Z_Halt_Err = false;
    bool Z_Readparam_Vaild = false;
    bool Z_Readparam_Err = false;
    bool Z_Reset_Busy = false;
    bool Z_Home_Busy = false;

    bool Z_ABS_Busy = false;
    bool Z_HomeComplete = false;
    bool Z_ABS_Done2 = false;
    bool Z_Spare3 = false;
    bool Z_Spare4 = false;
    bool Z_Spare5 = false;
    bool Z_Spare6 = false;
    bool Z_Spare7 = false;

    bool Z_Spare8 = false;
    bool Z_Spare9 = false;
    bool Z_Spare10 = false;
    bool X_PowerOn_Status = false;
    bool X_PowerOn_Error = false;
    bool X_Reset_Done = false;
    bool X_Reset_Error = false;
    bool X_Home_Done = false;

    bool X_Home_Error = false;
    bool X_ABS_Done = false;
    bool X_ABS_Error =false;
    bool X_JOG_inVelocity = false;
    bool X_JOG_Error = false;
    bool X_Halt_Done = false;
    bool X_Halt_Err = false;
    bool X_Readparam_Vaild = false;

    bool X_Readparam_Err = false;
    bool X_Reset_Busy = false;
    bool X_Home_Busy = false;
    bool X_ABS_Busy = false;
    bool X_HomeComplete = false;
    bool X_ABS_Done2 = false;
    bool X_Spare3 = false;
    bool X_Spare4 = false;

    bool X_Spare5 = false;
    bool X_Spare6 = false;
    bool X_Spare7 = false;
    bool X_Spare8 = false;
    bool X_Spare9 = false;
    bool X_Spare10 = false;
    bool Y_PowerOn_Status = false;
    bool Y_PowerOn_Error = false;

    bool Y_Reset_Done = false;
    bool Y_Reset_Error = false;
    bool Y_Home_Done = false;
    bool Y_Home_Error = false;
    bool Y_ABS_Done = false;
    bool Y_ABS_Error = false;
    bool Y_JOG_inVelocity = false;
    bool Y_JOG_Error = false;

    bool Y_Halt_Done = false;
    bool Y_Halt_Err = false;
    bool Y_Readparam_Vaild = false;
    bool Y_Readparam_Err = false;
    bool Y_Reset_Busy = false;
    bool Y_Home_Busy = false;
    bool Y_ABS_Busy = false;
    bool Y_HomeComplete = false;

    bool Y_ABS_Done2 = false;
    bool Y_Spare3 = false;
    bool Y_Spare4 = false;
    bool Y_Spare5 = false;
    bool Y_Spare6 = false;
    bool Y_Spare7 = false;
    bool Y_Spare8 = false;
    bool Y_Spare9 = false;

    bool Y_Spare10 = false;

    //初始化完成
    bool Initial_Complete_Lamp = false;
    //系统运行中
    bool Sys_Auto_Lamp = false;
    //系统暂停中
    bool Sys_Pause_Lamp = false;
    //系统停止
    bool Sys_Stop_Lamp = false;
    //异常复位
    bool Sys_RST_Lamp = false;
    bool NOKE_1 = false;
    bool NOKE_2 = false;
    bool NOKE_3 = false;
    bool NOKE_4 = false;
    bool NOKE_5 = false;
    bool NOKE_6 = false;
    bool NOKE_7 = false;
    bool NOKE_8= false;
    bool NOKE_9 = false;
    bool NOKE_10 = false;
    //Z_当前位置
    float Z_ActualPosition = 0;
    //X_当前位置
    float X_ActualPosition = 0;
    //Y_当前位置
    float Y_ActualPosition = 0;
    //Z_目标位置
    float Z_TargetPosition = 0;
    //X_目标位置
    float X_TargetPosition = 0;
    //Y_目标位置
    float Y_TargetPosition = 0;
    //自动流程
    uint16_t Auto_Sequence = 0;
    //初始化流程
    uint16_t Initial_Sequence = 0;
    //X_运动次数
    uint16_t X_Counter = 0;
    //Y_运动次数
    uint16_t Y_Counter = 0;
    //Z_运动次数
    uint16_t Z_Counter = 0;
    //产品信息
    uint32_t Product_Information = 0;
};
Q_DECLARE_METATYPE(PLCState)

class PLCCommand{
public:
    PLCCommand(std::function<void()> func):Func(func){
    }
    void operator()(){
        Func();
    }
private:
    std::function<void()> Func;
};
#endif // CPLCSTATE_H
