#include <UnitTestKit\tc_path.h>
#include <MiniMPL\arrayTrait.hpp>

#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

namespace UnitTest
{
    stlStringA getOutputPathA()
    {   
        stlStringA::value_type path[MAX_PATH];
//         GetModuleFileName(NULL,path,MAX_PATH);
//         //GetModuleFileName(NULL, modulename,arraySize(modulename));
//         PathRemoveFileSpec(path);  //从文件全路径中除去文件名及扩展名

        GetCurrentDirectoryA(arraySize(path),path);
        return path;
    }

    stlStringW getOutputPathW()
    {
        stlStringW::value_type  path[MAX_PATH];
        //         GetModuleFileName(NULL,path,MAX_PATH);
        //         //GetModuleFileName(NULL, modulename,arraySize(modulename));
        //         PathRemoveFileSpec(path);  //从文件全路径中除去文件名及扩展名

        GetCurrentDirectoryW(arraySize(path),path);
        return path;
    }

}