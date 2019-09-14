#ifndef __CONVERT_ENABLE_IF_HPP__
#define __CONVERT_ENABLE_IF_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/pointer2value.hpp>
#include <MiniMPL/isXXXEx.hpp>

namespace MiniMPL
{
    template<typename TReal,typename TFormal>
    struct ConvertEnableIf
    {
    protected:
        template<typename TF,typename TT>
        struct IsDiffType : public Not_T<Or_T<IsSameRawType<TF,TT>, IsBaseDerive<TT,TF> > > { };

        template<typename From_T,typename To_T,bool bDiffType = IsDiffType <typename Pointer2ValueFinal<From_T>::type,typename Pointer2ValueFinal<To_T>::type>::value > 
        struct ImplicitConstructTester : public FalseType {};
        template<typename From_T,typename To_T> struct ImplicitConstructTester<From_T,To_T,true> 
        : public IsConvertable<From_T,typename RemoveRef<To_T>::type > {};
        template<typename From_T,typename To_T>
        struct IsSerialClass: public Or_T<IsBaseDerive<To_T,From_T>,IsSameRawType<To_T,From_T> >{};

    public:
        //e.g. T* / stlSmartptr<T> / stlVector<T>::iterator / ... => T
        struct Pointer2Value   : public BoolType<And_T< IsPointer<TReal> , Not_T<IsPointer<TFormal> > , 
            IsSerialClass<typename Pointer2ValueFinal<TReal>::type,RAWTYPE(TFormal)> >::value>{};
        //e.g. T => T*
        struct Value2CPointer  : public BoolType<And_T< Not_T< Or_T<IsPointer<TReal>, IsArray<TReal> > > , IsCPointer<TFormal> >::value> {};
        //non T* => T* , e.g. stlSmartptr<T>/ stlSmartptr<T*> / stlSmartptr<T>* / stlVector<T>::iterator => T* [Note: except T* => T* because it needn't tag dispatch]
        struct DiffPointer2CPointer : public BoolType<And_T< And_T< IsPointer<TReal>,Not_T<IsSameRawType<TReal,TFormal> > > , IsCPointer<TFormal> >::value> {};
        //different type and implicit Construct, it needs TB::TB(TA const& rOther), e.g. char*/char[LEN] => stlStringA
        //implicit Construct condition: From , To
        //1). To can't be abstract class
        //2). To can't be reference object if From is not same type with To
        //    (if same type, it shouldn't implicit construct another instance -- it is not necessary)
        struct ImplicitConstructDiffObj : public ImplicitConstructTester<TReal,TFormal> {};
    };
}

#endif // __CONVERT_ENABLE_IF_HPP__
