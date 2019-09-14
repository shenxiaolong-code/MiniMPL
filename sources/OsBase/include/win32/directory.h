#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <win32/folderitemfounder.h>

namespace OS_Win32
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CFolderItemMonitor : public CFolderItem
    {
    public:
        CFolderItemMonitor(stlStringW const& rFolderPath);
        void setTransfer(TpFolerItemMonitor pItemMonitor);
        virtual void onItem( WCHAR const* pFile );

    protected:
        TpFolerItemMonitor  m_pItemMonitor;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CFolderItemMonitor_subFolder : public CFolderItemMonitor
    {
    public:
        CFolderItemMonitor_subFolder(stlStringW const& rFolderPath);
        virtual bool isExpectedItem( WIN32_FIND_DATA const& rFileData );

    protected:
        TpFolerItemMonitor  m_pItemMonitor;
    };

    class CFolderItemMonitor_file : public CFolderItemMonitor_subFolder
    {   
    public:
        CFolderItemMonitor_file(stlStringW const& rFolderPath);
        virtual bool isExpectedItem( WIN32_FIND_DATA const& rFileData );
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CDirectory  : public CFolderItem
    {
    public:
        CDirectory(stlStringW const& rFolderPath);
        virtual ~CDirectory();

        stlVector<stlStringW> const& fileList() const;
        stlVector<stlStringW> const& subFolderList() const;

    protected:
        virtual void onItem( WCHAR const* pFile );

    protected: 
        stlVector<stlStringW>   m_fileList;
        stlVector<stlStringW>   m_subFolderList;

    };
}


#endif // __DIRECTORY_H__
