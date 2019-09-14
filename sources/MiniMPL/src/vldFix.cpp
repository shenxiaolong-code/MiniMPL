#include <MiniMPL/vldFix.h>
#if Enable_VLD_FIX==1

#include <typeinfo>
#include <crtdbg.h>

//refer to : http://stackoverflow.com/questions/8308671/memory-leaks-after-using-typeinfoname
struct _CrtMemBlockHeader
{
    struct _CrtMemBlockHeader * pBlockHeaderNext;
    struct _CrtMemBlockHeader * pBlockHeaderPrev;
    char *                      szFileName;
    int                         nLine;
#ifdef _WIN64
    int                         nBlockUse;
    size_t                      nDataSize;
#else
    size_t                      nDataSize;
    int                         nBlockUse;
#endif
    long                        lRequest;
    unsigned char               gap[4];
};

namespace MiniMPL
{
    struct FixTypeInfoBlockUse  
    {
        ~FixTypeInfoBlockUse()
        {
            __type_info_node* pNode = __type_info_root_node.next;

            while(pNode != NULL)
            {
                __type_info_node* pNext = pNode->next;

                (((_CrtMemBlockHeader*)pNode) - 1)->nBlockUse = _CRT_BLOCK;

                if (pNode->memPtr != NULL)
                    (((_CrtMemBlockHeader*)pNode->memPtr) - 1)->nBlockUse = _CRT_BLOCK;

                pNode = pNext;
            }
        }
    } exitCall;
}
#else

#include <MiniMPL/macro_traceLog.h>
COMPILE_WARNING("VLD feature is disabled")

#endif//defined(Enable_VLD)