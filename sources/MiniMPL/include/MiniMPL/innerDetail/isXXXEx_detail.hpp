#ifndef ISXXX_DETAIL_H__
#define ISXXX_DETAIL_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	detail implement for isXXX.hpp
*************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/macro_makeVar.h>
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/hasXXX.hpp>
#include <MiniMPL/arrayTrait.hpp>

namespace MiniMPL
{      
    HasXXXType(iterator_category); 
    HasXXXType(iterator);

    template<typename T>    struct IsSmartPointerImpl                   : public FalseType{};
    template<typename T>    struct IsSmartPointerImpl<stlSmartptr<T> >  : public TrueType {};


#pragma warning( push )
#pragma warning( disable : 4800 )     //warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
    template<typename FromT,typename ToT>	struct ConvertTester
    {   
        static MiniMPL::No_Type			    test(...);
        static MiniMPL::Yes_Type	        test(ToT);
        static typename AddRef<FromT>::type makeFrom();  //if FromT is C array type

        enum {value = sizeof(MiniMPL::Yes_Type) == sizeof(test(makeFrom())) };
    };
    template<typename T>	struct ConvertTester<T,T>   :public TrueType{};
    template<typename T>	struct ConvertTester<T,void>:public FalseType{};
    template<typename T>	struct ConvertTester<void,T>:public FalseType{};
#pragma warning( pop )

    template<typename BaseT, typename DeriveT>  struct BaseDeriveTester
    { //in order to independent on OS and compiler , don't use MS specific : __is_base_of 
    private:
        template<typename T> struct ClassPointer : public AddCPointer<typename GetRawType<T>::type>{};
        typedef ConvertTester<typename ClassPointer<DeriveT>::type,typename ClassPointer<BaseT>::type>   H;  
        //filter int/char/float convertible ,e.g. int* => char* is illegal

    public:
        enum { value = And_T<H,Not_T<IsSameRawType<BaseT,DeriveT> > >::value };
    };
    template<typename DeriveT>  struct BaseDeriveTester<void,DeriveT>   : public FalseType{};
    template<typename BaseT>    struct BaseDeriveTester<BaseT,void>     : public FalseType{};

    template<typename T1, typename T2>  struct IsSameType;//fw declare
    template<typename T>        struct BuildInTypeTester 
    {
    private:
        template<typename U>    struct tester: IsSameType<T,U> {};

    public:
        enum{isFloat    = Or_T<tester<float>,tester<double>,tester<long double> >::value};
        enum{isChar     = Or_T<tester<char>, tester<unsigned char>,tester<signed char>,tester<wchar_t> >::value };
        enum{isInteger  = Or_T<tester<bool>,  BoolType<isChar>,
            Or_T<tester<short>, tester<unsigned short>, tester<int>,    tester<unsigned int>         >,
            Or_T<tester<long>,  tester<unsigned long>,  tester<__int64>,    tester<unsigned __int64> > >::value };

        enum{isBuildin=Or_T<IsCPointer<T>,BoolType<isFloat>,BoolType<isInteger> >::value };
        enum{value=Or_T<IsCPointer<T>,BoolType<isFloat>,BoolType<isInteger> >::value };
        /* below comes from C++ primer chapter 3, other is default
        bool                        //ANSI/ISO C++ 
        wchar_t                     //unicode , compiler dependency
        float                       //ANSI/ISO C++     
        double                      //ANSI/ISO C++     
        __int64                     //C99
        unsigned __int64            //C99     
        long double                 //ANSI/ISO C++
        IsPointer                   //default pointer
        */
    };

    template<typename T>        struct ClassStructTester
    {
        template<typename C> static MiniMPL::No_Type		test(...);		    //SFINAE    : capture default    type
        template<typename C> static MiniMPL::Yes_Type		test(bool C::*);    //SFINAE    : capture customized type

        enum { value = sizeof(test<T>(0)) == sizeof(MiniMPL::Yes_Type) };
    };

    template<typename T,bool bRef=IsRef<T>::value>  struct AtomTester;
    template<typename T> struct AtomTester<T,true>: public TrueType{};
    template<typename T> struct AtomTester<T,false>:public And_T<Not_T<ClassStructTester<T> > , Not_T< ArrayTester<T> > >{};
}

#endif // ISXXX_DETAIL_H__
