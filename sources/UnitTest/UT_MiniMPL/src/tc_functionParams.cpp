#include "../testconfig_MiniMPL.h"
/***********************************************************************************************************************
* Description         : test file for <MiniMPL\functionParams.hpp>
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
* usage demo          : #define RUN_EXAMPLE_FUNCTIONPARAMS to run this demo
***********************************************************************************************************************/
//#define RUN_EXAMPLE_FUNCTIONPARAMS

#ifdef COMPILE_EXAMPLE_ALL
    #define COMPILE_EXAMPLE_FUNCTIONPARAMS
#endif

#ifdef RUN_EXAMPLE_ALL
    #define RUN_EXAMPLE_FUNCTIONPARAMS
#endif

#if defined(RUN_EXAMPLE_FUNCTIONPARAMS) && !defined(COMPILE_EXAMPLE_FUNCTIONPARAMS)
    #define COMPILE_EXAMPLE_FUNCTIONPARAMS
#endif

//#undef RUN_EXAMPLE_FUNCTIONPARAMS
//#undef COMPILE_EXAMPLE_FUNCTIONPARAMS

////////////////////////////////////////////usage & test demo code//////////////////////////////////////////////////////////
#ifdef COMPILE_EXAMPLE_FUNCTIONPARAMS
#include <MiniMPL/functionParams.hpp>
#include <UnitTestKit/tc_tracer.h>
#include <MiniMPL/isXXXEx.hpp>
#include <UT_material/tc_def_typeStruct.h>
#include <UnitTestKit/tc_dump.h>
#include <MiniMPL/addRemove.hpp>

namespace UnitTest
{
    struct FuncTraitStruct
    {
        static void staticFunc(int a, char b)
        {
            outputTxtV(TXT("%s\n"),HEREINFO());
        }

        bool nonStaticFunc(char b)
        {
            outputTxtV(TXT("%s\n"),HEREINFO());
            return true;
        }
        bool nonStaticFunc_const(char b) const
        {
            outputTxtV(TXT("%s\n"),HEREINFO());
            return true;
        }
    };

    template<typename TF>
    void testFunctionTraint_StaticMember(TF f)
    {
        //test IsMemberFunctionPointer and IsFunctionPointer
        Static_Assert(!MiniMPL::IsMemberFunctionPointer<TF>::value);  //static member function is treated as non member function 
        Static_Assert(MiniMPL::IsFunctionPointer<TF>::value);
    }

    template<typename TF>
    void testFunctionTraint_NonStaticMember(TF f)
    {
        //test IsMemberFunctionPointer and IsFunctionPointer
        Static_Assert(MiniMPL::IsMemberFunctionPointer<TF>::value);
        Static_Assert(!MiniMPL::IsFunctionPointer<TF>::value);       //member function is not treated global function
    }

    void testTParamArray()
    {
        using namespace MiniMPL;
        //test full ParamPackage : max 6 elements
        typedef ParamPackage<>                                                   TTParamArray0P;
        typedef ParamPackage<int>                                                TTParamArray1P;
        typedef ParamPackage<int,char>                                           TTParamArray2P;
        typedef ParamPackage<int,char,int>                                       TTParamArray3P;
        typedef ParamPackage<int,char,int,stlString>                             TTParamArray4P;
        typedef ParamPackage<int,char,int,stlString,int>                         TTParamArray5P;
        typedef ParamPackage<int,char,int,stlString,int,int>                     TTParamArray6P;
        typedef ParamPackage<int,char,int,stlString,int,int,int>                 TTParamArray7P;
        Static_Assert((ParamPackageSize<TTParamArray0P>::value==0));
        Static_Assert((ParamPackageSize<TTParamArray1P>::value==1));
        Static_Assert((ParamPackageSize<TTParamArray2P>::value==2));
        Static_Assert((ParamPackageSize<TTParamArray3P>::value==3));
        Static_Assert((ParamPackageSize<TTParamArray4P>::value==4));
        Static_Assert((ParamPackageSize<TTParamArray5P>::value==5));
        Static_Assert((ParamPackageSize<TTParamArray6P>::value==6));
        Static_Assert((ParamPackageSize<TTParamArray7P>::value==7));

        //test TParamArrayAt
        Static_Assert((IsSameRawType<typename ParamPackageAt<TTParamArray6P,2>::type,char>::value));
        Static_Assert((IsSameRawType<typename ParamPackageAt<TTParamArray6P,1>::type,int>::value));
        Static_Assert((!IsSameRawType<typename ParamPackageAt<TTParamArray6P,2>::type,int>::value));
        Static_Assert((!IsSameRawType<typename ParamPackageAt<TTParamArray6P,1>::type,char>::value));
    }

    void testFunctionTraint_mf_nonConst()
    {
        using namespace MiniMPL;
        //test member function
        typedef void (S4::*O_RV_P0)();
        typedef FunctionParams<O_RV_P0>      O_RV_P0_T;
        Static_Assert((0==GetFunctionParamNum<O_RV_P0>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RV_P0_T>::type,O_RV_P0>::value));  //test GetFunction
        Static_Assert((IsSameType<S4,O_RV_P0_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4&,O_RV_P0_T::Object_T>::value));
        Static_Assert((IsSameType<void,O_RV_P0_T::Return_T>::value));
        Static_Assert(0==ParamPackageSize<typename O_RV_P0_T::Params_T>::value);                              //test parameter number

        typedef void (S4::*O_RV_P2)(char*,S4&);
        typedef FunctionParams<O_RV_P2>      O_RV_P2_T;
        Static_Assert((2==GetFunctionParamNum<O_RV_P2>::value));
        Static_Assert((IsSameType<void,O_RV_P2_T::Return_T>::value));
        Static_Assert((IsSameType<S4,O_RV_P2_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4*,O_RV_P2_T::Object_T>::value));
        Static_Assert((IsSameType<char*,typename ParamPackageAt<O_RV_P2_T::Params_T,1>::type>::value));
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<O_RV_P2_T::Params_T,1>::type>::value));
        Static_Assert((IsSameType<S4&,typename GetFunctionParam<O_RV_P2,2>::type>::value));
        Static_Assert((IsSameType<S4&,typename ParamPackageAt<O_RV_P2_T::Params_T,2>::type>::value));
        Static_Assert(!(IsSameType<S4,typename ParamPackageAt<O_RV_P2_T::Params_T,2>::type>::value));
        Static_Assert(2==ParamPackageSize<typename O_RV_P2_T::Params_T>::value);                              //test parameter number

        typedef int (S4::*O_RI_P0)();
        typedef FunctionParams<O_RI_P0>      O_RI_P0_T;
        Static_Assert((0==GetFunctionParamNum<O_RI_P0>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RI_P0_T>::type,O_RI_P0>::value));  //test GetFunction
        Static_Assert((IsSameType<int,O_RI_P0_T::Return_T>::value));
        Static_Assert((IsSameType<S4,O_RI_P0_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4 const,O_RI_P0_T::Object_T>::value));       //test parameter number
        Static_Assert(0==ParamPackageSize<typename O_RI_P0_T::Params_T>::value); 

        typedef int (S4::*O_RI_P1)(char);
        typedef FunctionParams<O_RI_P1>      O_RI_P1_T;
        Static_Assert((1==GetFunctionParamNum<O_RI_P1>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RI_P1_T>::type,O_RI_P1>::value));  //test GetFunction
        Static_Assert((IsSameType<int,O_RI_P1_T::Return_T>::value));
        Static_Assert(!(IsSameType<char,O_RI_P1_T::Return_T>::value));
        Static_Assert((IsSameType<S4,O_RI_P1_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4*,O_RI_P1_T::Object_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<O_RI_P1_T::Params_T,1>::type>::value));          //test 1st parameter
        Static_Assert(1==ParamPackageSize<typename O_RI_P1_T::Params_T>::value);                           //test parameter number

        typedef S4 (S4::*O_RS_P5)(char,int,int*,char&,float const&);
        typedef FunctionParams<O_RS_P5>      O_RS_P5_T;
        Static_Assert((5==GetFunctionParamNum<O_RS_P5>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RS_P5_T>::type,O_RS_P5>::value));  //test GetFunction
        Static_Assert((IsSameType<S4,O_RS_P5_T::Return_T>::value));  //test Return type
        Static_Assert(!(IsSameType<char,O_RS_P5_T::Return_T>::value));
        Static_Assert((IsSameType<S4,O_RS_P5_T::Object_T>::value));  //test Object type
        Static_Assert(!(IsSameType<S4&,O_RS_P5_T::Object_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<O_RS_P5_T::Params_T,1>::type>::value));               //test 1st parameter
        Static_Assert(!(IsSameType<char&,typename ParamPackageAt<O_RS_P5_T::Params_T,1>::type>::value));
        Static_Assert((IsSameType<int,typename GetFunctionParam<O_RS_P5,2>::type>::value));
        Static_Assert((IsSameType<int,typename ParamPackageAt<O_RS_P5_T::Params_T,2>::type>::value));                //test 2nd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<O_RS_P5_T::Params_T,2>::type>::value));
        Static_Assert((IsSameType<int*,typename ParamPackageAt<O_RS_P5_T::Params_T,3>::type>::value));               //test 3rd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<O_RS_P5_T::Params_T,3>::type>::value));     
        Static_Assert((IsSameType<char&,typename ParamPackageAt<O_RS_P5_T::Params_T,4>::type>::value));              //test 4th parameter
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<O_RS_P5_T::Params_T,4>::type>::value));
        Static_Assert((IsSameType<float const&,typename ParamPackageAt<O_RS_P5_T::Params_T,5>::type>::value));       //test 5th parameter
        Static_Assert(!(IsSameType<float const*,typename ParamPackageAt<O_RS_P5_T::Params_T,5>::type>::value));
        Static_Assert(!(IsSameType<void,typename GetFunctionParam<O_RS_P5,1>::type>::value));            //test 1st param
        Static_Assert((IsSameType<char,typename GetFunctionParam<O_RS_P5,1>::type>::value));             //test 1st param
        Static_Assert((IsSameType<int,typename GetFunctionParam<O_RS_P5,2>::type>::value));              //test 2st param
        Static_Assert((IsSameType<int*,typename GetFunctionParam<O_RS_P5,3>::type>::value));             //test 3rd param
        Static_Assert((IsSameType<char&,typename GetFunctionParam<O_RS_P5,4>::type>::value));            //test 4th param
        Static_Assert((IsSameType<float const&,typename GetFunctionParam<O_RS_P5,5>::type>::value));     //test 5th param
        Static_Assert(!(IsSameType<float const,typename GetFunctionParam<O_RS_P5,5>::type>::value));     //test 5th param

        Static_Assert(5==ParamPackageSize<typename O_RS_P5_T::Params_T>::value);  
    }

    void testFunctionTraint_mf_const()
    {
        using namespace MiniMPL;
        //test IsConstMemberFunctionPointer
        Static_Assert(!(MiniMPL::IsConstMemberFunctionPointer<int (S4::*)(char,bool)>::value));
        Static_Assert((MiniMPL::IsConstMemberFunctionPointer<int (S4::*)(char,bool) const>::value));

        //test member function
        typedef void (S4::*O_RV_P0)() const;
        typedef FunctionParams<O_RV_P0>      O_RV_P0_T;
        Static_Assert((0==GetFunctionParamNum<O_RV_P0>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RV_P0_T>::type,O_RV_P0>::value));  //test GetFunction
        Static_Assert((IsSameType<S4 const,O_RV_P0_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4,O_RV_P0_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4&,O_RV_P0_T::Object_T>::value));
        Static_Assert((IsSameType<void,O_RV_P0_T::Return_T>::value));
        Static_Assert(0==ParamPackageSize<typename O_RV_P0_T::Params_T>::value);                              //test parameter number

        typedef void (S4::*O_RV_P2)(char*,S4&) const;
        typedef FunctionParams<O_RV_P2>      O_RV_P2_T;
        Static_Assert((2==GetFunctionParamNum<O_RV_P2>::value));
        Static_Assert((IsSameType<void,O_RV_P2_T::Return_T>::value));
        Static_Assert((IsSameType<S4 const,O_RV_P2_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4,O_RV_P2_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4*,O_RV_P2_T::Object_T>::value));
        Static_Assert((IsSameType<char*,typename ParamPackageAt<O_RV_P2_T::Params_T,1>::type>::value));
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<O_RV_P2_T::Params_T,1>::type>::value));
        Static_Assert((IsSameType<S4&,typename GetFunctionParam<O_RV_P2,2>::type>::value));
        Static_Assert((IsSameType<S4&,typename ParamPackageAt<O_RV_P2_T::Params_T,2>::type>::value));
        Static_Assert(!(IsSameType<S4,typename ParamPackageAt<O_RV_P2_T::Params_T,2>::type>::value));
        Static_Assert(2==ParamPackageSize<typename O_RV_P2_T::Params_T>::value);                              //test parameter number

        typedef int (S4::*O_RI_P0)() const;
        typedef FunctionParams<O_RI_P0>      O_RI_P0_T;
        Static_Assert((0==GetFunctionParamNum<O_RI_P0>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RI_P0_T>::type,O_RI_P0>::value));  //test GetFunction
        Static_Assert((IsSameType<int,O_RI_P0_T::Return_T>::value));
        Static_Assert((IsSameType<S4 const,O_RI_P0_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4,O_RI_P0_T::Object_T>::value));       //test parameter number
        Static_Assert(0==ParamPackageSize<typename O_RI_P0_T::Params_T>::value); 

        typedef int (S4::*O_RI_P1)(char) const;
        typedef FunctionParams<O_RI_P1>      O_RI_P1_T;
        Static_Assert((1==GetFunctionParamNum<O_RI_P1>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RI_P1_T>::type,O_RI_P1>::value));  //test GetFunction
        Static_Assert((IsSameType<int,O_RI_P1_T::Return_T>::value));
        Static_Assert(!(IsSameType<char,O_RI_P1_T::Return_T>::value));
        Static_Assert((IsSameType<S4 const,O_RI_P1_T::Object_T>::value));
        Static_Assert(!(IsSameType<S4*,O_RI_P1_T::Object_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<O_RI_P1_T::Params_T,1>::type>::value));          //test 1st parameter
        Static_Assert(1==ParamPackageSize<typename O_RI_P1_T::Params_T>::value);                           //test parameter number

        typedef S4 (S4::*O_RS_P5)(char,int,int*,char&,float const&) const;
        typedef FunctionParams<O_RS_P5>      O_RS_P5_T;
        Static_Assert((5==GetFunctionParamNum<O_RS_P5>::value));
        Static_Assert((IsSameType<typename GetFunction<O_RS_P5_T>::type,O_RS_P5>::value));  //test GetFunction
        Static_Assert((IsSameType<S4,O_RS_P5_T::Return_T>::value));  //test Return type
        Static_Assert(!(IsSameType<char,O_RS_P5_T::Return_T>::value));
        Static_Assert((IsSameType<S4 const,O_RS_P5_T::Object_T>::value));  //test Object type
        Static_Assert(!(IsSameType<S4,O_RS_P5_T::Object_T>::value));  //test Object type
        Static_Assert(!(IsSameType<S4&,O_RS_P5_T::Object_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<O_RS_P5_T::Params_T,1>::type>::value));               //test 1st parameter
        Static_Assert(!(IsSameType<char&,typename ParamPackageAt<O_RS_P5_T::Params_T,1>::type>::value));
        Static_Assert((IsSameType<int,typename GetFunctionParam<O_RS_P5,2>::type>::value));
        Static_Assert((IsSameType<int,typename ParamPackageAt<O_RS_P5_T::Params_T,2>::type>::value));                //test 2nd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<O_RS_P5_T::Params_T,2>::type>::value));
        Static_Assert((IsSameType<int*,typename ParamPackageAt<O_RS_P5_T::Params_T,3>::type>::value));               //test 3rd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<O_RS_P5_T::Params_T,3>::type>::value));     
        Static_Assert((IsSameType<char&,typename ParamPackageAt<O_RS_P5_T::Params_T,4>::type>::value));              //test 4th parameter
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<O_RS_P5_T::Params_T,4>::type>::value));
        Static_Assert((IsSameType<float const&,typename ParamPackageAt<O_RS_P5_T::Params_T,5>::type>::value));       //test 5th parameter
        Static_Assert(!(IsSameType<float const*,typename ParamPackageAt<O_RS_P5_T::Params_T,5>::type>::value));
        Static_Assert(!(IsSameType<void,typename GetFunctionParam<O_RS_P5,1>::type>::value));            //test 1st param
        Static_Assert((IsSameType<char,typename GetFunctionParam<O_RS_P5,1>::type>::value));             //test 1st param
        Static_Assert((IsSameType<int,typename GetFunctionParam<O_RS_P5,2>::type>::value));              //test 2st param
        Static_Assert((IsSameType<int*,typename GetFunctionParam<O_RS_P5,3>::type>::value));             //test 3rd param
        Static_Assert((IsSameType<char&,typename GetFunctionParam<O_RS_P5,4>::type>::value));            //test 4th param
        Static_Assert((IsSameType<float const&,typename GetFunctionParam<O_RS_P5,5>::type>::value));     //test 5th param
        Static_Assert(!(IsSameType<float const,typename GetFunctionParam<O_RS_P5,5>::type>::value));     //test 5th param

        Static_Assert(5==ParamPackageSize<typename O_RS_P5_T::Params_T>::value);  
    }

    void testFunctionTraint_global()
    {
        using namespace MiniMPL;
        //test non-member function
        typedef void (*RV_P0)();
        typedef FunctionParams<RV_P0>      RV_P0_T;
        Static_Assert((IsSameType<void,RV_P0_T::Return_T>::value));        //test Return type
        Static_Assert(0==ParamPackageSize<typename RV_P0_T::Params_T>::value);                               //test parameter number

        typedef void (*RV_P3)(char*,S4&,char const);
        typedef FunctionParams<RV_P3>      RV_P3_T;
        Static_Assert((3==GetFunctionParamNum<RV_P3>::value));
        Static_Assert((IsSameType<typename GetFunction<RV_P3_T>::type,RV_P3>::value));  //test GetFunction
        Static_Assert((IsSameType<void,RV_P3_T::Return_T>::value));        //test Return type
        Static_Assert((IsSameType<char*,typename ParamPackageAt<RV_P3_T::Params_T,1>::type>::value));             //test 1st parameter
        Static_Assert(!(IsSameType<char,typename GetFunctionParam<RV_P3,1>::type>::value));
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<RV_P3_T::Params_T,1>::type>::value));
        //Static_Assert((IsSameType<char const,typename ParamPackageAt<RV_P3_T::Params_T,3>::type>::value));     //VS2008 Compiler Bug : it can't reconginze param type : T const which is not first param
        Static_Assert((IsSameType<char,typename ParamPackageAt<RV_P3_T::Params_T,3>::type>::value));             //VS2008 Compiler Bug : it can't reconginze type : R (*)(T1,T2 const)
        Static_Assert(!(IsSameType<char&,typename ParamPackageAt<RV_P3_T::Params_T,3>::type>::value));
        Static_Assert(!(IsSameType<char const&,typename ParamPackageAt<RV_P3_T::Params_T,3>::type>::value));
        Static_Assert((IsSameType<S4&,typename ParamPackageAt<RV_P3_T::Params_T,2>::type>::value));
        Static_Assert(!(IsSameType<S4,typename ParamPackageAt<RV_P3_T::Params_T,2>::type>::value));
        Static_Assert(!(IsSameType<void,typename GetFunctionParam<RV_P3,1>::type>::value));     //test 1st param
        Static_Assert((IsSameType<char*,typename GetFunctionParam<RV_P3,1>::type>::value));     //test 1st param
        Static_Assert((IsSameType<S4&,typename GetFunctionParam<RV_P3,2>::type>::value));       //test 2st param
        Static_Assert(3==ParamPackageSize<typename RV_P3_T::Params_T>::value);                              //test parameter number

        typedef int (*RI_P0)();
        typedef FunctionParams<RI_P0>      RI_P0_T;
        Static_Assert((0==GetFunctionParamNum<RI_P0>::value));
        Static_Assert((IsSameType<int,RI_P0_T::Return_T>::value));        //test Return type
        Static_Assert(0==ParamPackageSize<typename RI_P0_T::Params_T>::value);                              //test parameter number

        typedef int (*RI_P1)(char);
        typedef FunctionParams<RI_P1>      RI_P1_T;
        Static_Assert((1==GetFunctionParamNum<RI_P1>::value));
        Static_Assert((IsSameType<int,RI_P1_T::Return_T>::value));        //test Return type
        Static_Assert((IsSameType<char,typename GetFunctionParam<RI_P1,1>::type>::value));
        Static_Assert(!(IsSameType<char,RI_P1_T::Return_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<RI_P1_T::Params_T,1>::type>::value));             //test 1st parameter
        Static_Assert(1==ParamPackageSize<typename RI_P1_T::Params_T>::value);                              //test parameter number

        typedef S4 (*RS_P5)(char,int,int*,char&,float const&);
        typedef FunctionParams<RS_P5>      RS_P5_T;
        Static_Assert((5==GetFunctionParamNum<RS_P5>::value));
        Static_Assert((IsSameType<typename GetFunction<RS_P5_T>::type,RS_P5>::value));  //test GetFunction
        Static_Assert((IsSameType<S4,RS_P5_T::Return_T>::value));  //test Return type
        Static_Assert(!(IsSameType<char,RS_P5_T::Return_T>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<RS_P5_T::Params_T,1>::type>::value));               //test 1st parameter
        Static_Assert(!(IsSameType<char&,typename ParamPackageAt<RS_P5_T::Params_T,1>::type>::value));
        Static_Assert((IsSameType<char,typename GetFunctionParam<RS_P5,1>::type>::value));
        Static_Assert((IsSameType<int,typename ParamPackageAt<RS_P5_T::Params_T,2>::type>::value));                //test 2nd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<RS_P5_T::Params_T,2>::type>::value));
        Static_Assert((IsSameType<int*,typename ParamPackageAt<RS_P5_T::Params_T,3>::type>::value));               //test 3rd parameter
        Static_Assert(!(IsSameType<int&,typename ParamPackageAt<RS_P5_T::Params_T,3>::type>::value));     
        Static_Assert((IsSameType<char&,typename ParamPackageAt<RS_P5_T::Params_T,4>::type>::value));              //test 4th parameter
        Static_Assert(!(IsSameType<char,typename ParamPackageAt<RS_P5_T::Params_T,4>::type>::value));
        Static_Assert((IsSameType<float const&,typename ParamPackageAt<RS_P5_T::Params_T,5>::type>::value));       //test 5th parameter
        Static_Assert(!(IsSameType<float const*,typename ParamPackageAt<RS_P5_T::Params_T,5>::type>::value));
        Static_Assert(!(IsSameType<void,typename GetFunctionParam<RS_P5,1>::type>::value));            //test 1st param
        Static_Assert((IsSameType<char,typename GetFunctionParam<RS_P5,1>::type>::value));             //test 1st param
        Static_Assert((IsSameType<int,typename GetFunctionParam<RS_P5,2>::type>::value));              //test 2st param
        Static_Assert((IsSameType<int*,typename GetFunctionParam<RS_P5,3>::type>::value));             //test 3rd param
        Static_Assert((IsSameType<char&,typename GetFunctionParam<RS_P5,4>::type>::value));            //test 4th param
        Static_Assert((IsSameType<float const&,typename GetFunctionParam<RS_P5,5>::type>::value));     //test 5th param
        Static_Assert(!(IsSameType<float const,typename GetFunctionParam<RS_P5,5>::type>::value));     //test 5th param
        Static_Assert(5==ParamPackageSize<typename RS_P5_T::Params_T>::value);                                //test parameter number
    }

    inline void TestCase_functionParams_add()
    {
        PrintTestcase();

        using namespace MiniMPL;
        typedef void (*pFvcis)(char,int&,S4);
        typedef pFvcis      TFvcis;
        typedef TAddTClassToPack<TFvcis>::type      TFPackvcis;
        typedef TAddTFToPack<TFvcis>::type          TFPackAllvcis;
        Static_Assert((3==ParamPackageSize<TFPackvcis>::value));
        Static_Assert((4==ParamPackageSize<TFPackAllvcis>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<TFPackvcis,1>::type>::value));
        Static_Assert((IsSameType<int&,typename ParamPackageAt<TFPackvcis,2>::type>::value));
        Static_Assert((IsSameType<S4,typename ParamPackageAt<TFPackvcis,3>::type>::value));
        Static_Assert((IsSameType<TFvcis,typename ParamPackageAt<TFPackAllvcis,1>::type>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<TFPackAllvcis,2>::type>::value));
        Static_Assert((IsSameType<int&,typename ParamPackageAt<TFPackAllvcis,3>::type>::value));
        Static_Assert((IsSameType<S4,typename ParamPackageAt<TFPackAllvcis,4>::type>::value));

        typedef int (S4::*pFiocis)(char,int&,S4);
        typedef pFiocis      TFiocis;
        typedef TAddTFToPack<TFiocis>::type    TFPackiocis;
        Static_Assert((4==ParamPackageSize<typedef TAddTClassToPack<TFiocis>::type>::value));
        Static_Assert((5==ParamPackageSize<TFPackiocis>::value));
        Static_Assert((IsSameType<TFiocis,typename ParamPackageAt<TFPackiocis,1>::type>::value));
        Static_Assert((IsSameType<S4&,typename ParamPackageAt<TFPackiocis,2>::type>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<TFPackiocis,3>::type>::value));
        Static_Assert((IsSameType<int&,typename ParamPackageAt<TFPackiocis,4>::type>::value));
        Static_Assert((IsSameType<S4,typename ParamPackageAt<TFPackiocis,5>::type>::value));

        typedef int (S4::*pFiocisConst)(char,int&,S4) const;
        typedef pFiocisConst      TFiocisConst;
        typedef TAddTFToPack<TFiocisConst>::type    TFConstPackiocis;
        Static_Assert((4==ParamPackageSize<typedef TAddTClassToPack<TFiocisConst>::type>::value));
        Static_Assert((5==ParamPackageSize<TFConstPackiocis>::value));
        Static_Assert((IsSameType<TFiocisConst,typename ParamPackageAt<TFConstPackiocis,1>::type>::value));
        Static_Assert((IsSameType<S4 const&,typename ParamPackageAt<TFConstPackiocis,2>::type>::value));
        Static_Assert(!(IsSameType<S4&,typename ParamPackageAt<TFConstPackiocis,2>::type>::value));
        Static_Assert((IsSameType<char,typename ParamPackageAt<TFConstPackiocis,3>::type>::value));
        Static_Assert((IsSameType<int&,typename ParamPackageAt<TFConstPackiocis,4>::type>::value));
        Static_Assert((IsSameType<S4,typename ParamPackageAt<TFConstPackiocis,5>::type>::value));
    }

    inline void TestCase_functionParams()
    {
        PrintTestcase();
        testTParamArray();
        testFunctionTraint_global();
        testFunctionTraint_mf_nonConst();
        testFunctionTraint_mf_const();
        TestCase_functionParams_add();

        //test parameter number
        testFunctionTraint_StaticMember(&FuncTraitStruct::staticFunc);
        testFunctionTraint_NonStaticMember(&FuncTraitStruct::nonStaticFunc);
        testFunctionTraint_NonStaticMember(&FuncTraitStruct::nonStaticFunc_const);
    }

#ifdef RUN_EXAMPLE_FUNCTIONPARAMS
    InitRunFunc(TestCase_functionParams);
#else //else of RUN_EXAMPLE_FUNCTIONPARAMS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if defined(RUN_WARNING_NO_TESTCASE_RUN)
    GLOBALVAR(RUN_FUNCTIONPARAMS)=(outputTxtV(TXT("[Unit test run disabled] functionParams.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_RUN)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is runing for \"functionParams.hpp\".")
    #endif
#endif  	// RUN_EXAMPLE_FUNCTIONPARAMS
}

#else //else of COMPILE_EXAMPLE_FUNCTIONPARAMS
    #if defined(RUN_WARNING_NO_TESTCASE_COMPILE)
    GLOBALVAR(COMPILE_FUNCTIONPARAMS)=(outputTxtV(TXT("[Unit test compile disabled] functionParams.hpp\n%s(%d)\n"),TXT(__FILE__),__LINE__),1);
    #endif

    #if defined(BUILD_WARNING_NO_TESTCASE_COMPILE)
    #pragma message (__FILE__ "(" MAKESTRA(__LINE__) "):No test code is compiled for \"functionParams.hpp\".")
    #endif
#endif // COMPILE_EXAMPLE_FUNCTIONPARAMS

