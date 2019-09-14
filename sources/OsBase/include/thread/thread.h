#ifndef __THREAD_H__
#define __THREAD_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <thread/threadBase.h>
#include <MiniMPL/macro_class.h>
#include <MiniMPL/callbacker.hpp>

class CThread : public CThreadBase
{
public:
    CThread();
    virtual ~CThread();
    
    bool setCallback(MiniMPL::TpCallbacker const& pCallee);    
    template<typename F>    bool setCallback(F f)
    {
        using namespace MiniMPL;
        return setCallback(TpCallbacker(makeCallbacker(f)));
    }
    template<typename F>    bool setCallback(F f,FO(F)& rObj)
    {
        using namespace MiniMPL;
        return setCallback(TpCallbacker(makeCallbacker(f,rObj)));
    }

protected:
    virtual void run();    //derived or setCallback
    Disable_Class_Assign(CThread);

protected:
    MiniMPL::TpCallbacker    m_callee;
};

typedef stlSmartptr<CThread>    TpThread;

#endif // __THREAD_H__
