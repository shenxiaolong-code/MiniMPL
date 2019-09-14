#include "testconfig_OsBase.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for <OsBase/directory.h>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_DIRECTORY to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_DIRECTORY

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_DIRECTORY
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_DIRECTORY
#endif

#if defined(RUN_EXAMPLE_) && !defined(COMPILE_EXAMPLE_)
    #define COMPILE_EXAMPLE_DIRECTORY
#endif

//#undef RUN_EXAMPLE_DIRECTORY
//#undef COMPILE_EXAMPLE_DIRECTORY

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_DIRECTORY
#include <win32/directory.h>
#include <UnitTestKit/tc_tracer.h>
#include <UnitTestKit/tc_path.h>
#include <MiniMPL/unaryFunctionCreater.hpp>

namespace UnitTest
{
    using namespace OS_Win32;

    struct  TC_FolderItemMonitor: OS_Win32::CFolderItemMonitor 
    {
        TC_FolderItemMonitor()
            : OS_Win32::CFolderItemMonitor(getOutputPathW())
        {   
            using namespace MiniMPL;
            MiniMPL::dbgOutput(TXT("\n\ntest TC_FolderItemMonitor:"));
            setTransfer(makeFolerItemMonitor(makeUnaryFunction(&TC_FolderItemMonitor::printFoundFile,*this,_$)));

            go();
        };

        void printFoundFile(stlStringW const& rFile)
        {
            MiniMPL::dbgOutputV(L"\n%s",rFile.c_str());
        }
    };

    struct UT_Directory : public OS_Win32::CDirectory 
    {
        UT_Directory()
            : OS_Win32::CDirectory(getOutputPathW()){};

        void dumpFile()
        {
            MiniMPL::dbgOutputV(L"\nfiles in [%s] :",folderpath().c_str());
            for (stlVector<stlStringW>::const_iterator it=m_fileList.begin();
                it!=m_fileList.end();++it)
            {
                MiniMPL::dbgOutputV(L"\n%s",(*it).c_str());
            }
        }

        void dumpSubfolder()
        {
            MiniMPL::dbgOutputV(L"\n\nsubdirectory in [%s] :",folderpath().c_str());
            for (stlVector<stlStringW>::const_iterator it=m_subFolderList.begin();
                it!=m_subFolderList.end();++it)
            {
                MiniMPL::dbgOutputV(L"\n%s",(*it).c_str());
            }
        }
    };

    inline void TestCase_directory()
    {
        PrintTestcase();
        UT_Directory fs;
        fs.dumpFile();
        fs.dumpSubfolder();

        TC_FolderItemMonitor fim;

    }

#ifdef RUN_EXAMPLE_DIRECTORY
    InitRunFunc(TestCase_directory);
#else //else of RUN_EXAMPLE_DIRECTORY

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_)=(outputTxtV(TXT("[Unit test run disabled] directory.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"directory.h\".")
    #endif
#endif  	// RUN_EXAMPLE_DIRECTORY
}

#else //else of COMPILE_EXAMPLE_DIRECTORY
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_)=(outputTxtV(TXT("[Unit test compile disabled] directory.h\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"directory.h\".")
    #endif
#endif // COMPILE_EXAMPLE_DIRECTORY

