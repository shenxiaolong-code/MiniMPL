#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__
/***********************************************************************************************************************
* Description         : Singleton general implement
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/kitType.hpp>
#include <thread/sync.h>
#include <MiniMPL/macro_assert.h>

/*
SingletonDestroyable<T,1>;
T::getInstance();
T ok;           // it is OK

SingletonDestroyable<T,0>;
T::getInstance();
T fail;         // it will trigger assert.
*/

//don't move SingletonMultiInstance from OsBase to MiniMPL because it needs one thread lock which is based on OS feature.
//std::mutex is one process lock with worse performance,  here one thread lock is best.
//if we want OS decouple, so we have to compromise to use std:: mutex process lock with worse performance.

template<typename T,bool bAllownMultiInstance=false>    struct SingletonMultiInstance;

template<typename TImpl>
class SingletonDestroyable
{
    template<typename T>        struct GetInstanceType;
    template<typename T,bool b> struct GetInstanceType<SingletonMultiInstance<T,b> > : public MiniMPL::Type2Type<T>{};

    typedef typename GetInstanceType<TImpl>::type  InstanceType;

public:
    static InstanceType& getInstance()
    {
        if (!gs_pInstance)
        {
            LockHere(getGlobalThreadLock());
            if (!gs_pInstance)
            {
                TImpl::createInstance();
                atexit(destroyInstance);
            }
        }
        ASSERT_AND_LOG(NULL !=gs_pInstance);
        return *gs_pInstance;
    }

    static void destroyInstance()
    {
        LockHere(getGlobalThreadLock());
        if (gs_pInstance)
        {
            TImpl::deleteInstance();
            ASSERT_AND_LOG(NULL==gs_pInstance);
        }
    }

private:
    SingletonDestroyable(SingletonDestroyable const&){};
    SingletonDestroyable& operator=(SingletonDestroyable const&){};

protected:            
    SingletonDestroyable() {};
    ~SingletonDestroyable() {};

protected:
    static InstanceType* volatile gs_pInstance;
};
template<typename TImpl>
typename SingletonDestroyable<TImpl>::InstanceType* volatile SingletonDestroyable<TImpl>::gs_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct SingletonMultiInstance<T,false> : public SingletonDestroyable<SingletonMultiInstance<T,false> >
{
    friend class SingletonDestroyable<SingletonMultiInstance<T,false> >;

protected:            
    static void createInstance()
    {
        new T();
    }
    static void deleteInstance()
    {
        delete gs_pInstance;
        ASSERT_AND_LOG(NULL ==gs_pInstance);
    }

    SingletonMultiInstance()
    { 
        LockHere(getGlobalThreadLock()); //thread reentry
        ASSERT_AND_LOG_INFO(NULL==gs_pInstance,(L"Not Allow Multiple Instance!")); 
        gs_pInstance = static_cast<T*>(this);
    };

    ~SingletonMultiInstance()
    {
        LockHere(getGlobalThreadLock());  //thread reentry
        ASSERT_AND_LOG(this==gs_pInstance);
        gs_pInstance = NULL;
    }
};

template<typename T>
struct SingletonMultiInstance<T,true> : public SingletonDestroyable<SingletonMultiInstance<T,true> >
{
    friend class SingletonDestroyable<SingletonMultiInstance<T,true> >;

protected:
    static void createInstance()
    {
        ASSERT_AND_LOG(NULL==gs_pInstance);
        gs_pInstance = new T();
    }
    static void deleteInstance()
    {
        delete gs_pInstance;
        gs_pInstance = NULL;
    }
};
#endif // __SINGLETON_HPP__
