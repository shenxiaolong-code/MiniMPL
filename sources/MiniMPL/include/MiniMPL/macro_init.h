#ifndef __MACRO_INIT_H__
#define __MACRO_INIT_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/macro_makeVar.h>

//////////////////////////////global Init helper macro begin ////////////////////////////////////////////////////////////
template<typename F>  inline bool globalInit(F& pFunc)
{
    pFunc();
    return true;
}

template<typename F,typename P1>  inline bool globalInit1(F& pFunc,P1& p1)
{
    pFunc(p1);
    return true;
}

#define GLOBALVAR(N)            static bool N 
#define GLOBALFUNC(X)           globalInit(X)
#define GLOBALFUNC1(X,p1)       globalInit1(X,p1)

#define InitRunFunc(X)          GLOBALVAR(MAKEVAR3(MAKEVAR2(GlobalInit_,X),_,UNIQUEID))	= GLOBALFUNC(X)
#define InitRunFunc1(X,p1)      GLOBALVAR(MAKEVAR3(MAKEVAR2(GlobalInit_,X),_,UNIQUEID)) = GLOBALFUNC1(X,p1)
//////////////////////////////global Init helper macro end ////////////////////////////////////////////////////////////


#endif // __MACRO_INIT_H__
