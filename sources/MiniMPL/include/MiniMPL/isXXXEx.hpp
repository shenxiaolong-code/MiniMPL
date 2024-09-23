#ifndef __ISXXXEX_HPP__
#define __ISXXXEX_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/isXXX.hpp>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/typeLogic.hpp>
#include <MiniMPL/InnerDetail/isXXXEx_detail.hpp>
#include <MiniMPL/InnerDetail/isFuncPointer_detail.hpp>
#include <MiniMPL/addRemove.hpp>

namespace MiniMPL
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T1, typename T2>  struct IsSameType           : public FalseType {}; 
    template<typename T>                struct IsSameType<T,T>      : public TrueType  {};
    template<typename T1, typename T2>  constexpr bool IsSameType_v = IsSameType<T1,T2>::value;
    
    template<typename T1, typename T2>  struct IsSameRawType        : public IsSameType<RAWTYPE(T1),RAWTYPE(T2)>{};
    template<typename T>                struct IsRawType            : public IsSameType<T,RAWTYPE(T)> {};

    template<typename FromT, typename ToT>  struct IsConvertable    : public ConvertTester<FromT,ToT>{}; //Note : int and int* is not convertable
    template<typename BaseT, typename DeriveT>  struct IsBaseDerive : public BaseDeriveTester<BaseT,DeriveT>{};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct IsSmartPointer                   : public IsSmartPointerImpl<RAWTYPE(T)>  {};
    template<typename T>    struct IsStlIterator                    : public HasType_iterator_category<T>{};
    template<typename T>    struct IsPointer                        : public Or_T<IsCPointer<T> , IsSmartPointer<T> , IsStlIterator<T> > {};

    template<typename T>    struct IsFunctionPointer        : public FunctionPointerTester<T>{};
    template<typename T>    struct IsMemberFunctionPointer  : public MemberFunctionPointerTester<T>{};
    template<typename T>    struct IsFunction               : public Or_T<FunctionPointerTester<T>,MemberFunctionPointerTester<T> >{};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct IsBuildInType    : public BoolType<BuildInTypeTester<RAWTYPE(T)>::isBuildin>{};
    template<typename T>    struct IsBuildInInteger : public BoolType<BuildInTypeTester<RAWTYPE(T)>::isInteger>{};
    template<typename T>    struct isBuildinFloat   : public BoolType<BuildInTypeTester<RAWTYPE(T)>::isFloat> {};

    template<typename T>    struct IsClassStruct    : public ClassStructTester<T>   {};
    template<typename T>    struct IsArray          : public ArrayTester<T>         {};
    template<typename T>    struct IsEnumType       : public And_T<BoolType<sizeof(enum EnumType)==sizeof(T)>
                                                    , Not_T<Or_T<IsClassStruct<T> , IsArray<T> , IsBuildInType<T> > > > {};

    template<typename T>    struct IsAtomType   : public AtomTester<T>{};
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    template<typename T>    struct IsStringStl  : public Or_T<IsSameRawType<T,stlStringA> ,IsSameRawType<T,stlStringW> >{};
    template<typename T>    struct IsStringC    : public Or_T<IsSameRawType<T,typename stlStringA::value_type*>,IsSameRawType<T,typename stlStringW::value_type*> >{};
    template<typename T,    bool b=IsArray<T>::value>   struct IsCharArray:public FalseType                 {};
    template<typename T>    struct IsCharArray<T,true> :public IsStringC<typename ArrayValueType<T>::type*> {};

    template<typename T>    struct IsString : public Or_T<IsStringStl<T>,IsStringC<T>,IsCharArray<T> >      {};
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct IsStlContainer   : public HasType_iterator<RAWTYPE(T)>{};    
}


#endif // __ISXXXEX_HPP__
