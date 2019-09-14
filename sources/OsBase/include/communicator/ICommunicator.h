#ifndef __ICOMMUNICATOR_H__
#define __ICOMMUNICATOR_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <communicator/IReceiver.h>

struct ICommunicator : public stlVector<TpReceiver>
{
    virtual ~ICommunicator();;
    
    //control interface
    virtual bool start()=0;
    virtual bool stop()=0;
    
    //r/w interface
    virtual int  send(void* pBuf,unsigned iLen)=0;
    virtual int  recv(CCommBuffer& rBuf)=0;

    virtual bool registerReceiver(TpReceiver pReceiver);
    virtual bool unregisterReceiver(IReceiver* pReceiver);

    //notification/callback interface
    virtual void  onDataReceivced(CCommBuffer const& rBuf);
    virtual void  onConnected();
    virtual void  onDisconnected();
};

#endif // __ICOMMUNICATOR_H__
