#ifndef __COMMUDEF_H__
#define __COMMUDEF_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/macro_assert.h>
#include <utility/dynamicBuffer.hpp>

typedef unsigned char        TCommBufferElement;
struct CCommBuffer : public  TDynamicBuffer<TCommBufferElement>
{
    char const* getCharBuf() const;

    char* getCharBuf(unsigned iNewSize);
};

#endif // __COMMUDEF_H__
