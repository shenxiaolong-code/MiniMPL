#ifndef __SOCKET_OPT_DEF_H__
#define __SOCKET_OPT_DEF_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <winsock2.h>
#include <MiniMPL\kitType.hpp>
//ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.en/winsock/winsock/getsockopt_2.htm

#ifndef SO_CONNECT_TIME
    #define SO_CONNECT_TIME             0x700C
#endif

namespace OS_Win32
{
    #define SOCKET_OPT_LIST(_)                      \
    _(SO_ACCEPTCONN,            BOOL)               \
    _(SO_BROADCAST,             BOOL)               \
    _(SO_CONDITIONAL_ACCEPT,    BOOL)               \
    _(SO_CONNECT_TIME,          DWORD)              \
    _(SO_DEBUG,                 BOOL)               \
    _(SO_DONTLINGER,            BOOL)               \
    _(SO_DONTROUTE,             BOOL)               \
    _(SO_ERROR,                 int)                \
    _(SO_GROUP_ID,              GROUP)              \
    _(SO_GROUP_PRIORITY,        int)                \
    _(SO_KEEPALIVE,             BOOL)               \
    _(SO_LINGER,                LINGER)             \
    _(SO_MAX_MSG_SIZE,          unsigned)           \
    _(SO_OOBINLINE,             BOOL)               \
    _(SO_PROTOCOL_INFO,         WSAPROTOCOL_INFO)   \
    _(SO_RCVBUF,                int)                \
    _(SO_REUSEADDR,             BOOL)               \
    _(SO_SNDBUF,                int)                \
    _(SO_TYPE,                  int)                

#define SOCK_OPT_ENUM(a,b)    E##a = a,

    enum ESockOpt
    {
        SOCKET_OPT_LIST(SOCK_OPT_ENUM)
    };

#define SOCK_OPT_Val_Type_Def(a,b)  \
    template<> struct GetSockOptValueType< E##a > : public MiniMPL::Type2Type< ##b >{};
    template<ESockOpt opt> struct GetSockOptValueType;
    SOCKET_OPT_LIST(SOCK_OPT_Val_Type_Def);
}

#endif // __SOCKET_OPT_DEF_H__
