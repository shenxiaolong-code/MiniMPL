#include <win32/folderitemfounder.h>
#include <atlpath.h>
#include <MiniMPL/macro_assert.h>

namespace OS_Win32
{

    CFolderItem::CFolderItem( stlStringW const& rFolderPath )
        : m_bValid(false)
    {
        m_bValid = initPath(rFolderPath);
    }

    stlStringW CFolderItem::fullpath(WCHAR const* pFile)
    {
        ASSERT_AND_LOG(isValid());
        return m_folderPath+L"\\"+pFile;
    }

    stlStringW const& CFolderItem::folderpath() const
    {
        return m_folderPath;
    }

    bool CFolderItem::find()
    {
        if (m_bValid)
        {
            stlStringW sFilter = m_folderPath+L"\\*.*";
            m_hFile = FindFirstFile(sFilter.c_str(),&m_fileData);
            m_bValid = INVALID_HANDLE_VALUE!=m_hFile;
            if (m_bValid)
            {
                onItemCheck(m_fileData);
            }
        }
        return m_bValid;
    }

    bool CFolderItem::next()
    {
        if (isValid())
        {               
            m_bValid = TRUE==FindNextFile(m_hFile,&m_fileData);
            if (m_bValid)
            {
                onItemCheck(m_fileData);
            }
            return m_bValid;
        }
        return false;
    }

    void CFolderItem::go()
    {
        if (find())
        {
            while(next());
        }
    }

    bool CFolderItem::isValid() const
    {
        return m_bValid;
    }

    bool CFolderItem::getFileData( WIN32_FIND_DATA& wfd ) const
    {
        if (isValid())
        {
            wfd = m_fileData;
            return true;
        }
        return false;
    }

    bool CFolderItem::isDirectory() const
    {
        ASSERT_AND_LOG(isValid());
        return 0!=(m_fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool CFolderItem::initPath( stlStringW const& rFolderPath )
    {
        unsigned iSize = rFolderPath.length();
        if ('\\'==rFolderPath[iSize-1])
        {
            iSize--;
        }
        m_folderPath = rFolderPath.substr(0,iSize);
        return TRUE==ATL::ATLPath::FileExists(m_folderPath.c_str());
    }

    void CFolderItem::onItemCheck( WIN32_FIND_DATA const& rFileData )
    {
        if (isExpectedItem(rFileData))
        {
            onItem(rFileData.cFileName);
        }
        else
        {   
            next();
        }
    }

    void CFolderItem::onItem( WCHAR const* pFile )
    {

    }

    bool CFolderItem::isExpectedItem( WIN32_FIND_DATA const& rFileData )
    {
        stlStringW dir=rFileData.cFileName;
        return !(L"."==dir || L".."==dir) ;
    }

}
