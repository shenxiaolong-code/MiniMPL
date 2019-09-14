#include <Win32/memmapfile.h>
#include "MiniMPL/arrayTrait.hpp"


namespace OS_Win32
{

    CMemMapFile::CMemMapFile()
        : m_mapview(NULL)
    {

    }

    CMemMapFile::~CMemMapFile()
    {
        close();
    }

    LPVOID CMemMapFile::acceptFile( CHandle const& hFile , bool bReadOnly )
    {
        if (m_handle[EHandleFile]!=hFile)
        {
            close();
        }

        m_handle[EHandleFile] = hFile;
        if (m_handle[EHandleFile].isValid())
        {
            DWORD flProtect = SEC_COMMIT;
            flProtect |= bReadOnly ? PAGE_READONLY : PAGE_READWRITE;
            
            m_handle[EHandleMap] = CHandle(CreateFileMapping(m_handle[EHandleFile], 0, flProtect, 0, 0, 0));
            if (m_handle[EHandleMap].isValid())
            {
                m_mapview = MapViewOfFile(m_handle[EHandleMap], bReadOnly ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS, 0, 0, 0);
            }
        }

        return m_mapview;
    }

    LPVOID CMemMapFile::getPtr()
    {
        return m_mapview;
    }

    bool CMemMapFile::isValid()
    {
        return NULL != m_mapview;
    }

    bool CMemMapFile::close()
    {
        if (NULL != m_mapview)
        {
            UnmapViewOfFile(m_mapview);
            m_mapview = NULL;
        }

        for (int idx=arraySize(m_handle)-1;idx>=0;--idx)
        {
            if (m_handle[idx].isValid())
            {
                m_handle[idx].close();
            }
        }
        return true;
    }

}
