#include <win32/registry.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/scanPrint.hpp>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#define RootKey_List(_)     \
_(HKEY_CLASSES_ROOT),       \
_(HKEY_CURRENT_USER),       \
_(HKEY_LOCAL_MACHINE),      \
_(HKEY_USERS)

#if 1==USE_UNICODE_STRING
    #define RootKey_Txt(_) L## #_
#else
    #define RootKey_Txt(_) #_
#endif
stlChar* RootKeyArr[4]={RootKey_List(RootKey_Txt)};

namespace OS_Win32
{
#define KeyIdx  (LONG)m_rootKey & 0xF

    CRegistry::CRegistry( HKEY rootKey )
        : m_rootKey(rootKey)
    {
        ASSERT_AND_LOG(HKEY_LOCAL_MACHINE==m_rootKey ||
            HKEY_CLASSES_ROOT==m_rootKey ||
            HKEY_CURRENT_USER==m_rootKey ||
            HKEY_USERS==m_rootKey);
    }

    CRegistry::~CRegistry()
    {
        close();
    }

    bool CRegistry::listSubKeys( stlString const& keyPath,stlVector<stlString>& subKeys )
    {
        if (!open(keyPath,KEY_READ))
        {
            return false;
        }

        TCHAR    keyNameBuf[MAX_KEY_LENGTH] = {0};
        DWORD    keyNameBufSize;
        DWORD    cSubKeys=0;

        DWORD retCode; 
        retCode = RegQueryInfoKey(m_lastOpenedKey,NULL,NULL,NULL,&cSubKeys,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
        // Enumerate the sub keys, until RegEnumKeyEx fails.
        if (cSubKeys)
        {
            for (DWORD idx=0; idx<cSubKeys && (retCode == ERROR_SUCCESS); idx++) 
            { 
                keyNameBufSize = MAX_KEY_LENGTH;
                retCode = RegEnumKeyEx(m_lastOpenedKey, idx,keyNameBuf,&keyNameBufSize,NULL,NULL,NULL,NULL); 
                if (retCode == ERROR_SUCCESS) 
                {
                    subKeys.push_back(keyNameBuf);
                }
            }
        }

        return true;
    }

    bool CRegistry::readBinaryValue( stlString const& valueName, unsigned char* pValue, ULONG& nBytes )
    {
        if (0 == m_keyPath.size())
        {
            return false;
        }
        ASSERT_AND_LOG_INFO(verifyKeyPath(m_keyPath),(m_lastErrorText.c_str()));

        LONG lRes;
        DWORD dwType;
        lRes = ::RegQueryValueEx(m_lastOpenedKey, valueName.c_str(), NULL, &dwType,pValue,&nBytes);
        if (lRes != ERROR_SUCCESS || dwType != REG_BINARY)
        {
            outputTxtV(TXT("[error info]\n%s"),getErrorText(GetLastError()).c_str());
            return false;
        }

        return true;
    }


    bool CRegistry::readStringValue( stlString const& valueName, stlString& val )
    {
        if (0 == m_keyPath.size())
        {
            return false;
        } 
        ASSERT_AND_LOG_INFO(verifyKeyPath(m_keyPath),(m_lastErrorText.c_str()));

        TCHAR	valBuffer[1024] = {0};

        LONG lRes;
        DWORD dwType;
        ULONG nBytes = sizeof(valBuffer);
        lRes = ::RegQueryValueEx(m_lastOpenedKey, valueName.c_str(), NULL, &dwType, (LPBYTE)valBuffer,&nBytes);
        if (lRes != ERROR_SUCCESS || (dwType != REG_SZ && dwType != REG_EXPAND_SZ))
        {
            outputTxtV(TXT("[error info]\n%s"),getErrorText(GetLastError()).c_str());            
            return false;
        }

        if(nBytes!=0 && valBuffer[nBytes-1]!=0)
        {
            return false;	//invalid data
        }

        val	= valBuffer;
        return true;

    }

    bool CRegistry::open( stlString const& keyPath,REGSAM dwAccess/*=KEY_READ*/ )
    {
        if (0 == keyPath.size())
        {
            return false;
        }

        ASSERT_AND_LOG_INFO(verifyKeyPath(keyPath),(m_lastErrorText.c_str()));

        if (keyPath != m_keyPath || dwAccess != m_dwAccess)
        {
            close();

            if( RegOpenKeyEx( m_rootKey,keyPath.c_str(),0,dwAccess,&m_lastOpenedKey) == ERROR_SUCCESS)
            {
                m_keyPath = keyPath;
                m_dwAccess	= dwAccess;
                return true;
            }
            else
            {
                outputTxtV(TXT("[error info]\n%s"),getErrorText(GetLastError()).c_str());
                return false;
            }
        }

        return 0 != m_keyPath.size();
    }

    bool CRegistry::close()
    {
        if (0!=m_keyPath.size())
        {
            RegCloseKey(m_lastOpenedKey);
            m_keyPath.empty();
        }

        return true;
    }

    stlString CRegistry::getErrorText( DWORD eCode )
    {
        LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, eCode, 0,(LPTSTR) &lpMsgBuf,0,NULL);

        m_lastErrorText = (LPCTSTR)lpMsgBuf;
        LocalFree( lpMsgBuf );
        return m_lastErrorText;
    }

    bool CRegistry::verifyKeyPath( stlString const& keyPath )
    {
        if (keyPath.size()>=std::char_traits<stlChar>::length(RootKeyArr[KeyIdx]))  
        {
            if (0==std::char_traits<stlChar>::compare(RootKeyArr[KeyIdx],keyPath.c_str(),std::char_traits<stlChar>::length(RootKeyArr[KeyIdx])))
            {
                stlChar buf[1024]={0};
                printBuf(buf,TXT("key path[%s] shouldn't include [%s\\]"),keyPath.c_str(),RootKeyArr[KeyIdx]);
                m_lastErrorText = buf;
                return false;
            }            
        }
        return true;
    }

}