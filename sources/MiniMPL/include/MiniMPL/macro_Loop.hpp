#ifndef __MACRO_LOOP_HPP__
#define __MACRO_LOOP_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/macro_loop_detail.hpp>
/* example.
#define loopfun(i)  {key##i,val##i,name##i}
old way:
StrcutType rArr[] = 
{
    {key1,val1,name1},
    {key2,val2,name2},
    {key3,val3,name3},
    {key4,val4,name4}
};
new way:
StrcutType rArr[]={LOOP_1ToN(4,loopfun)};
*/

#define  LOOP_1ToN(n,loopFunc)          LOOP_1ToN_SEP(n,loopFunc,SEP_COMMA)
#define  LOOP_0ToN(n,loopFunc)          LOOP_0ToN_SEP(n,loopFunc,SEP_COMMA)
#define  LOOP_1ToN_CLS(n,loopFunc)      LOOP_1ToN_SEP(n,loopFunc,SEP_SEMICOLON)
#define  LOOP_0ToN_CLS(n,loopFunc)      LOOP_0ToN_SEP(n,loopFunc,SEP_SEMICOLON)

#define  LOOP_NTo1(n,loopFunc)          LOOP_NTo1_SEP(n,loopFunc,SEP_COMMA)
#define  LOOP_NTo0(n,loopFunc)          LOOP_NTo0_SEP(n,loopFunc,SEP_COMMA)
#define  LOOP_NTo1_CLS(n,loopFunc)      LOOP_NTo1_SEP(n,loopFunc,SEP_SEMICOLON)
#define  LOOP_NTo0_CLS(n,loopFunc)      LOOP_NTo0_SEP(n,loopFunc,SEP_SEMICOLON)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//loop func with extend parameter
#define  LOOP_1ToNP(n,loopFunc2,p)      LOOP_1ToNP_SEP(n,loopFunc2,p,SEP_COMMA)
#define  LOOP_0ToNP(n,loopFunc2,p)      LOOP_0ToNP_SEP(n,loopFunc2,p,SEP_COMMA)
#define  LOOP_1ToNP_CLS(n,loopFunc2,p)  LOOP_1ToNP_SEP(n,loopFunc2,p,SEP_SEMICOLON)
#define  LOOP_0ToNP_CLS(n,loopFunc2,p)  LOOP_0ToNP_SEP(n,loopFunc2,p,SEP_SEMICOLON)

#define  LOOP_NTo1P(n,loopFunc2,p)      LOOP_NTo1P_SEP(n,loopFunc2,p,SEP_COMMA)
#define  LOOP_NTo0P(n,loopFunc2,p)      LOOP_NTo0P_SEP(n,loopFunc2,p,SEP_COMMA)
#define  LOOP_NTo1P_CLS(n,loopFunc2,p)  LOOP_NTo1P_SEP(n,loopFunc2,p,SEP_SEMICOLON)
#define  LOOP_NTo0P_CLS(n,loopFunc2,p)  LOOP_NTo0P_SEP(n,loopFunc2,p,SEP_SEMICOLON)

#endif // __MACRO_LOOP_HPP__
