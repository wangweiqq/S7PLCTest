#include "LPCContrlDialog.h"
#include <QApplication>
#include "plc_s7.h"
#include "cplcstate.h"
#include "cconfigmanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<PLCState>("PLCState");
    CConfigManager* config = CConfigManager::getInstance();
    qDebug()<<config->mPLCIp;
    PLC_S7 *plcS7 = NULL;
    plcS7 = new PLC_S7(config->mPLCIp);

    LPCContrlDialog w;
    w.show();
    //QObject::connect(plcS7,SIGNAL(plcState(PLCState)),&w,SIGNAL(plcState(PLCState)));
    //QObject::connect(plcS7,SIGNAL(plcState(PLCState)),&w,SIGNAL(onPLCState(PLCState)));
    QObject::connect(plcS7,SIGNAL(plcState(PLCState)),&w,SLOT(onPLCState(PLCState)));
    QObject::connect(plcS7,SIGNAL(plcLinkChanged(bool)),&w,SLOT(onPlcLinkChanged(bool)));

    QObject::connect(&w,SIGNAL(SetJOG1(float)),plcS7,SLOT(onSetJOG1(float)));
    QObject::connect(&w,SIGNAL(PowerOn1()),plcS7,SLOT(onPowerOn1()));
    QObject::connect(&w,SIGNAL(PowerOff1()),plcS7,SLOT(onPowerOff1()));
    QObject::connect(&w,SIGNAL(Reset1()),plcS7,SLOT(onReset1()));
    QObject::connect(&w,SIGNAL(Pause1()),plcS7,SLOT(onPause1()));
    QObject::connect(&w,SIGNAL(Pause1_2()),plcS7,SLOT(onPause1_2()));
    QObject::connect(&w,SIGNAL(Home1()),plcS7,SLOT(onHome1()));
    QObject::connect(&w,SIGNAL(SetABS1(float)),plcS7,SLOT(onSetABS1(float)));
    QObject::connect(&w,SIGNAL(JOGMinus1_1()),plcS7,SLOT(onJOGMinus1_1()));
    QObject::connect(&w,SIGNAL(JOGMinus1_2()),plcS7,SLOT(onJOGMinus1_2()));
    QObject::connect(&w,SIGNAL(JOGPlus1_1()),plcS7,SLOT(onJOGPlus1_1()));
    QObject::connect(&w,SIGNAL(JOGPlus1_2()),plcS7,SLOT(onJOGPlus1_2()));
    QObject::connect(&w,SIGNAL(SetArray1(QVector<float>)),plcS7,SLOT(onSetArray1(QVector<float>)));
    QObject::connect(&w,SIGNAL(ABSLeft1()),plcS7,SLOT(onABSLeft1()));
    QObject::connect(&w,SIGNAL(ABSRight1()),plcS7,SLOT(onABSRight1()));
    QObject::connect(&w,SIGNAL(SetABSLeft1()),plcS7,SLOT(onSetABSLeft1()));
    QObject::connect(&w,SIGNAL(SetABSRight1()),plcS7,SLOT(onSetABSRight1()));

    QObject::connect(&w,SIGNAL(SetJOG2(float)),plcS7,SLOT(onSetJOG2(float)));
    QObject::connect(&w,SIGNAL(PowerOn2()),plcS7,SLOT(onPowerOn2()));
    QObject::connect(&w,SIGNAL(PowerOff2()),plcS7,SLOT(onPowerOff2()));
    QObject::connect(&w,SIGNAL(Reset2()),plcS7,SLOT(onReset2()));
    QObject::connect(&w,SIGNAL(Pause2()),plcS7,SLOT(onPause2()));
    QObject::connect(&w,SIGNAL(Pause2_2()),plcS7,SLOT(onPause2_2()));
    QObject::connect(&w,SIGNAL(Home2()),plcS7,SLOT(onHome2()));
    QObject::connect(&w,SIGNAL(SetABS2(float)),plcS7,SLOT(onSetABS2(float)));
    QObject::connect(&w,SIGNAL(JOGMinus2_1()),plcS7,SLOT(onJOGMinus2_1()));
    QObject::connect(&w,SIGNAL(JOGMinus2_2()),plcS7,SLOT(onJOGMinus2_2()));
    QObject::connect(&w,SIGNAL(JOGPlus2_1()),plcS7,SLOT(onJOGPlus2_1()));
    QObject::connect(&w,SIGNAL(JOGPlus2_2()),plcS7,SLOT(onJOGPlus2_2()));
    QObject::connect(&w,SIGNAL(SetArray2(QVector<float>)),plcS7,SLOT(onSetArray2(QVector<float>)));
    QObject::connect(&w,SIGNAL(ABSLeft2()),plcS7,SLOT(onABSLeft2()));
    QObject::connect(&w,SIGNAL(ABSRight2()),plcS7,SLOT(onABSRight2()));
    QObject::connect(&w,SIGNAL(SetABSLeft2()),plcS7,SLOT(onSetABSLeft2()));
    QObject::connect(&w,SIGNAL(SetABSRight2()),plcS7,SLOT(onSetABSRight2()));

    QObject::connect(&w,SIGNAL(SetJOG3(float)),plcS7,SLOT(onSetJOG3(float)));
    QObject::connect(&w,SIGNAL(PowerOn3()),plcS7,SLOT(onPowerOn3()));
    QObject::connect(&w,SIGNAL(PowerOff3()),plcS7,SLOT(onPowerOff3()));
    QObject::connect(&w,SIGNAL(Reset3()),plcS7,SLOT(onReset3()));
    QObject::connect(&w,SIGNAL(Pause3()),plcS7,SLOT(onPause3()));
    QObject::connect(&w,SIGNAL(Pause3_2()),plcS7,SLOT(onPause3_2()));
    QObject::connect(&w,SIGNAL(Home3()),plcS7,SLOT(onHome3()));
    QObject::connect(&w,SIGNAL(SetABS3(float)),plcS7,SLOT(onSetABS3(float)));
    QObject::connect(&w,SIGNAL(JOGMinus3_1()),plcS7,SLOT(onJOGMinus3_1()));
    QObject::connect(&w,SIGNAL(JOGMinus3_2()),plcS7,SLOT(onJOGMinus3_2()));
    QObject::connect(&w,SIGNAL(JOGPlus3_1()),plcS7,SLOT(onJOGPlus3_1()));
    QObject::connect(&w,SIGNAL(JOGPlus3_2()),plcS7,SLOT(onJOGPlus3_2()));
    QObject::connect(&w,SIGNAL(SetArray3(QVector<float>)),plcS7,SLOT(onSetArray3(QVector<float>)));
    QObject::connect(&w,SIGNAL(ABSLeft3()),plcS7,SLOT(onABSLeft3()));
    QObject::connect(&w,SIGNAL(ABSRight3()),plcS7,SLOT(onABSRight3()));
    QObject::connect(&w,SIGNAL(SetABSLeft3()),plcS7,SLOT(onSetABSLeft3()));
    QObject::connect(&w,SIGNAL(SetABSRight3()),plcS7,SLOT(onSetABSRight3()));

    QObject::connect(&w,SIGNAL(SysInitial1()),plcS7,SLOT(onSysInitial1()));
    QObject::connect(&w,SIGNAL(SysInitial2()),plcS7,SLOT(onSysInitial2()));
    QObject::connect(&w,SIGNAL(SysStart1()),plcS7,SLOT(onSysStart1()));
    QObject::connect(&w,SIGNAL(SysStart2()),plcS7,SLOT(onSysStart2()));
    QObject::connect(&w,SIGNAL(SysPause()),plcS7,SLOT(onSysPause()));
    QObject::connect(&w,SIGNAL(SysStop1()),plcS7,SLOT(onSysStop1()));
    QObject::connect(&w,SIGNAL(SysStop2()),plcS7,SLOT(onSysStop2()));
    QObject::connect(&w,SIGNAL(SysAlmReset1()),plcS7,SLOT(onSysAlmReset1()));
    QObject::connect(&w,SIGNAL(SysAlmReset2()),plcS7,SLOT(onSysAlmReset2()));

    QObject::connect(&w,SIGNAL(SysSpare1()),plcS7,SLOT(onSysSpare1()));
    QObject::connect(&w,SIGNAL(SysSpare2()),plcS7,SLOT(onSysSpare2()));
    QObject::connect(&w,SIGNAL(RightLaser()),plcS7,SLOT(onRightLaser()));
    QObject::connect(&w,SIGNAL(LeftLaser()),plcS7,SLOT(onLeftLaser()));
    QObject::connect(&w,SIGNAL(InitialSequenceReset()),plcS7,SLOT(onInitialSequenceReset()));
    QObject::connect(&w,SIGNAL(AutoSequenceReset()),plcS7,SLOT(onAutoSequenceReset()));
    QObject::connect(&w,SIGNAL(X_Counter_Rst()),plcS7,SLOT(onX_Counter_Rst()));
    QObject::connect(&w,SIGNAL(Y_Counter_Rst()),plcS7,SLOT(onY_Counter_Rst()));
    QObject::connect(&w,SIGNAL(Z_Counter_Rst()),plcS7,SLOT(onZ_Counter_Rst()));
    QObject::connect(&w,SIGNAL(Total_Rst()),plcS7,SLOT(onTotal_Rst()));

    QObject::connect(&w,SIGNAL(ReadRecipe(QString)),plcS7,SLOT(onReadRecipe(QString)));
	QObject::connect(&w,SIGNAL(WriteRecipe(int , QVector<float> , QVector<float> , QVector<float> )),plcS7,SLOT(onWriteRecope(int , QVector<float> , QVector<float> , QVector<float> )));
    
    QObject::connect(&w, SIGNAL(Type_1_Select()), plcS7, SLOT(onType_1_Select()));
    QObject::connect(&w, SIGNAL(Type_2_Select()), plcS7, SLOT(onType_2_Select()));
    QObject::connect(&w, SIGNAL(Manul_X_Y_Z(uint16_t)), plcS7, SLOT(onManul_X_Y_Z(uint16_t)));
	QObject::connect(&w, SIGNAL(LocalOnLine()), plcS7, SLOT(onLocalOnLine()));
    plcS7->start();
    return a.exec();
}
