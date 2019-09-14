#ifndef __VLDFIX_H__
#define __VLDFIX_H__
/***********************************************************************************************************************
* Description         : vld is perfect memory leak checker, but before VS2012, it has one bug.
*                       it will mis-report memory leak when typeinfo::name() is used.
*                       here is fix. include this header is enough
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/productSpecialDef.h>

#if Enable_VLD_FIX==1
    #include <vld.h>
#endif

namespace MiniMPL
{
#if Enable_VLD_FIX==1
    #pragma comment(linker, "/include:?exitCall@MiniMPL@@3UFixTypeInfoBlockUse@1@A")
#endif // _DEBUG    
}

#endif // __VLDFIX_H__
