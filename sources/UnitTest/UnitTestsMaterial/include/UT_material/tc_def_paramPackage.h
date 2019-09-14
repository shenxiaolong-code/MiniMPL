#ifndef TC_DEF_PARAMPACKAGE_H__
#define TC_DEF_PARAMPACKAGE_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/

#include <MiniMPL/paramPack.hpp>
#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/paramPackageCall.hpp>

namespace UnitTest
{
    typedef MiniMPL::ParamPackage<>                                      ParamPackage0_T;  
    typedef MiniMPL::ParamPackage<int>                                   ParamPackage1_T;  
    typedef MiniMPL::ParamPackage<int,char>                              ParamPackage2_T;  
    typedef MiniMPL::ParamPackage<int,char,void>                         ParamPackage3_T;  
    typedef MiniMPL::ParamPackage<int,char,void,void*>                   ParamPackage4_T;
    typedef MiniMPL::ParamPackage<int,char,void,void*,float>             ParamPackage5_T;
    typedef MiniMPL::ParamPackage<int,char,void,void*,float,double>      ParamPackage6_T;

    typedef MiniMPL::ParamPackageCall<>                                             TParamPackageCall0;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&>                                 TParamPackageCall1;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&,char>                            TParamPackageCall2;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&,char,char*>                      TParamPackageCall3;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&,char,char*,int>                  TParamPackageCall4;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&,char,char*,int,float>            TParamPackageCall5;
    typedef MiniMPL::ParamPackageCall<MFStruct0_6&,char,char*,int,float,void>       TParamPackageCall6;


    struct T0{int const m_t0;T0(int t0=0):m_t0(t0){};};
    struct T1{int const m_t1;T1(int t1=1):m_t1(t1){};};
    struct T2{int const m_t2;T2(int t2=2):m_t2(t2){};};
    struct T3{int const m_t3;T3(int t3=3):m_t3(t3){};};
    struct T4{int const m_t4;T4(int t4=4):m_t4(t4){};};
    struct T5{int const m_t5;T5(int t5=5):m_t5(t5){};};
    struct T6{int const m_t6;T6(int t6=6):m_t6(t6){};};
    typedef MiniMPL::ParamPackage<>                                      Params0_T;  
    typedef MiniMPL::ParamPackage<T1>                                    Params1_T;  
    typedef MiniMPL::ParamPackage<T1,T2>                                 Params2_T;  
    typedef MiniMPL::ParamPackage<T1,T2,T3>                              Params3_T;  
    typedef MiniMPL::ParamPackage<T1,T2,T3,T4>                           Params4_T;
    typedef MiniMPL::ParamPackage<T1,T2,T3,T4,T5>                        Params5_T;
    typedef MiniMPL::ParamPackage<T1,T2,T3,T4,T5,T6>                     Params6_T;
}

#endif // TC_DEF_PARAMPACKAGE_H__
