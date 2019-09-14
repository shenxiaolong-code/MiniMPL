#include <thread\threadManager.h>
#include "MiniMPL\container.hpp"

CThreadMananger::~CThreadMananger()
{

}

CThreadBase* CThreadMananger::getThread( ThreadID id ) const
{
    for (const_iterator it=begin(); it!=end();it++)
    {
        if ((*it)->getThreadId()==id)
        {
            return *it;
        }
    }
    return NULL;
}

bool CThreadMananger::registerThread( CThreadBase& newThrd)
{
    if (!getThread(newThrd.getThreadId()))
    {
        push_back(&newThrd);
        return true;
    }
    return false;
}

bool CThreadMananger::unregisterThread( CThreadBase& existThrd)
{
    for (iterator it=begin(); it!=end();it++)
    {
        if ((*it)->getThreadId()==existThrd.getThreadId())
        {
            std::swap(*it,back());
            erase(--end());
            return true;
        }
    }

    return false;
}

