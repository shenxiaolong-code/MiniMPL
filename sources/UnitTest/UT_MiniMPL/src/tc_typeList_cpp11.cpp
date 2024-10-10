#include "../testconfig_MiniMPL.h"
#include <MiniMPL/macro_init.h>
/***********************************************************************************************************************
* Description         : test file for </typeList_cpp11.hpp>
* Author              : Shen.Xiaolong (at 2024-09-23) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_TYPELIST_CPP11 to run this demo
***********************************************************************************************************************/
#define RUN_EXAMPLE_TYPELIST_CPP11

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_TYPELIST_CPP11
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_TYPELIST_CPP11
#endif

#if defined(RUN_EXAMPLE_TYPELIST_CPP11) && !defined(COMPILE_EXAMPLE_TYPELIST_CPP11)
    #define COMPILE_EXAMPLE_TYPELIST_CPP11
#endif

//#undef RUN_EXAMPLE_TYPELIST_CPP11
//#undef COMPILE_EXAMPLE_TYPELIST_CPP11

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_TYPELIST_CPP11
#include <MiniMPL/typeList_cpp11.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <UnitTestKit/tc_tracer.h>

namespace UnitTest
{

    using namespace MiniMPL;
    struct  S4;

    using tc_typeList=MiniMPL::TypeList<int,char,std::string,char*>;
    template <typename ... Args>    struct TypeList2;
    template <typename ... Args>    struct TypeList3;

    inline void TestCase_typeList_cpp11()
    {
        PrintTestcase();
        using namespace MiniMPL;

        //test GetTypeListLength
        Static_Assert((GetTypeListLength<tc_typeList>::value == 4));
        Static_Assert((GetTypeListLength<MiniMPL::TypeList <int,       std::string,  char*> >::value == 3));
        Static_Assert((GetTypeListLength<MiniMPL::TypeList <int, char, std::string>         >::value == 3));
        Static_Assert((GetTypeListLength<MiniMPL::TypeList <int, char,               char*> >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList2<int,       std::string,  char*> >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList2<int, char, std::string>         >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList2<int, char,               char*> >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList3<int,       std::string,  char*> >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList3<int, char, std::string>         >::value == 3));
        Static_Assert((GetTypeListLength<         TypeList3<int, char,               char*> >::value == 3));
        
#if CPP17_ENABLED
        Static_Assert((GetTypeListLength_v<tc_typeList> == 4));
#endif

        //test TypeIsInTypeList
        Static_Assert((TypeIsInTypeList<int,            tc_typeList>::value));
        Static_Assert((TypeIsInTypeList<char,           tc_typeList>::value));
        Static_Assert((TypeIsInTypeList<std::string,    tc_typeList>::value));
        Static_Assert((TypeIsInTypeList<char*,          tc_typeList>::value));
        Static_Assert(!(TypeIsInTypeList<float,         tc_typeList>::value));
        Static_Assert(!(TypeIsInTypeList<double,        tc_typeList>::value));

        //test GetTypeFirstIndexInTypeList
        Static_Assert((GetTypeFirstIndexInTypeList<int,         tc_typeList>::value == 0));
        Static_Assert((GetTypeFirstIndexInTypeList<char,        tc_typeList>::value == 1));
        Static_Assert((GetTypeFirstIndexInTypeList<std::string, tc_typeList>::value == 2));
        Static_Assert((GetTypeFirstIndexInTypeList<char*,       tc_typeList>::value == 3));
        Static_Assert((GetTypeFirstIndexInTypeList<float,       tc_typeList>::value == -1));
        Static_Assert((GetTypeFirstIndexInTypeList<double,      tc_typeList>::value == -1));

        //test GetNthTypeInTypeList
        Static_Assert((IsSameType<GetNthTypeInTypeList_t< 0, tc_typeList>,int>::value));
        Static_Assert((IsSameType<GetNthTypeInTypeList_t< 1, tc_typeList>,char>::value));
        Static_Assert((IsSameType<GetNthTypeInTypeList_t< 2, tc_typeList>,std::string>::value));
        Static_Assert((IsSameType<GetNthTypeInTypeList_t< 3, tc_typeList>,char*>::value));
        Static_Assert(!(IsSameType<GetNthTypeInTypeList_t<0, tc_typeList>,char>::value));

        //test ReplaceWrapperTemplate
        Static_Assert((IsSameType<ReplaceWrapperTemplate_t<tc_typeList,TypeList2>,TypeList2<int,char,std::string,char*>>::value));
        Static_Assert((IsSameType<ReplaceWrapperTemplate_t<tc_typeList,TypeList3>,TypeList3<int,char,std::string,char*>>::value));

        //test ReplaceNthTypeInTypeList
        Static_Assert((IsSameType<ReplaceNthTypeInTypeList_t<0, S4, tc_typeList>,TypeList<S4  , char ,std::string, char* >>::value));
        Static_Assert((IsSameType<ReplaceNthTypeInTypeList_t<1, S4, tc_typeList>,TypeList<int , S4   ,std::string, char* >>::value));
        Static_Assert((IsSameType<ReplaceNthTypeInTypeList_t<2, S4, tc_typeList>,TypeList<int , char ,S4         , char* >>::value));
        Static_Assert((IsSameType<ReplaceNthTypeInTypeList_t<3, S4, tc_typeList>,TypeList<int , char ,std::string, S4    >>::value));
        Static_Assert((GetTypeListLength<ReplaceNthTypeInTypeList_t<0, S4, tc_typeList>>::value == 4));
        Static_Assert((GetTypeListLength<ReplaceNthTypeInTypeList_t<1, S4, tc_typeList>>::value == 4));
        Static_Assert((GetTypeListLength<ReplaceNthTypeInTypeList_t<2, S4, tc_typeList>>::value == 4));
        Static_Assert((GetTypeListLength<ReplaceNthTypeInTypeList_t<3, S4, tc_typeList>>::value == 4));


        //test DeleteNthTypeInTypeList
        Static_Assert((IsSameType<DeleteNthTypeInTypeList_t<0, tc_typeList>,TypeList<    char,std::string, char*>>::value));
        Static_Assert((IsSameType<DeleteNthTypeInTypeList_t<1, tc_typeList>,TypeList<int,     std::string, char*>>::value));
        Static_Assert((IsSameType<DeleteNthTypeInTypeList_t<2, tc_typeList>,TypeList<int,char,             char*>>::value));
        Static_Assert((IsSameType<DeleteNthTypeInTypeList_t<3, tc_typeList>,TypeList<int,char,std::string       >>::value));
        Static_Assert((GetTypeListLength<DeleteNthTypeInTypeList_t<0, tc_typeList>>::value == 3));
        Static_Assert((GetTypeListLength<DeleteNthTypeInTypeList_t<1, tc_typeList>>::value == 3));
        Static_Assert((GetTypeListLength<DeleteNthTypeInTypeList_t<2, tc_typeList>>::value == 3));
        Static_Assert((GetTypeListLength<DeleteNthTypeInTypeList_t<3, tc_typeList>>::value == 3));

        //test InsertTypeInTypeList
        Static_Assert((IsSameType<InsertTypeInTypeList_t<0, S4, tc_typeList>,TypeList<S4  , int , char,         std::string, char* >>::value));
        Static_Assert((IsSameType<InsertTypeInTypeList_t<1, S4, tc_typeList>,TypeList<int , S4  , char,         std::string, char* >>::value));
        Static_Assert((IsSameType<InsertTypeInTypeList_t<2, S4, tc_typeList>,TypeList<int , char, S4  ,         std::string, char* >>::value));
        Static_Assert((IsSameType<InsertTypeInTypeList_t<3, S4, tc_typeList>,TypeList<int , char, std::string,  S4         , char* >>::value));
        Static_Assert((IsSameType<InsertTypeInTypeList_t<4, S4, tc_typeList>,TypeList<int , char, std::string,  char*      , S4    >>::value));
        Static_Assert((GetTypeListLength<InsertTypeInTypeList_t<0, S4, tc_typeList>>::value == 5));
        Static_Assert((GetTypeListLength<InsertTypeInTypeList_t<1, S4, tc_typeList>>::value == 5));
        Static_Assert((GetTypeListLength<InsertTypeInTypeList_t<2, S4, tc_typeList>>::value == 5));
        Static_Assert((GetTypeListLength<InsertTypeInTypeList_t<3, S4, tc_typeList>>::value == 5));

        //test AppendTypeInTypeList
        Static_Assert((IsSameType<AppendTypeInTypeList_t<S4, tc_typeList>,   TypeList<int , char, std::string,  char*      , S4    >>::value));
        Static_Assert((GetTypeListLength<AppendTypeInTypeList_t<S4, tc_typeList>>::value == 5));

   }

#ifdef RUN_EXAMPLE_TYPELIST_CPP11
    InitRunFunc(TestCase_typeList_cpp11);
#else //else of RUN_EXAMPLE_TYPELIST_CPP11

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_TYPELIST_CPP11)=(outputTxtV(TXT("[Unit test run disabled] typeList_cpp11.hpp\n%s(%d)\n") TXT(__FILE__) MAKESTR(__LINE__)),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"typeList_cpp11.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_TYPELIST_CPP11
}

#else //else of COMPILE_EXAMPLE_TYPELIST_CPP11
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_TYPELIST_CPP11)=(outputTxtV(TXT("[Unit test compile disabled] typeList_cpp11.hpp\n%s(%d)\n") TXT(__FILE__) MAKESTR(__LINE__)),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"typeList_cpp11.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_TYPELIST_CPP11

