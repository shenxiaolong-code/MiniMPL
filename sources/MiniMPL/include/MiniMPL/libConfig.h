#ifndef __LIBCONFIG_H__
#define __LIBCONFIG_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#define HAS_BOOST_SUPPORT                               0
//_UNICODE is defined by compiler,UNICODE is defined by user, e.g. MS
#ifdef _UNICODE
    #define USE_UNICODE_STRING                          1
#else
    #define USE_UNICODE_STRING                          0
#endif
#define USE_STD_TRAIT                                   0
#define USE_MINIMPL_SMARTPOINTER                        0
#define CONST_CONTAINER_HAS_ITERATOR                    0
#define USE_FLOAT_MIN_THRESHOLD_CMP                     1
#define ENABLE_UNSAFE_SCANPRINT							0   
#define ENABLE_DUMP										1   
#define ASSERT_NO_INFO_OUTPUT							0 
#define ENABLE_TRACE									0
#define ENABLE_LONG_JUMP								1
#define ENABLE_COMPILE_WARNING							1
#define ENABLE_TRACE_COMPILE							0
#define ENABLE_TRACE_COMPILE_SRC						1
#define ENABLE_RELEASE_ASSERT							1
#define ENABLE_STATIC_ASSERT_NEED_COMPLETE_TYPE			1

#endif // __LIBCONFIG_H__
