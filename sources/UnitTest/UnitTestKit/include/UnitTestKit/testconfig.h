#ifndef TESTCONFIG_H__
#define TESTCONFIG_H__
/***********************************************************************************************************************
* Description         : define global unit test compile options
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/macro_assert.h>
#include <MiniMPL/macro_makeTxt.h>
#include <MiniMPL/macro_init.h>

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
    #define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif
#ifndef WINVER
    #define WINVER 0x0600
#endif

//detect memory leak, if needn't , comment it out.
#include <MiniMPL/vldFix.h>

#define RUN_WARNING_NO_TESTCASE_COMPILE
#define RUN_WARNING_NO_TESTCASE_RUN
#define BUILD_WARNING_NO_TESTCASE_COMPILE
#define BUILD_WARNING_NO_TESTCASE_RUN
#define COMPILE_EXAMPLE_ALL          
#define RUN_EXAMPLE_ALL   

#endif // TESTCONFIG_H__
