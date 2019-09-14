#ifndef TC_PATH_H__
#define TC_PATH_H__
/************************************************************************************
author  :	Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose :	get current lib source path : .\sources\
*************************************************************************************/
#include <MiniMPL\productSpecialDef.h>

namespace UnitTest
{
    stlStringA getOutputPathA();
    stlStringW getOutputPathW();
#ifdef USE_UNICODE_STRING
    #define getOutputPath   getOutputPathW;
#else
    #define getOutputPath   getOutputPathA;
#endif // _DEBUG
}

#endif // TC_PATH_H__
