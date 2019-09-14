#ifndef __MACRO_LONGJUMP_H__
#define __MACRO_LONGJUMP_H__
/***********************************************************************************************************************
* Description         : free to switch on/off long jump function in same deep call function stack.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>

#if ENABLE_LONG_JUMP
    // Address for long jump to jump to , feature for rapid return    
    #include <setjmp.h>
    #define LongJump_FParam         ,jmp_buf& mark              //formal parameter
    #define LongJump_RParam         ,mark                       //real parameter
    #define LongJump_RParam2        ,mark2                      //real parameter
    #define LongJump_Return0()      longjmp(mark,0)
    #define LongJump_Returnx(x)     longjmp(mark,x)
    #define LongJump_Begin()        jmp_buf mark;       \
            if (0==setjmp(mark))                        \
            {
    #define LongJump_Begin2()       jmp_buf mark2;      \
            if (0==setjmp(mark2))                       \
            {
    #define  LongJump_End()                             \
            }
#else
    #define LongJump_FParam
    #define LongJump_RParam
    #define LongJump_RParam2
    #define LongJump_Return0()
    #define LongJump_Returnx(x)
    #define LongJump_Begin()
    #define LongJump_Begin2()
    #define LongJump_End()
#endif // #if ENABLE_LONG_JUMP

#endif // __MACRO_LONGJUMP_H__
