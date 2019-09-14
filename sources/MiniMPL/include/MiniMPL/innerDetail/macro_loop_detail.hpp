#ifndef __MACRO_LOOP_DETAIL_HPP__
#define __MACRO_LOOP_DETAIL_HPP__
/***********************************************************************************************************************
* Description         : detail implement of macro_Loop.hpp
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>

namespace MiniMPL
{
#define SEP_COMMA()         ,
#define SEP_SEMICOLON()     ;

#define  LOOP_IMPL_1To1(loopFunc,unused)    loopFunc(1)

#define  LOOP_IMPL_1To2(loopFunc,sep)       LOOP_IMPL_1To1(loopFunc,sep) sep##()   loopFunc(2)
#define  LOOP_IMPL_1To3(loopFunc,sep)       LOOP_IMPL_1To2(loopFunc,sep) sep##()   loopFunc(3)
#define  LOOP_IMPL_1To4(loopFunc,sep)       LOOP_IMPL_1To3(loopFunc,sep) sep##()   loopFunc(4)
#define  LOOP_IMPL_1To5(loopFunc,sep)       LOOP_IMPL_1To4(loopFunc,sep) sep##()   loopFunc(5)
#define  LOOP_IMPL_1To6(loopFunc,sep)       LOOP_IMPL_1To5(loopFunc,sep) sep##()   loopFunc(6)
#define  LOOP_IMPL_1To7(loopFunc,sep)       LOOP_IMPL_1To6(loopFunc,sep) sep##()   loopFunc(7)
#define  LOOP_IMPL_1To8(loopFunc,sep)       LOOP_IMPL_1To7(loopFunc,sep) sep##()   loopFunc(8)
#define  LOOP_IMPL_1To9(loopFunc,sep)       LOOP_IMPL_1To8(loopFunc,sep) sep##()   loopFunc(9)
#define  LOOP_IMPL_1To10(loopFunc,sep)      LOOP_IMPL_1To9(loopFunc,sep) sep##()   loopFunc(10)
#define  LOOP_IMPL_1To11(loopFunc,sep)      LOOP_IMPL_1To10(loopFunc,sep) sep##()  loopFunc(11)
#define  LOOP_IMPL_1To12(loopFunc,sep)      LOOP_IMPL_1To11(loopFunc,sep) sep##()  loopFunc(12)
#define  LOOP_IMPL_1To13(loopFunc,sep)      LOOP_IMPL_1To12(loopFunc,sep) sep##()  loopFunc(13)
#define  LOOP_IMPL_1To14(loopFunc,sep)      LOOP_IMPL_1To13(loopFunc,sep) sep##()  loopFunc(14)
#define  LOOP_IMPL_1To15(loopFunc,sep)      LOOP_IMPL_1To14(loopFunc,sep) sep##()  loopFunc(15)
#define  LOOP_IMPL_1To16(loopFunc,sep)      LOOP_IMPL_1To15(loopFunc,sep) sep##()  loopFunc(16)
#define  LOOP_IMPL_1To17(loopFunc,sep)      LOOP_IMPL_1To16(loopFunc,sep) sep##()  loopFunc(17)
#define  LOOP_IMPL_1To18(loopFunc,sep)      LOOP_IMPL_1To17(loopFunc,sep) sep##()  loopFunc(18)
#define  LOOP_IMPL_1To19(loopFunc,sep)      LOOP_IMPL_1To18(loopFunc,sep) sep##()  loopFunc(19)
#define  LOOP_IMPL_1To20(loopFunc,sep)      LOOP_IMPL_1To19(loopFunc,sep) sep##()  loopFunc(20)

#define  LOOP_1ToN_SEP(n,loopFunc,sep)      LOOP_IMPL_1To##n(loopFunc,sep)
#define  LOOP_0ToN_SEP(n,loopFunc,sep)      loopFunc(0) sep##() LOOP_IMPL_1To##n(loopFunc,sep)
///////////////////////////////////////////////////////////////////////////////////

#define  LOOP_IMPL_2To1(loopFunc,sep)       loopFunc(2) sep##()   LOOP_IMPL_1To1(loopFunc,sep)
#define  LOOP_IMPL_3To1(loopFunc,sep)       loopFunc(3) sep##()   LOOP_IMPL_2To1(loopFunc,sep)
#define  LOOP_IMPL_4To1(loopFunc,sep)       loopFunc(4) sep##()   LOOP_IMPL_3To1(loopFunc,sep)
#define  LOOP_IMPL_5To1(loopFunc,sep)       loopFunc(5) sep##()   LOOP_IMPL_4To1(loopFunc,sep)
#define  LOOP_IMPL_6To1(loopFunc,sep)       loopFunc(6) sep##()   LOOP_IMPL_5To1(loopFunc,sep)
#define  LOOP_IMPL_7To1(loopFunc,sep)       loopFunc(7) sep##()   LOOP_IMPL_6To1(loopFunc,sep)
#define  LOOP_IMPL_8To1(loopFunc,sep)       loopFunc(8) sep##()   LOOP_IMPL_7To1(loopFunc,sep)
#define  LOOP_IMPL_9To1(loopFunc,sep)       loopFunc(9) sep##()   LOOP_IMPL_8To1(loopFunc,sep)
#define  LOOP_IMPL_10To1(loopFunc,sep)      loopFunc(10) sep##()  LOOP_IMPL_9To1(loopFunc,sep)
#define  LOOP_IMPL_11To1(loopFunc,sep)      loopFunc(11) sep##()  LOOP_IMPL_10To1(loopFunc,sep)
#define  LOOP_IMPL_12To1(loopFunc,sep)      loopFunc(12) sep##()  LOOP_IMPL_11To1(loopFunc,sep)
#define  LOOP_IMPL_13To1(loopFunc,sep)      loopFunc(13) sep##()  LOOP_IMPL_12To1(loopFunc,sep)
#define  LOOP_IMPL_14To1(loopFunc,sep)      loopFunc(14) sep##()  LOOP_IMPL_13To1(loopFunc,sep)
#define  LOOP_IMPL_15To1(loopFunc,sep)      loopFunc(15) sep##()  LOOP_IMPL_14To1(loopFunc,sep)
#define  LOOP_IMPL_16To1(loopFunc,sep)      loopFunc(16) sep##()  LOOP_IMPL_15To1(loopFunc,sep)
#define  LOOP_IMPL_17To1(loopFunc,sep)      loopFunc(17) sep##()  LOOP_IMPL_16To1(loopFunc,sep)
#define  LOOP_IMPL_18To1(loopFunc,sep)      loopFunc(18) sep##()  LOOP_IMPL_17To1(loopFunc,sep)
#define  LOOP_IMPL_19To1(loopFunc,sep)      loopFunc(19) sep##()  LOOP_IMPL_18To1(loopFunc,sep)
#define  LOOP_IMPL_20To1(loopFunc,sep)      loopFunc(20) sep##()  LOOP_IMPL_19To1(loopFunc,sep)

#define  LOOP_NTo1_SEP(n,loopFunc,sep)      LOOP_IMPL_##n##To1(loopFunc,sep)
#define  LOOP_NTo0_SEP(n,loopFunc,sep)      LOOP_IMPL_##n##To1(loopFunc,sep) sep##() loopFunc(0)
///////////////////////////////////////////////////////////////////////////////////
#define  LOOP_IMPL_1To1P(loopFunc2,p,unused)     loopFunc2(1,p)

#define  LOOP_IMPL_1To2P(loopFunc2,p,sep)   LOOP_IMPL_1To1P(loopFunc2,p,sep) sep##()   loopFunc2(2,p)
#define  LOOP_IMPL_1To3P(loopFunc2,p,sep)   LOOP_IMPL_1To2P(loopFunc2,p,sep) sep##()   loopFunc2(3,p)
#define  LOOP_IMPL_1To4P(loopFunc2,p,sep)   LOOP_IMPL_1To3P(loopFunc2,p,sep) sep##()   loopFunc2(4,p)
#define  LOOP_IMPL_1To5P(loopFunc2,p,sep)   LOOP_IMPL_1To4P(loopFunc2,p,sep) sep##()   loopFunc2(5,p)
#define  LOOP_IMPL_1To6P(loopFunc2,p,sep)   LOOP_IMPL_1To5P(loopFunc2,p,sep) sep##()   loopFunc2(6,p)
#define  LOOP_IMPL_1To7P(loopFunc2,p,sep)   LOOP_IMPL_1To6P(loopFunc2,p,sep) sep##()   loopFunc2(7,p)
#define  LOOP_IMPL_1To8P(loopFunc2,p,sep)   LOOP_IMPL_1To7P(loopFunc2,p,sep) sep##()   loopFunc2(8,p)
#define  LOOP_IMPL_1To9P(loopFunc2,p,sep)   LOOP_IMPL_1To8P(loopFunc2,p,sep) sep##()   loopFunc2(9,p)
#define  LOOP_IMPL_1To10P(loopFunc2,p,sep)  LOOP_IMPL_1To9P(loopFunc2,p,sep) sep##()   loopFunc2(10,p)
#define  LOOP_IMPL_1To11P(loopFunc2,p,sep)  LOOP_IMPL_1To10P(loopFunc2,p,sep) sep##()  loopFunc2(11,p)
#define  LOOP_IMPL_1To12P(loopFunc2,p,sep)  LOOP_IMPL_1To11P(loopFunc2,p,sep) sep##()  loopFunc2(12,p)
#define  LOOP_IMPL_1To13P(loopFunc2,p,sep)  LOOP_IMPL_1To12P(loopFunc2,p,sep) sep##()  loopFunc2(13,p)
#define  LOOP_IMPL_1To14P(loopFunc2,p,sep)  LOOP_IMPL_1To13P(loopFunc2,p,sep) sep##()  loopFunc2(14,p)
#define  LOOP_IMPL_1To15P(loopFunc2,p,sep)  LOOP_IMPL_1To14P(loopFunc2,p,sep) sep##()  loopFunc2(15,p)
#define  LOOP_IMPL_1To16P(loopFunc2,p,sep)  LOOP_IMPL_1To15P(loopFunc2,p,sep) sep##()  loopFunc2(16,p)
#define  LOOP_IMPL_1To17P(loopFunc2,p,sep)  LOOP_IMPL_1To16P(loopFunc2,p,sep) sep##()  loopFunc2(17,p)
#define  LOOP_IMPL_1To18P(loopFunc2,p,sep)  LOOP_IMPL_1To17P(loopFunc2,p,sep) sep##()  loopFunc2(18,p)
#define  LOOP_IMPL_1To19P(loopFunc2,p,sep)  LOOP_IMPL_1To18P(loopFunc2,p,sep) sep##()  loopFunc2(19,p)
#define  LOOP_IMPL_1To20P(loopFunc2,p,sep)  LOOP_IMPL_1To19P(loopFunc2,p,sep) sep##()  loopFunc2(20,p)

#define  LOOP_1ToNP_SEP(n,loopFunc2,p,sep)  LOOP_IMPL_1To##n##P(loopFunc2,p,sep)
#define  LOOP_0ToNP_SEP(n,loopFunc2,p,sep)  loopFunc2(0,p) sep##() LOOP_IMPL_1To##n##P(loopFunc2,p,sep)
///////////////////////////////////////////////////////////////////////////////////
#define  LOOP_IMPL_2To1P(loopFunc2,p,sep)   loopFunc2(2,p) sep##()   LOOP_IMPL_1To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_3To1P(loopFunc2,p,sep)   loopFunc2(3,p) sep##()   LOOP_IMPL_2To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_4To1P(loopFunc2,p,sep)   loopFunc2(4,p) sep##()   LOOP_IMPL_3To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_5To1P(loopFunc2,p,sep)   loopFunc2(5,p) sep##()   LOOP_IMPL_4To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_6To1P(loopFunc2,p,sep)   loopFunc2(6,p) sep##()   LOOP_IMPL_5To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_7To1P(loopFunc2,p,sep)   loopFunc2(7,p) sep##()   LOOP_IMPL_6To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_8To1P(loopFunc2,p,sep)   loopFunc2(8,p) sep##()   LOOP_IMPL_7To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_9To1P(loopFunc2,p,sep)   loopFunc2(9,p) sep##()   LOOP_IMPL_8To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_10To1P(loopFunc2,p,sep)  loopFunc2(10,p) sep##()  LOOP_IMPL_9To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_11To1P(loopFunc2,p,sep)  loopFunc2(11,p) sep##()  LOOP_IMPL_10To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_12To1P(loopFunc2,p,sep)  loopFunc2(12,p) sep##()  LOOP_IMPL_11To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_13To1P(loopFunc2,p,sep)  loopFunc2(13,p) sep##()  LOOP_IMPL_12To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_14To1P(loopFunc2,p,sep)  loopFunc2(14,p) sep##()  LOOP_IMPL_13To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_15To1P(loopFunc2,p,sep)  loopFunc2(15,p) sep##()  LOOP_IMPL_14To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_16To1P(loopFunc2,p,sep)  loopFunc2(16,p) sep##()  LOOP_IMPL_15To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_17To1P(loopFunc2,p,sep)  loopFunc2(17,p) sep##()  LOOP_IMPL_16To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_18To1P(loopFunc2,p,sep)  loopFunc2(18,p) sep##()  LOOP_IMPL_17To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_19To1P(loopFunc2,p,sep)  loopFunc2(19,p) sep##()  LOOP_IMPL_18To1P(loopFunc2,p,sep)
#define  LOOP_IMPL_20To1P(loopFunc2,p,sep)  loopFunc2(20,p) sep##()  LOOP_IMPL_19To1P(loopFunc2,p,sep)

#define  LOOP_NTo1P_SEP(n,loopFunc2,p,sep)  LOOP_IMPL_##n##To1##P(loopFunc2,p,sep)
#define  LOOP_NTo0P_SEP(n,loopFunc2,p,sep)  LOOP_IMPL_##n##To1##P(loopFunc2,p,sep) sep##() loopFunc2(0,p)
}


#endif // __MACRO_LOOP_DETAIL_HPP__
