#ifndef __WINAPIPACK_H__
#define __WINAPIPACK_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/productSpecialDef.h>

namespace OS_Win32
{
    stlString GetErrorText( unsigned eCode );

#define GetLastErrorText  GetErrorText  

}






#endif // __WINAPIPACK_H__
