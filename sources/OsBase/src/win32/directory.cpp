#include <win32/directory.h>
#include "MiniMPL/arrayTrait.hpp"
#include "win32/handleguard.h"
#include "win32/WinApiPack.h"

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CFolderItemMonitor::CFolderItemMonitor( stlStringW const& rFolderPath )
        : CFolderItem(rFolderPath)
    {
    }

    void CFolderItemMonitor::setTransfer( TpFolerItemMonitor pItemMonitor )
    {
        m_pItemMonitor = pItemMonitor;
    }

    void CFolderItemMonitor::onItem( WCHAR const* pFile )
    {
        if (m_pItemMonitor)
        {
            m_pItemMonitor->onItemFound(pFile);
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CFolderItemMonitor_subFolder::CFolderItemMonitor_subFolder( stlStringW const& rFolderPath) 
        : CFolderItemMonitor(rFolderPath)
    { 
    }

    bool CFolderItemMonitor_subFolder::isExpectedItem( WIN32_FIND_DATA const& /*rFileData*/ )
    {
        return isDirectory();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CFolderItemMonitor_file::CFolderItemMonitor_file( stlStringW const& rFolderPath)
        : CFolderItemMonitor_subFolder(rFolderPath)
    {
    }

    bool CFolderItemMonitor_file::isExpectedItem( WIN32_FIND_DATA const& rFileData )
    {
        return !CFolderItemMonitor_subFolder::isExpectedItem(rFileData);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CDirectory::CDirectory( stlStringW const& rFolderPath )
        : CFolderItem(rFolderPath)
    {        
        go();
    }

    CDirectory::~CDirectory()
    {
    }

    stlVector<stlStringW> const& CDirectory::fileList() const
    {
        return m_fileList;
    }

    stlVector<stlStringW> const& CDirectory::subFolderList() const
    {
        return m_subFolderList;
    }

    void CDirectory::onItem( WCHAR const* pFile )
    {
        if (isDirectory())
        {
            m_subFolderList.push_back(pFile);
        }
        else
        {
            m_fileList.push_back(pFile);
        }
    }
}
