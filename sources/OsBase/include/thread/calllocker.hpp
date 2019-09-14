#ifndef __CALLLOCKER_HPP__
#define __CALLLOCKER_HPP__
/***********************************************************************************************************************
* Description         : simple mutual exclusion in different thread.
*                       e.g. operate device, add/delete container element
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/productSpecialDef.h>
#include <thread/sync.h>
#include <MiniMPL/macro_makeVar.h>
#include <MiniMPL/isXXXEx.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>  
struct TCallLocker : public CSyncLocker<CSyncThread>
{
    TCallLocker(T& robj,CSyncThread& lock)
        : CSyncLocker(lock),m_obj(robj)
    {}

    T* operator->()
    {
        TRACE_INFO(("ready implement(operator->):\n"));
        return &m_obj;
    }

protected:
    T&               m_obj;
};

template<typename T>
inline TCallLocker<T> makeCallLocker(T& rObj,CSyncThread& lock)
{
    TRACE_INFO(("make exclusion:\n"));
    return TCallLocker<T>(rObj,lock); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//T MUST be derived from TExclusiveCallBase<T>, else compile fail when calling exclusion()
template<typename T> 
struct TLockCallBase
{
#define innerLock()     LockHere(m_lock)

    TCallLocker<T> useLocker()
    {
        Static_Assert((MiniMPL::IsBaseDerive<TLockCallBase,T>::value));  //assert Base-derive relation
        return makeCallLocker(*(T*)(this),m_lock);
    }

    CSyncThread             m_lock;   

protected:
    TLockCallBase(){};                          //disable construct base class object directly
    TLockCallBase(TLockCallBase const&){};      //disable copy base class object directly
};

#endif // __CALLLOCKER_HPP__
