#pragma execution_character_set("utf-8")
#include "plc_s7.h"
#include <QtEndian>


float X_CurPosLeft = 50;
float X_CurPosRight= 50;
float Y_CurPosLeft= 50;
float Y_CurPosRight= 50;
float Z_CurPosLeft= 50;
float Z_CurPosRight= 50;

PLC_S7::PLC_S7(QString ipAddress): QThread(nullptr)
{
    S7Client = new TS7Client();
    this->ipAddress = ipAddress;
    listCommand.clear();
    Connect();
//    QObject::connect(this,SIGNAL(plcState(PLCState)),this,SLOT(onPLCState(PLCState)));
//    connect(this,SIGNAL(myPlCState(PLCState)),this,SLOT(onPLCState(PLCState)));
//    connect(this,SIGNAL(myTest(MyClass)),this,SLOT(onMyTest(MyClass)));
}
//void PLC_S7::onPLCState(PLCState state){
//    qDebug()<<"PLC_S7::onPLCState "<<&state;
//}
//void PLC_S7::onMyTest(MyClass ){
//    qDebug()<<"PLC_S7::onMyTest ";
//}
PLC_S7::~PLC_S7()
{
    StopThread();
    delete S7Client;
    S7Client = NULL;
    listCommand.clear();
    qDebug()<<"~PLC_S7";
}
void PLC_S7::StopThread(){
    if(this->isRunning()){
        mStop = true;
        this->wait();
    }
}
bool PLC_S7::Connect()
{

    int bl = S7Client->ConnectTo(ipAddress.toStdString().c_str(), 0, 0);
    qDebug()<<ipAddress.toStdString().c_str()<<",bl = "<<bl;
//    if(bl){
//        //PowerOn();
//    }
    return bl == 0;
//    if (!S7Client->Connected())
//    {
//        int val = S7Client->ConnectTo(ipAddress.toStdString().c_str(), 0, 0);
//        qDebug()<<ipAddress.toStdString().c_str()<<",val = "<<val;
//        return val;
//        // set power on
//        // TO DO CODE
//    }
//    else
//    {
//        return S7Client->Connected();
//    }
}

int PLC_S7::ReadData(int dbNum, int offset, int size, void *val)
{
//    QMutexLocker locker(&mutex);
    if (S7Client->Connected())
    {
        int rtnVal;
        rtnVal = S7Client->DBRead(dbNum, offset, size, val);
        if (rtnVal != 0)
        {
            // qDebug() << "Error read from DB:"
            //          << "1 " << QString::number(rtnVal);
        }
        return rtnVal;
    }
    else
    {
        return -1;
    }
}

int PLC_S7::WriteData(int dbNum, int offset, int size, void *val)
{
    //QMutexLocker locker(&mutex);
    if (S7Client->Connected())
    {
        qDebug()<<"WriteData";
        int rtnVal = S7Client->DBWrite(dbNum, offset, size, val);
        // qDebug() << "Write to DB" << dbNum << ".DBB" << offset << ", rtnVal= " << QString::number(rtnVal);
        return rtnVal;
    }
    else
    {
        return -1;
    }
}
//是否允许加入PLC命令
bool PLC_S7::AllowCmdPLC(){
    bool bl = listCommand.isEmpty() && S7Client->Connected();
    if(!bl){
        qDebug()<<"当前命令不能加入队列："<<"listCommand size = "<<listCommand.size()+",S7Client->Connected() = "<<S7Client->Connected();
    }
    return bl;
//    if(listCommand.isEmpty() && S7Client->Connected()){
//        return true;
//    }
//    return false;
}
void PLC_S7::SetLinkState(bool isOk){
    if(isOk != IsLinkOk){
        IsLinkOk = isOk;
        emit plcLinkChanged(IsLinkOk);
        if(IsLinkOk){
            qDebug()<<"S7Client->Connected() true";
        }else{
            qDebug()<<"S7Client->Connected() false";
        }
    }
}
void PLC_S7::run()
{
    while (!mStop)
    {
        mutex.lock();
//        qDebug()<<"run Locked ";
        if (S7Client->Connected())
        {
//            qDebug()<<"SetLinkState1";
            SetLinkState(true);
//            qDebug()<<"SetLinkState2";

            //1、写软件状态（byte数组）
            //2、读PLC状态（byte数组）
            //3、发送信号处理读出信息（刷主界面状态信息）
            //注意此线程中必须先读后写，写入有可能用到读出的数据
//            qDebug()<<"ParsePLC1";
            mutex.unlock();
            ParsePLC();
            mutex.lock();
//            qDebug()<<"ParsePLC2";
//             ReadData();
            // qDebug() << "connected";
            if(!listCommand.isEmpty()){
                //执行PLC命令
//                qDebug()<<"执行PLC命令1";
                PLCCommand* command = listCommand.dequeue();
                (*command)();
                delete command;
//                qDebug()<<"执行PLC命令2";
            }
        }
        else
        {
            SetLinkState(false);
            Connect();
        }
        mutex.unlock();
//        qDebug()<<"run unLock";
//        qDebug()<<"PLC_S7::run";
        this->msleep(ulong(100.0));
//        qDebug()<<"PLC_S7::run msleep";
    }
    qDebug()<<"PLC_S7::run Exit";
}
void PLC_S7::ParsePLC(){
    mutex.lock();
    byte data_array[12] = {0};
    int size = sizeof(data_array);
    ReadData(16, 0, size, data_array);
    float fdata_array[6]= {0};
    size = sizeof(fdata_array);
    ReadData(11, 0, size, fdata_array);
    uint16_t sdata_array[5] = {0};
    size = sizeof(sdata_array);
    ReadData(11, 22, size, sdata_array);
    uint32_t idata = 0;
    size = sizeof(idata);
    ReadData(11, 34, size, &idata);
//    setDB16_0(data_array[0]);
    mutex.unlock();

    state.Z_PowerOn_Status = (data_array[0] & BIT0) != 0;
    state.Z_PowerOn_Error = (data_array[0] & BIT1) != 0;
    state.Z_Reset_Done = (data_array[0] & BIT2) != 0;
    state.Z_Reset_Error = (data_array[0] & BIT3) != 0;
    state.Z_Home_Done = (data_array[0] & BIT4) != 0;
    state.Z_Home_Error = (data_array[0] & BIT5) != 0;
    state.Z_ABS_Done = (data_array[0] & BIT6) != 0;
    state.Z_ABS_Error = (data_array[0] & BIT7) != 0;

    state.Z_JOG_inVelocity =    (data_array[1] & BIT0) != 0;
    state.Z_JOG_Error =         (data_array[1] & BIT1) != 0;
    state.Z_Halt_Done =         (data_array[1] & BIT2) != 0;
    state.Z_Halt_Err =          (data_array[1] & BIT3) != 0;
    state.Z_Readparam_Vaild =   (data_array[1] & BIT4) != 0;
    state.Z_Readparam_Err =     (data_array[1] & BIT5) != 0;
    state.Z_Reset_Busy =        (data_array[1] & BIT6) != 0;
    state.Z_Home_Busy =         (data_array[1] & BIT7) != 0;

    state.Z_ABS_Busy =          (data_array[2] & BIT0) != 0;
    state.Z_HomeComplete =      (data_array[2] & BIT1) != 0;
    state.Z_ABS_Done2 =            (data_array[2] & BIT2) != 0;
    state.Z_Spare3 =            (data_array[2] & BIT3) != 0;
    state.Z_Spare4 =            (data_array[2] & BIT4) != 0;
    state.Z_Spare5 =            (data_array[2] & BIT5) != 0;
    state.Z_Spare6 =            (data_array[2] & BIT6) != 0;
    state.Z_Spare7 =            (data_array[2] & BIT7) != 0;

    state.Z_Spare8 =            (data_array[3] & BIT0) != 0;
    state.Z_Spare9 =            (data_array[3] & BIT1) != 0;
    state.Z_Spare10 =           (data_array[3] & BIT2) != 0;
    state.X_PowerOn_Status =    (data_array[3] & BIT3) != 0;
    state.X_PowerOn_Error =     (data_array[3] & BIT4) != 0;
    state.X_Reset_Done =        (data_array[3] & BIT5) != 0;
    state.X_Reset_Error =       (data_array[3] & BIT6) != 0;
    state.X_Home_Done =         (data_array[3] & BIT7) != 0;

    state.X_Home_Error =        (data_array[4] & BIT0) != 0;
    state.X_ABS_Done =          (data_array[4] & BIT1) != 0;
    state.X_ABS_Error =         (data_array[4] & BIT2) != 0;
    state.X_JOG_inVelocity =    (data_array[4] & BIT3) != 0;
    state.X_JOG_Error =         (data_array[4] & BIT4) != 0;
    state.X_Halt_Done =         (data_array[4] & BIT5) != 0;
    state.X_Halt_Err =          (data_array[4] & BIT6) != 0;
    state.X_Readparam_Vaild =   (data_array[4] & BIT7) != 0;

    state.X_Readparam_Err =     (data_array[5] & BIT0) != 0;
    state.X_Reset_Busy =        (data_array[5] & BIT1) != 0;
    state.X_Home_Busy =         (data_array[5] & BIT2) != 0;
    state.X_ABS_Busy =          (data_array[5] & BIT3) != 0;
    state.X_HomeComplete =      (data_array[5] & BIT4) != 0;
    state.X_ABS_Done2 =         (data_array[5] & BIT5) != 0;
    state.X_Spare3 =            (data_array[5] & BIT6) != 0;
    state.X_Spare4 =            (data_array[5] & BIT7) != 0;

    state.X_Spare5 =            (data_array[6] & BIT0) != 0;
    state.X_Spare6 =            (data_array[6] & BIT1) != 0;
    state.X_Spare7 =            (data_array[6] & BIT2) != 0;
    state.X_Spare8 =            (data_array[6] & BIT3) != 0;
    state.X_Spare9 =            (data_array[6] & BIT4) != 0;
    state.X_Spare10 =           (data_array[6] & BIT5) != 0;
    state.Y_PowerOn_Status =    (data_array[6] & BIT6) != 0;
    state.Y_PowerOn_Error =     (data_array[6] & BIT7) != 0;

    state.Y_Reset_Done =        (data_array[7] & BIT0) != 0;
    state.Y_Reset_Error =       (data_array[7] & BIT1) != 0;
    state.Y_Home_Done =         (data_array[7] & BIT2) != 0;
    state.Y_Home_Error =        (data_array[7] & BIT3) != 0;
    state.Y_ABS_Done =          (data_array[7] & BIT4) != 0;
    state.Y_ABS_Error =         (data_array[7] & BIT5) != 0;
    state.Y_JOG_inVelocity =    (data_array[7] & BIT6) != 0;
    state.Y_JOG_Error =         (data_array[7] & BIT7) != 0;

    state.Y_Halt_Done =         (data_array[8] & BIT0) != 0;
    state.Y_Halt_Err =          (data_array[8] & BIT1) != 0;
    state.Y_Readparam_Vaild =   (data_array[8] & BIT2) != 0;
    state.Y_Readparam_Err =     (data_array[8] & BIT3) != 0;
    state.Y_Reset_Busy =        (data_array[8] & BIT4) != 0;
    state.Y_Home_Busy =         (data_array[8] & BIT5) != 0;
    state.Y_ABS_Busy =          (data_array[8] & BIT6) != 0;
    state.Y_HomeComplete =      (data_array[8] & BIT7) != 0;

    state.Y_ABS_Done2 =         (data_array[9] & BIT0) != 0;
    state.Y_Spare3 =            (data_array[9] & BIT1) != 0;
    state.Y_Spare4 =            (data_array[9] & BIT2) != 0;
    state.Y_Spare5 =            (data_array[9] & BIT3) != 0;
    state.Y_Spare6 =            (data_array[9] & BIT4) != 0;
    state.Y_Spare7 =            (data_array[9] & BIT5) != 0;
    state.Y_Spare8 =            (data_array[9] & BIT6) != 0;
    state.Y_Spare9 =            (data_array[9] & BIT7) != 0;

    state.Y_Spare10 =           (data_array[10] & BIT0) != 0;    
    //初始化完成
    state.Initial_Complete_Lamp =(data_array[10] & BIT1) != 0;
    //系统运行中
    state.Sys_Auto_Lamp =       (data_array[10] & BIT2) != 0;
    //系统暂停中
    state.Sys_Pause_Lamp =      (data_array[10] & BIT3) != 0;
    //系统停止
    state.Sys_Stop_Lamp =       (data_array[10] & BIT4) != 0;
    //异常复位
    state.Sys_RST_Lamp =        (data_array[10] & BIT5) != 0;
    state.NOKE_1 =              (data_array[10] & BIT6) != 0;
    state.NOKE_2 =              (data_array[10] & BIT7) != 0;

    state.NOKE_3 =              (data_array[11] & BIT0) != 0;
    state.NOKE_4 =              (data_array[11] & BIT1) != 0;
    state.NOKE_5 =              (data_array[11] & BIT2) != 0;
    state.NOKE_6 =              (data_array[11] & BIT3) != 0;
    state.NOKE_7 =              (data_array[11] & BIT4) != 0;
    state.NOKE_8=               (data_array[11] & BIT5) != 0;
    state.NOKE_9 =              (data_array[11] & BIT6) != 0;
    state.NOKE_10 =             (data_array[11] & BIT7) != 0;



    //Z_当前位置
    state.Z_ActualPosition = qToLittleEndian<float>(fdata_array[0]);
    //X_当前位置
    state.X_ActualPosition = qToLittleEndian<float>(fdata_array[1]);
    //Y_当前位置
    state.Y_ActualPosition = qToLittleEndian<float>(fdata_array[2]);
    //Z_目标位置
    state.Z_TargetPosition = qToLittleEndian<float>(fdata_array[3]);
    //X_目标位置
    state.X_TargetPosition = qToLittleEndian<float>(fdata_array[4]);
    //Y_目标位置
    state.Y_TargetPosition = qToLittleEndian<float>(fdata_array[5]);
    //自动流程
    state.Auto_Sequence = qToLittleEndian<quint16>(sdata_array[0]);
    //初始化流程
    state.Initial_Sequence = qToLittleEndian<quint16>(sdata_array[1]);
    //X_运动次数
    state.X_Counter = qToLittleEndian<quint16>(sdata_array[2]);
    //Y_运动次数
    state.Y_Counter = qToLittleEndian<quint16>(sdata_array[3]);
    //Z_运动次数
    state.Z_Counter = qToLittleEndian<quint16>(sdata_array[4]);
    //产品信息
    state.Product_Information = qToLittleEndian<quint32>(idata);
//    myclass.isflag = true;
//    emit myTest(myclass);
//    QVariant DataVar;
//    DataVar.setValue(state);
    emit plcState(state);

    if(state.X_PowerOn_Status && state.X_PowerOn_Error){
        onPowerOff1();
    }
    if(state.X_PowerOn_Status && state.Y_PowerOn_Error){
        onPowerOff2();
    }
    if(state.X_PowerOn_Status && state.Z_PowerOn_Error){
        onPowerOff3();
    }
    //主动关闭Home键
    if(state.X_Home_Done || state.X_Home_Error){
        //表示X轴Home动作完成需要把Home键置0
        onHome1_2();
    }
    if(state.Y_Home_Done || state.Y_Home_Error){
        //表示Y轴Home动作完成需要把Home键置0
        onHome2_2();
    }
    if(state.Z_Home_Done || state.Z_Home_Error){
        //表示Y轴Home动作完成需要把Home键置0
        onHome3_2();
    }
//    if(state.X_ABS_Error){
//        onABSLeft1_2();
//        onABSRight1_2();
//    }else{
        //主动关闭Go Left和Go Right键
        if(state.X_ABS_Done ){
            //表示X轴Go Left完成
            onABSLeft1_2();
        }
        if(state.X_ABS_Done2 ){
            //表示X轴Go Right完成
            onABSRight1_2();
        }
//    }
//    if(state.Y_ABS_Error){
//        onABSLeft2_2();
//        onABSRight2_2();
//    }else{
        if(state.Y_ABS_Done){
            //表示Y轴Go Left完成
            onABSLeft2_2();
        }
        if(state.Y_ABS_Done2){
            //表示Y轴Go Right完成
            onABSRight2_2();
        }
//    }
//    if(state.Z_ABS_Error){
//        onABSLeft3_2();
//        onABSRight3_2();
//    }else{
        if(state.Z_ABS_Done){
            //表示Z轴Go Left完成
            onABSLeft3_2();
        }
        if(state.Z_ABS_Done2){
            //表示Z轴Go Right完成
            onABSRight3_2();
        }
//    }
    if(state.X_Halt_Err){
        onPause1_2();
    }
    if(state.Y_Halt_Err){
        onPause2_2();
    }
    if(state.Z_Halt_Err){
        onPause3_2();
    }
//    emit myPlCState(state);
//    qDebug()<<"thread & state = "<< &state;
//    QString str = QString("Z_PowerOn_Status = %1\nZ_PowerOn_Error = %2\nZ_Reset_Done = %3\nZ_Reset_Error = %4\nZ_Home_Done = %5\nZ_Home_Error = %6\nZ_ABS_Done = %7\nZ_ABS_Error = %8")
//            .arg(Z_PowerOn_Status).arg(Z_PowerOn_Error).arg(Z_Reset_Done).arg(Z_Reset_Error).arg(Z_Home_Done).arg(Z_Home_Error).arg(Z_ABS_Done).arg(Z_ABS_Error);
////    qDebug()<<str;
//    emit plcState(str);
}
//////////////////////////////////////////////////////////////////////
void PLC_S7::onSetJOG1(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_JOG_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetJOG1"<<":data = "<<data;
}
void PLC_S7::onPowerOn1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_PowerOn,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOn1";
}
void PLC_S7::onReset1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_Reset_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_Reset_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onReset1";
}
void PLC_S7::onPause1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_Pause_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPause1";
}
void PLC_S7::onPause1_2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_Pause_2,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPause1_2";
}
void PLC_S7::onPowerOff1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_PowerOff,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOff1";
}
void PLC_S7::onHome1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_Home_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::X_Home_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onHome1";
}
void PLC_S7::onHome1_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_Home_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onHome1_2";
}
void PLC_S7::onSetABS1(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_ABS_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABS1";
}
void PLC_S7::onJOGPlus1_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_JOGPlus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGPlus1_1";
}
void PLC_S7::onJOGPlus1_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_JOGPlus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGPlus1_2";
}
void PLC_S7::onJOGMinus1_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_JOGMinus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGMinus1_1";
}
void PLC_S7::onJOGMinus1_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_JOGMinus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGMinus1_2";
}
void PLC_S7::onSetArray1(QVector<float> vec){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::setArray,this,vec);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetArray1";
}
void PLC_S7::onABSLeft1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_ABSLeft_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::X_ABSLeft_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft1";
}
void PLC_S7::onABSLeft1_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_ABSLeft_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft1_2";
}
void PLC_S7::onABSRight1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_ABSRight_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::X_ABSRight_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight1";
}
void PLC_S7::onABSRight1_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_ABSRight_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight1_2";
}
void PLC_S7::onSetABSLeft1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_SetCurPosLeft,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABSLeft1";
}
void PLC_S7::onSetABSRight1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_SetCurPosRight,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABSRight1";
}
//////////////////////////2///////////////////////////////
void PLC_S7::onSetJOG2(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_JOG_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetJOG2"<<",data = "<<data;
}
void PLC_S7::onPowerOn2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_PowerOn,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOn2";
}
void PLC_S7::onReset2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_Reset_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_Reset_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onReset2";
}
void PLC_S7::onPause2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_Pause_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPause2";
}
void PLC_S7::onPause2_2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_Pause_2,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPause2_2";
}
void PLC_S7::onPowerOff2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_PowerOff,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOff2";
}
void PLC_S7::onHome2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_Home_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Y_Home_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onHome2";
}
void PLC_S7::onHome2_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_Home_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onHome2_2";
}
void PLC_S7::onSetABS2(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_ABS_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABS2"<<",data = "<<data;
}
void PLC_S7::onJOGPlus2_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_JOGPlus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGPlus2_1";
}
void PLC_S7::onJOGPlus2_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_JOGPlus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGPlus2_2";
}
void PLC_S7::onJOGMinus2_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_JOGMinus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGMinus2_1";
}
void PLC_S7::onJOGMinus2_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_JOGMinus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGMinus2_2";
}
void PLC_S7::onSetArray2(QVector<float> vec){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::setArray,this,vec);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetArray2";
}
void PLC_S7::onABSLeft2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_ABSLeft_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Y_ABSLeft_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft2";
}
void PLC_S7::onABSLeft2_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_ABSLeft_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft2_2";
}
void PLC_S7::onABSRight2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_ABSRight_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Y_ABSRight_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight2";
}
void PLC_S7::onABSRight2_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_ABSRight_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight2_2";
}
void PLC_S7::onSetABSLeft2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_SetCurPosLeft,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABSLeft2";
}
void PLC_S7::onSetABSRight2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_SetCurPosRight,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABSRight2";
}
//////////////////////////3///////////////////////////////
void PLC_S7::onSetJOG3(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_JOG_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetJOG3";
}
void PLC_S7::onPowerOn3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_PowerOn,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOn3";
}
void PLC_S7::onReset3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_Reset_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_Reset_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onReset3";
}
void PLC_S7::onPause3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_Pause_1,this);
    this->Push(new PLCCommand(func));
     qDebug()<<"PLC_S7::onPause3";
}
void PLC_S7::onPause3_2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_Pause_2,this);
    this->Push(new PLCCommand(func));
     qDebug()<<"PLC_S7::onPause3_2";
}
void PLC_S7::onPowerOff3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_PowerOff,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onPowerOff3";
}
void PLC_S7::onHome3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_Home_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Z_Home_2,this);
//    this->Push(new PLCCommand(func2));
     qDebug()<<"PLC_S7::onHome3";
}
void PLC_S7::onHome3_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_Home_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onHome3_2";
}
void PLC_S7::onSetABS3(float data){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_ABS_Speed,this,data);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABS3";
}
void PLC_S7::onJOGPlus3_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_JOGPlus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGPlus3_1";
}
void PLC_S7::onJOGPlus3_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_JOGPlus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGPlus3_2";
}
void PLC_S7::onJOGMinus3_1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_JOGMinus_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onJOGMinus3_1";
}
void PLC_S7::onJOGMinus3_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_JOGMinus_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onJOGMinus3_2";
}
void PLC_S7::onSetArray3(QVector<float> vec){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::setArray,this,vec);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetArray3";
}
void PLC_S7::onABSLeft3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_ABSLeft_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Z_ABSLeft_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft3";
}
void PLC_S7::onABSLeft3_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_ABSLeft_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSLeft3_2";
}
void PLC_S7::onABSRight3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_ABSRight_1,this);
    this->Push(new PLCCommand(func));
//    std::function<void()> func2;
//    func2 = std::bind(&PLC_S7::Z_ABSRight_2,this);
//    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight3";
}
void PLC_S7::onABSRight3_2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_ABSRight_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onABSRight3_2";
}
void PLC_S7::onSetABSLeft3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_SetCurPosLeft,this);
    this->Push(new PLCCommand(func));
     qDebug()<<"PLC_S7::onSetABSLeft3";
}
void PLC_S7::onSetABSRight3(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_SetCurPosRight,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSetABSRight3";
}
//////////////////////////////////////////////////////////////////////
void PLC_S7::onSysInitial1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Initial_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSysInitial1";
}
void PLC_S7::onSysInitial2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Initial_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysInitial2";
}
void PLC_S7::onSysStart1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Start_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSysStart1";
}
void PLC_S7::onSysStart2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Start_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysStart2";
}
void PLC_S7::onSysPause(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Pause_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Pause_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysPause";
}
void PLC_S7::onSysStop1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Stop_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSysStop1";
}
void PLC_S7::onSysStop2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Stop_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysStop2";
}
void PLC_S7::onSysAlmReset1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_AlmReset_1,this);
    this->Push(new PLCCommand(func));
    qDebug()<<"PLC_S7::onSysAlmReset1";
}
void PLC_S7::onSysAlmReset2(){
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_AlmReset_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysAlmReset2";
}
void PLC_S7::onSysSpare1(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Spare1_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Spare1_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysSpare1";
}
void PLC_S7::onSysSpare2(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Sys_Spare2_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Sys_Spare2_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onSysSpare2";
}
void PLC_S7::onRightLaser(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::RightLaser_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::RightLaser_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onRightLaser";
}
void PLC_S7::onLeftLaser(){
//    if(!AllowCmdPLC()){
//        return;
//    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::LeftLaser_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::LeftLaser_2,this);
    this->Push(new PLCCommand(func2));
    qDebug()<<"PLC_S7::onRightLaser";
}
void PLC_S7::onInitialSequenceReset(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Initial_Sequence_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Initial_Sequence_2,this);
    this->Push(new PLCCommand(func2));
}
void PLC_S7::onAutoSequenceReset(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Auto_Sequence_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Auto_Sequence_2,this);
    this->Push(new PLCCommand(func2));
}
void PLC_S7::onX_Counter_Rst(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::X_Counter_Rst_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::X_Counter_Rst_2,this);
    this->Push(new PLCCommand(func2));
}
void PLC_S7::onY_Counter_Rst(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Y_Counter_Rst_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Y_Counter_Rst_2,this);
    this->Push(new PLCCommand(func2));
}
void PLC_S7::onZ_Counter_Rst(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Z_Counter_Rst_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Z_Counter_Rst_2,this);
    this->Push(new PLCCommand(func2));
}
void PLC_S7::onTotal_Rst(){
    //    if(!AllowCmdPLC()){
    //        return;
    //    }
    std::function<void()> func;
    func = std::bind(&PLC_S7::Total_Rst_1,this);
    this->Push(new PLCCommand(func));
    std::function<void()> func2;
    func2 = std::bind(&PLC_S7::Total_Rst_2,this);
    this->Push(new PLCCommand(func2));
}
///////////////////////////////////////////////////////////////
/*命令入队，在线程中写入PLC*/
void PLC_S7::Push(PLCCommand* func){
    QMutexLocker locker(&mutex);
//    if(AllowCmdPLC()){
        listCommand.enqueue(func);
//    }else{
//        qDebug()<<"当前命令不能加入队列："<<"listCommand size = "<<listCommand.size()+",S7Client->Connected() = "<<S7Client->Connected();
//    }
}
//void PLC_S7::PowerOn(){
//    qDebug()<<"PLC_S7::PowerOn()";
//    byte data = 0x01;
//    WriteData(2, 0, 1, &data);
//}
void PLC_S7::X_PowerOn(){
    qDebug()<<"PLC_S7::X_PowerOn";
    byte rdata = 0;
    ReadData(2, 1, 1, &rdata);
    byte data = rdata | BIT7;//0x80;
    WriteData(2, 1, 1, &data);
}
void PLC_S7::Y_PowerOn(){
    qDebug()<<"PLC_S7::Y_PowerOn";
    byte rdata = 0;
    ReadData(2, 3, 1, &rdata);
    byte data = rdata | BIT6;//0x40;
    WriteData(2, 3, 1, &data);
}
void PLC_S7::Z_PowerOn(){
    qDebug()<<"PLC_S7::Z_PowerOn";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT0;//0x01;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::X_PowerOff(){
    qDebug()<<"PLC_S7::X_PowerOff";
    byte rdata = 0;
    ReadData(2, 1, 1, &rdata);
    byte data = rdata & ~BIT7;//0x00;
    WriteData(2, 1, 1, &data);
}
void PLC_S7::Y_PowerOff(){
    qDebug()<<"PLC_S7::Y_PowerOff";
    byte rdata = 0;
    ReadData(2, 3, 1, &rdata);
    byte data = rdata & ~BIT6;//0x00;
    WriteData(2, 3, 1, &data);
}
void PLC_S7::Z_PowerOff(){
    qDebug()<<"PLC_S7::Z_PowerOff";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT0;//0x00;
    WriteData(2, 0, 1, &data);
}
//void PLC_S7::Reset_pressed(){
//    byte data = 0x09;
//    WriteData(2, 0, 1, &data);
//}
//void PLC_S7::Reset_released(){
//    byte data = 0x01;
//    WriteData(2, 0, 1, &data);
//}
void PLC_S7::X_Reset_1(){
    qDebug()<<"PLC_S7::X_Reset_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT0;//0x01;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_Reset_2(){
    qDebug()<<"PLC_S7::X_Reset_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT0;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_Reset_1(){
    qDebug()<<"PLC_S7::Y_Reset_1";
    byte rdata = 0;
    ReadData(2, 3, 1, &rdata);
    byte data = rdata | BIT7;//0xC0;
    WriteData(2, 3, 1, &data);
}
void PLC_S7::Y_Reset_2(){
    qDebug()<<"PLC_S7::Y_Reset_2";
    byte rdata = 0;
    ReadData(2, 3, 1, &rdata);
    byte data = rdata & ~BIT7;//0x40;
    WriteData(2, 3, 1, &data);
}
void PLC_S7::Z_Reset_1(){
    qDebug()<<"PLC_S7::Z_Reset_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT1;//0x03;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_Reset_2(){
    qDebug()<<"PLC_S7::Z_Reset_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT1;//0x01;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::X_Pause_1(){
    qDebug()<<"PLC_S7::X_Pause_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT7;//0x80;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_Pause_2(){
    qDebug()<<"PLC_S7::X_Pause_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT7;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_Pause_1(){
    qDebug()<<"PLC_S7::Y_Pause_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT6;//0x40;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_Pause_2(){
    qDebug()<<"PLC_S7::Y_Pause_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT6;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_Pause_1(){
    qDebug()<<"PLC_S7::Z_Pause_1";
    byte rdata = 0;
    ReadData(2, 1, 1, &rdata);
    byte data = rdata | BIT0;//0x81;
    WriteData(2, 1, 1, &data);
}
void PLC_S7::Z_Pause_2(){
    qDebug()<<"PLC_S7::Z_Pause_2";
    byte rdata = 0;
    ReadData(2, 1, 1, &rdata);
    byte data = rdata & ~BIT0; //0x80;
    WriteData(2, 1, 1, &data);
}
//void PLC_S7::Home_pressed(){
//    byte data = 0x41;
//    WriteData(2, 0, 1, &data);
//}
//void PLC_S7::Home_released(){
//    byte data = 0x01;
//    WriteData(2, 0, 1, &data);
//}
void PLC_S7::X_Home_1(){
    qDebug()<<"PLC_S7::X_Home_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT1;//0x02;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_Home_2(){
    qDebug()<<"PLC_S7::X_Home_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT1;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_Home_1(){
    qDebug()<<"PLC_S7::Y_Home_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT0;//0x01;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_Home_2(){
    qDebug()<<"PLC_S7::Y_Home_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT0;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_Home_1(){
    qDebug()<<"PLC_S7::Z_Home_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT2;//0x05;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_Home_2(){
    qDebug()<<"PLC_S7::Z_Home_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT2;//0x01;
    WriteData(2, 0, 1, &data);
}

//void PLC_S7::ABSLeft_pressed(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x02;
//    WriteData(2, 0, 2, data);
//}
//void PLC_S7::ABSLeft_released(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x00;
//    WriteData(2, 0, 2, data);
//}
void PLC_S7::X_ABSLeft_1(){
    qDebug()<<"PLC_S7::X_ABSLeft_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT2;//0x04;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_ABSLeft_2(){
    qDebug()<<"PLC_S7::X_ABSLeft_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT2;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_ABSLeft_1(){
    qDebug()<<"PLC_S7::Y_ABSLeft_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT1;//0x02;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_ABSLeft_2(){
    qDebug()<<"PLC_S7::Y_ABSLeft_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT1;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_ABSLeft_1(){
    qDebug()<<"PLC_S7::Z_ABSLeft_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT3;//0x09;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_ABSLeft_2(){
    qDebug()<<"PLC_S7::Z_ABSLeft_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT3;//0x01;
    WriteData(2, 0, 1, &data);
}

//void PLC_S7::JOGMinus_pressed(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x20;
//    WriteData(2, 0, 2, data);
//}
//void PLC_S7::JOGMinus_released(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x00;
//    WriteData(2, 0, 2, data);
//}
void PLC_S7::X_JOGMinus_1(){
    qDebug()<<"PLC_S7::X_JOGMinus_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT4;//0x08;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_JOGMinus_2(){
    qDebug()<<"PLC_S7::X_JOGMinus_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT4;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_JOGMinus_1(){
    qDebug()<<"PLC_S7::Y_JOGMinus_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT3;//0x04;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_JOGMinus_2(){
    qDebug()<<"PLC_S7::Y_JOGMinus_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT3;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_JOGMinus_1(){
    qDebug()<<"PLC_S7::Z_JOGMinus_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT5;//0x11;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_JOGMinus_2(){
    qDebug()<<"PLC_S7::Z_JOGMinus_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT5;//0x01;
    WriteData(2, 0, 1, &data);
}
//void PLC_S7::JOGPlus_pressed(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x10;
//    WriteData(2, 0, 2, data);
//}
//void PLC_S7::JOGPlus_released(){
//    byte data[2];
//    data[0] = 0x01;
//    data[1] = 0x00;
//    WriteData(2, 0, 2, data);
//}
void PLC_S7::X_JOGPlus_1(){
    qDebug()<<"PLC_S7::X_JOGPlus_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT3;//0x10;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_JOGPlus_2(){
    qDebug()<<"PLC_S7::X_JOGPlus_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT3;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_JOGPlus_1(){
    qDebug()<<"PLC_S7::Y_JOGPlus_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT2;//0x08;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_JOGPlus_2(){
    qDebug()<<"PLC_S7::Y_JOGPlus_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT2;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_JOGPlus_1(){
    qDebug()<<"PLC_S7::Z_JOGPlus_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT4;//0x21;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_JOGPlus_2(){
    qDebug()<<"PLC_S7::Z_JOGPlus_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT4;//0x01;
    WriteData(2, 0, 1, &data);
}

//void PLC_S7::ABSRight_pressed(){
//    byte data[3];
//    data[0] = 0x01;
//    data[1] = 0x00;
//    data[2] = 0x08;
//    WriteData(2, 0, 3, data);
//}
//void PLC_S7::ABSRight_released(){
//    byte data[3];
//    data[0] = 0x01;
//    data[1] = 0x00;
//    data[2] = 0x00;
//    WriteData(2, 0, 3, data);
//}
void PLC_S7::X_ABSRight_1(){
    qDebug()<<"PLC_S7::X_ABSRight_1";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata | BIT6;//0x40;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::X_ABSRight_2(){
    qDebug()<<"PLC_S7::X_ABSRight_2";
    byte rdata = 0;
    ReadData(2, 2, 1, &rdata);
    byte data = rdata & ~BIT6;//0x00;
    WriteData(2, 2, 1, &data);
}
void PLC_S7::Y_ABSRight_1(){
    qDebug()<<"PLC_S7::Y_ABSRight_1";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata | BIT5;//0x20;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Y_ABSRight_2(){
    qDebug()<<"PLC_S7::Y_ABSRight_2";
    byte rdata = 0;
    ReadData(2, 4, 1, &rdata);
    byte data = rdata & ~BIT5;//0x00;
    WriteData(2, 4, 1, &data);
}
void PLC_S7::Z_ABSRight_1(){    
    qDebug()<<"PLC_S7::Z_ABSRight_1";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata | BIT7;//0x81;
    WriteData(2, 0, 1, &data);
}
void PLC_S7::Z_ABSRight_2(){
    qDebug()<<"PLC_S7::Z_ABSRight_2";
    byte rdata = 0;
    ReadData(2, 0, 1, &rdata);
    byte data = rdata & ~BIT7;//0x01;
    WriteData(2, 0, 1, &data);
}

//void PLC_S7::setABSLeft_clicked(){
//    byte data_array[4];
//    ReadData(10, 0, 4, data_array);
//    float data = qFromBigEndian<float>(data_array);
//    //WriteData(15, 90, 4, data_array);
//}
//void PLC_S7::setABSRight_clicked(){
//    byte data_array[4];
//    ReadData(10, 0, 4, data_array);
//    // float data = qFromBigEndian<float>(data_array);
//    WriteData(15, 94, 4, data_array);
//}
void PLC_S7::X_SetCurPosLeft(){
    qDebug()<<"PLC_S7::X_SetCurPosLeft";
    byte data_array[4];
    ReadData(10, 4, 4, data_array);
    //X_CurPosLeft = qFromBigEndian<float>(data_array);
    WriteData(18, 0, 4, data_array);
}
void PLC_S7::X_SetCurPosRight(){
    qDebug()<<"PLC_S7::X_SetCurPosRight";
    byte data_array[4];
    ReadData(10, 4, 4, data_array);
    //X_CurPosRight = qFromBigEndian<float>(data_array);
    WriteData(18, 4, 4, data_array);
}
void PLC_S7::Y_SetCurPosLeft(){
    qDebug()<<"PLC_S7::Y_SetCurPosLeft";
    byte data_array[4];
    ReadData(10, 8, 4, data_array);
    //Y_CurPosLeft = qFromBigEndian<float>(data_array);
    WriteData(17, 0, 4, data_array);
}
void PLC_S7::Y_SetCurPosRight(){
    qDebug()<<"PLC_S7::Y_SetCurPosRight";
    byte data_array[4];
    ReadData(10, 8, 4, data_array);
    //Y_CurPosRight = qFromBigEndian<float>(data_array);
    WriteData(17, 4, 4, data_array);
}
void PLC_S7::Z_SetCurPosLeft(){
    qDebug()<<"PLC_S7::Z_SetCurPosLeft";
    byte data_array[4];
    ReadData(10, 0, 4, data_array);
    //Z_CurPosLeft = qFromBigEndian<float>(data_array);
    WriteData(15, 90, 4, data_array);
}
void PLC_S7::Z_SetCurPosRight(){
    qDebug()<<"PLC_S7::Z_SetCurPosRight";
    byte data_array[4];
    ReadData(10, 0, 4, data_array);
    //Z_CurPosRight = qFromBigEndian<float>(data_array);
    WriteData(15, 94, 4, data_array);
}
//void PLC_S7::setABS(float data){
//    byte data_array[4];
//    qToBigEndian<float>(data, data_array);
//    WriteData(3, 0, 4, data_array);
//}
void PLC_S7::X_ABS_Speed(float data){
    qDebug()<<"PLC_S7::X_ABS_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 8, 4, data_array);
}
void PLC_S7::Y_ABS_Speed(float data){
    qDebug()<<"PLC_S7::Y_ABS_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 16, 4, data_array);
}
void PLC_S7::Z_ABS_Speed(float data){
    qDebug()<<"PLC_S7::Z_ABS_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 0, 4, data_array);
}

//void PLC_S7::setJOG(float data){
//    byte data_array[4];
//    qToBigEndian<float>(data, data_array);
//    WriteData(3, 4, 4, data_array);
//}
void PLC_S7::X_JOG_Speed(float data){
    qDebug()<<"PLC_S7::X_JOG_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 12, 4, data_array);
}
void PLC_S7::Y_JOG_Speed(float data){
    qDebug()<<"PLC_S7::Y_JOG_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 20, 4, data_array);
}
void PLC_S7::Z_JOG_Speed(float data){
    qDebug()<<"PLC_S7::Z_JOG_Speed";
    byte data_array[4];
    qToBigEndian<float>(data, data_array);
    WriteData(3, 4, 4, data_array);
}

void PLC_S7::Sys_Initial_1(){
    qDebug()<<"PLC_S7::Sys_Initial_1";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata | BIT5;//0x20;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Initial_2(){
    qDebug()<<"PLC_S7::Sys_Initial_2";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata & ~BIT5;//0x00;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Start_1(){
    qDebug()<<"PLC_S7::Sys_Start_1";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata | BIT6;//0x40;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Start_2(){
    qDebug()<<"PLC_S7::Sys_Start_2";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata & ~BIT6;//0x00;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Pause_1(){
    qDebug()<<"PLC_S7::Sys_Pause_1";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata | BIT7;//0x80;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Pause_2(){
    qDebug()<<"PLC_S7::Sys_Pause_2";
    byte rdata = 0;
    ReadData(2, 5, 1, &rdata);
    byte data = rdata & ~BIT7;//0x00;
    WriteData(2, 5, 1, &data);
}
void PLC_S7::Sys_Stop_1(){
    qDebug()<<"PLC_S7::Sys_Stop_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT0;//0x01;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_Stop_2(){
    qDebug()<<"PLC_S7::Sys_Stop_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata & ~BIT0;//0x00;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_AlmReset_1(){
    qDebug()<<"PLC_S7::Sys_AlmReset_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT1;//0x02;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_AlmReset_2(){
    qDebug()<<"PLC_S7::Sys_AlmReset_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata & ~BIT1;//0x00;
    WriteData(2, 6, 1, &data);
}

void PLC_S7::Sys_Spare1_1(){
    qDebug()<<"PLC_S7::Sys_Spare1_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT2;//0x02;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_Spare1_2(){
    qDebug()<<"PLC_S7::Sys_Spare1_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT2;//0x00;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_Spare2_1(){
    qDebug()<<"PLC_S7::Sys_Spare2_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT3;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Sys_Spare2_2(){
    qDebug()<<"PLC_S7::Sys_Spare2_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT3;//0x00;
    WriteData(2, 6, 1, &data);
}
//左激光
void PLC_S7::RightLaser_1(){
    qDebug()<<"PLC_S7::RightLaser_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT4;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::RightLaser_2(){
    qDebug()<<"PLC_S7::RightLaser_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT4;
    WriteData(2, 6, 1, &data);
}
//右激光
void PLC_S7::LeftLaser_1(){
    qDebug()<<"PLC_S7::LeftLaser_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT5;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::LeftLaser_2(){
    qDebug()<<"PLC_S7::LeftLaser_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT5;
    WriteData(2, 6, 1, &data);
}
//初始化流程复位
void PLC_S7::Initial_Sequence_1(){
    qDebug()<<"PLC_S7::Initial_Sequence_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT6;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Initial_Sequence_2(){
    qDebug()<<"PLC_S7::Initial_Sequence_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT6;
    WriteData(2, 6, 1, &data);
}
//自动流程复位
void PLC_S7::Auto_Sequence_1(){
    qDebug()<<"PLC_S7::Auto_Sequence_1";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata | BIT7;
    WriteData(2, 6, 1, &data);
}
void PLC_S7::Auto_Sequence_2(){
    qDebug()<<"PLC_S7::Auto_Sequence_2";
    byte rdata = 0;
    ReadData(2, 6, 1, &rdata);
    byte data = rdata ^ BIT7;
    WriteData(2, 6, 1, &data);
}
//X轴运动次数复位
void PLC_S7::X_Counter_Rst_1(){
    qDebug()<<"PLC_S7::X_Counter_Rst_1";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata | BIT0;
    WriteData(2, 7, 1, &data);
}
void PLC_S7::X_Counter_Rst_2(){
    qDebug()<<"PLC_S7::X_Counter_Rst_2";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata ^ BIT0;
    WriteData(2, 7, 1, &data);
}
//Y轴运动次数复位
void PLC_S7::Y_Counter_Rst_1(){
    qDebug()<<"PLC_S7::Y_Counter_Rst_1";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata | BIT1;
    WriteData(2, 7, 1, &data);
}
void PLC_S7::Y_Counter_Rst_2(){
    qDebug()<<"PLC_S7::Y_Counter_Rst_2";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata ^ BIT1;
    WriteData(2, 7, 1, &data);
}
//Z轴运动次数复位
void PLC_S7::Z_Counter_Rst_1(){
    qDebug()<<"PLC_S7::Z_Counter_Rst_1";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata | BIT2;
    WriteData(2, 7, 1, &data);
}
void PLC_S7::Z_Counter_Rst_2(){
    qDebug()<<"PLC_S7::Z_Counter_Rst_2";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata ^ BIT2;
    WriteData(2, 7, 1, &data);
}
//已检测产品数量复位
void PLC_S7::Total_Rst_1(){
    qDebug()<<"PLC_S7::Total_Rst_1";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata | BIT3;
    WriteData(2, 7, 1, &data);
}
void PLC_S7::Total_Rst_2(){
    qDebug()<<"PLC_S7::Total_Rst_2";
    byte rdata = 0;
    ReadData(2, 7, 1, &rdata);
    byte data = rdata ^ BIT3;
    WriteData(2, 7, 1, &data);
}


void PLC_S7::setArray(QVector<float> vec){
    int size = vec.size();
    int len = size*sizeof(float);
    byte* data_array = new byte[len];
    for(int i= 0;i<size;++i){
        qToBigEndian<float>(vec[i], &(data_array[i * sizeof(float)]));
    }
    WriteData(15, 0, len, data_array);
    delete[] data_array;
}
//void PLC_S7::setArrayByte(byte* data,int size){
////    float value = 0.123f;
//    WriteData(15, 0, size, data);
//}
//void PLC_S7::ABSRight_clicked(){
//    byte data = 0x41;
//    //WriteData(2, 0, 1, &data);
//}
/////////////////////////////////////////////////////////////////////////////
//void PLC_S7::setZPowerOnStatus(byte data){
//    bool flag = ((0x01 & data) != 0);
//    if(Z_PowerOn_Status != flag){
//        Z_PowerOn_Status = flag;
//    }
//}
//void PLC_S7::setZPowerOnError(byte data){
//    bool flag = ((0x02 & data) != 0);
//    if(Z_PowerOn_Error != flag){
//        Z_PowerOn_Error = flag;
//    }
//}
//void PLC_S7::setZResetDone(byte data){
//    bool flag = ((0x04 & data) != 0);
//    if(Z_Reset_Done != flag){
//        Z_Reset_Done = flag;
//    }
//}
//void PLC_S7::setZResetError(byte data){
//    bool flag = ((0x08 & data) != 0);
//    if(Z_Reset_Error != flag){
//        Z_Reset_Error = flag;
//    }
//}
//void PLC_S7::setZHomeDone(byte data){
//    bool flag = ((0x10 & data) != 0);
//    if(Z_Home_Done != flag){
//        Z_Home_Done = flag;
//    }
//}
//void PLC_S7::setZHomeError(byte data){
//    bool flag = ((0x20 & data) != 0);
//    if(Z_Home_Error != flag){
//        Z_Home_Error = flag;
//    }
//}
//void PLC_S7::setZABSDone(byte data){
//    bool flag = ((0x40 & data) != 0);
//    if(Z_ABS_Done != flag){
//        Z_ABS_Done = flag;
//    }
//}
//void PLC_S7::setZABSError(byte data){
//    bool flag = ((0x80 & data) != 0);
//    if(Z_ABS_Error != flag){
//        Z_ABS_Error = flag;
//    }
//}

//void PLC_S7::setDB16_1(byte data){
//    setZJOGinVelocity(data);
//    setZJOGError(data);
//    setZHaltDone(data);
//    setZHaltErr(data);
//    setZReadparamVaild(data);
//    setZReadparamErr(data);
//    setZResetBusy(data);
//    setZHomeBusy(data);
//}
//void PLC_S7::setZJOGinVelocity(byte data){
//    bool flag = ((0x01 & data) != 0);
//    if(Z_JOG_inVelocity != flag){
//        Z_JOG_inVelocity = flag;
//    }
//}
//void PLC_S7::setZJOGError(byte data){
//    bool flag = ((0x02 & data) != 0);
//    if(Z_JOG_Error != flag){
//        Z_JOG_Error = flag;
//    }
//}
//void PLC_S7::setZHaltDone(byte data){
//    bool flag = ((0x04 & data) != 0);
//    if(Z_Halt_Done != flag){
//        Z_Halt_Done = flag;
//    }
//}
//void PLC_S7::setZHaltErr(byte data){
//    bool flag = ((0x08 & data) != 0);
//    if(Z_Halt_Err != flag){
//        Z_Halt_Err = flag;
//    }
//}
//void PLC_S7::setZReadparamVaild(byte data){
//    bool flag = ((0x10 & data) != 0);
//    if(Z_Readparam_Vaild != flag){
//        Z_Readparam_Vaild = flag;
//    }
//}
//void PLC_S7::setZReadparamErr(byte data){
//    bool flag = ((0x20 & data) != 0);
//    if(Z_Readparam_Err != flag){
//        Z_Readparam_Err = flag;
//    }
//}
//void PLC_S7::setZResetBusy(byte data){
//    bool flag = ((0x40 & data) != 0);
//    if(Z_Reset_Busy != flag){
//        Z_Reset_Busy = flag;
//    }
//}
//void PLC_S7::setZHomeBusy(byte data){
//    bool flag = ((0x80 & data) != 0);
//    if(Z_Home_Busy != flag){
//        Z_Home_Busy = flag;
//    }
//}
