#ifndef THREADMANAGER_H__
#define THREADMANAGER_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	thread manager 
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>
#include <thread\thread.h>
#include <utility\singleton.hpp>

class CThreadMananger : public stlVector<CThreadBase*> 
                      , public SingletonMultiInstance<CThreadMananger,false>
{
public:
	virtual ~CThreadMananger();
    CThreadBase* getThread(ThreadID id) const;

    bool registerThread(CThreadBase& newThrd);
    bool unregisterThread(CThreadBase& existThrd);
};

#endif // THREADMANAGER_H__