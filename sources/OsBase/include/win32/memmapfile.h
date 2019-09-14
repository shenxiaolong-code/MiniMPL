#ifndef __MEMMAPFILE_H__
#define __MEMMAPFILE_H__
/***********************************************************************************************************************
* Description         : easy to use memory map file
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <win32/handleguard.h>

namespace OS_Win32
{                   
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMemMapFile
    {
        enum {EHandleFile=0,EHandleMap};
    public:
    	CMemMapFile();
    	virtual ~CMemMapFile();

        LPVOID  acceptFile(CHandle const& hFile , bool bReadOnly);
        LPVOID  getPtr();
        bool    isValid();
        bool    close();
    
    protected:       
        LPVOID      m_mapview;
        CHandle     m_handle[1+EHandleMap];
    };

}


#endif // __MEMMAPFILE_H__
