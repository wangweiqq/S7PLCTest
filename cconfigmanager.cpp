#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QSettings>
#include "cconfigmanager.h"
CConfigManager* CConfigManager::Instance = NULL;
CConfigManager::CConfigManager()
{
    QSettings setting("./config.ini",QSettings::IniFormat);
    mPLCIp = setting.value("PLC/plc_ip").toString();
    qDebug()<<mPLCIp;
    qDebug()<<setting.fileName();
//	qDebug() << "mDbIp : " << mDbIp.toStdString().c_str() << "mDbPort : " << mDbPort<<"mDbUser : "<< mDbUser.toStdString().c_str()<<" mDbPwd : "<< mDbPwd.toStdString().c_str()<<" mDbName : "<< mDbName.toStdString().c_str();
}
CConfigManager::~CConfigManager(){

}
CConfigManager* CConfigManager::getInstance(){
    if(Instance){
        return Instance;
    }
    Instance = new CConfigManager();
    return Instance;
}

