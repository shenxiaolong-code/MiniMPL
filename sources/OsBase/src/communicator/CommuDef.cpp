#include <communicator/CommuDef.h>

char* CCommBuffer::getCharBuf(unsigned iNewSize)
{
    return (char*)getBuffer(iNewSize);
}

char const* CCommBuffer::getCharBuf() const
{
    return (char const*)m_pBuf;
}
