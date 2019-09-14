#include <Win32/handleguard.h>

namespace OS_Win32
{
    OnReturn::OnReturn( MiniMPL::TpCallbacker pcall ) : m_pcall(pcall)
    { 
    }

    OnReturn::~OnReturn()
    {
        if (m_pcall)
        {
            m_pcall->execute();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CHandle::CHandle()
        :m_pHandle( new HANDLE(INVALID_HANDLE_VALUE))
    { 
    }

    CHandle::CHandle( HANDLE handle )
        :m_pHandle( new HANDLE(handle))
    {
    }

    CHandle::CHandle( CHandle const& rOther )
    {
        m_pHandle = rOther.m_pHandle;
    }

    CHandle::~CHandle()
    {  
        if (1==m_pHandle.use_count())
        {
            close();
        }
    }

    CHandle& CHandle::operator=( CHandle const& rOther )
    {   
        close();
        m_pHandle = rOther.m_pHandle;
        return *this;
    }

    bool CHandle::operator==( HANDLE handle ) const
    {
        return *m_pHandle == handle;
    }

    bool CHandle::operator!=( HANDLE handle ) const
    {
        return !(*this==handle);
    }

    HANDLE& CHandle::rawHandle()
    {
        return *m_pHandle;
    }

    HANDLE const& CHandle::rawHandle() const
    {
        return *m_pHandle;
    }

    CHandle::operator HANDLE const&() const
    {
        return *m_pHandle;
    }

    CHandle::operator HANDLE&()
    {
        return *m_pHandle;
    }

    bool CHandle::close()
    {  
        if (INVALID_HANDLE_VALUE != *m_pHandle)
        {
            CloseHandle(*m_pHandle);
            *m_pHandle = INVALID_HANDLE_VALUE;
        }
        return true;
    }

    bool CHandle::isValid() const
    {
        return INVALID_HANDLE_VALUE != *m_pHandle;
    }

}
