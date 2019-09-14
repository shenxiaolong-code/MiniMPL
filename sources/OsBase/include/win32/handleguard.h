#ifndef __HANDLEGUARD_H__
#define __HANDLEGUARD_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <windows.h>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/callbacker.hpp>

namespace OS_Win32
{
    struct OnReturn
    {
        OnReturn(MiniMPL::TpCallbacker   pcall);
        virtual ~OnReturn();

        MiniMPL::TpCallbacker   m_pcall;
    };
    typedef stlSmartptr<OnReturn>   TpOnReturn;
#define DoOnReturn(X)  OnReturn MAKEVAR2(OnReturn_,UNIQUEID)(X)

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CHandle
    {
    public:
        CHandle();
        explicit CHandle(HANDLE handle);  //avoid CHandle -> HANDLE -> CHandle
        explicit CHandle(CHandle const& rOther);
        virtual ~CHandle();

        CHandle& operator=(CHandle const& rOther);
        bool operator==(HANDLE handle) const;
        bool operator!=(HANDLE handle) const;

        HANDLE&         rawHandle();
        HANDLE const&   rawHandle() const;

        operator HANDLE&();
        operator HANDLE const&()    const;

        bool     close();
        bool     isValid() const;

    protected:
        stlSmartptr<HANDLE>     m_pHandle;  //use smart pointer to keep copyable and assignable  
    };
}


#endif // __HANDLEGUARD_H__
