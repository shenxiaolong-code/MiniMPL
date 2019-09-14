#ifndef __FOLDERITEMFOUNDER_H__
#define __FOLDERITEMFOUNDER_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/productSpecialDef.h>
#include <windows.h>

namespace OS_Win32
{
    class CFolderItem
    {
    public:
        CFolderItem(stlStringW const& rFolderPath);
        stlStringW fullpath(WCHAR const* pFile);
        stlStringW const& folderpath() const;

        void go();
        bool isValid() const;
        bool getFileData(WIN32_FIND_DATA& wfd) const;
        bool isDirectory() const;

    protected: 
        bool find();
        bool next();

        bool initPath(stlStringW const& rFolderPath);
        virtual void onItemCheck(WIN32_FIND_DATA const& rFileData);
        virtual void onItem(WCHAR const* pFile);
        virtual bool isExpectedItem(WIN32_FIND_DATA const& rFileData);

    protected:
        bool                m_bValid;
        HANDLE              m_hFile;
        WIN32_FIND_DATA     m_fileData;
        stlStringW          m_folderPath;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct IFolerItemMonitor
    {
        virtual ~IFolerItemMonitor(){};
        virtual void onItemFound(WCHAR const* pFile)=0;
    };
    template<typename TUF>
    struct TFolerItemMonitorImpl : public IFolerItemMonitor
    {  
        TUF m_uf;

        TFolerItemMonitorImpl(TUF const& rUf):m_uf(rUf){};
        virtual void onItemFound(WCHAR const* pFile)
        {
            m_uf(pFile);
        }
    };
    typedef stlSmartptr<IFolerItemMonitor>  TpFolerItemMonitor;

    template<typename TUF>
    TpFolerItemMonitor makeFolerItemMonitor(TUF const& rUf)
    {
        return TpFolerItemMonitor(new TFolerItemMonitorImpl<TUF>(rUf));
    }
}


#endif // __FOLDERITEMFOUNDER_H__
