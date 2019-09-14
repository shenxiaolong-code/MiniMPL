#ifndef __IRECEIVER_H__
#define __IRECEIVER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <MiniMPL\functionParams.hpp>
#include <communicator\CommuDef.h>

struct IReceiver 
{    
    virtual void onReceive(CCommBuffer const& rBuf)=0;
    virtual ~IReceiver(){};
};
typedef stlSmartptr<IReceiver>        TpReceiver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TBinF>
struct IReceiverImpl : public IReceiver
{
    IReceiverImpl(TBinF f):m_f(f){};

    virtual void onReceive(void* pBuf,unsigned iLen)
    {
        return m_f(pBuf,iLen);
    }

    virtual ~IReceiverImpl(){};

    TBinF  m_f;
};

template<typename TBinF>
TpReceiver makeReceiver(TBinF f)
{
    return TpReceiver(new IReceiverImpl<TBinF>(f));
}

template<typename TBinF>
struct IReceiverImpl_Obj : public IReceiver
{
    typedef FO(TBinF)       TObj;
    IReceiverImpl_Obj(TObj& obj,TBinF f) 
        : m_f(f)
        , m_pObj(&obj){};

    virtual void onReceive(void* pBuf,unsigned iLen)
    {
        return (m_pObj->*m_f)(pBuf,iLen);
    }

    virtual ~IReceiverImpl_Obj(){};

    TBinF   m_f;
    TObj*   m_pObj;
};

template<typename TBinF>
TpReceiver makeReceiver(FO(TBinF)& obj,TBinF f)
{
    return TpReceiver(new IReceiverImpl_Obj<TBinF>(obj,f));
}



#endif // __IRECEIVER_H__
