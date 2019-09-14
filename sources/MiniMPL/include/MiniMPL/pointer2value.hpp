#ifndef __POINTER2VALUE_HPP__
#define __POINTER2VALUE_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/productSpecialDef.h>

#define VT(X)           typename MiniMPL::Pointer2Value<X>::type       //get value type from pointer type

namespace MiniMPL
{
    template<typename T,bool b=IsStlIterator<T>::value>    
    struct Pointer2ValueImpl                                    : public RemoveCPointer<T>{};
    template<typename T> struct Pointer2ValueImpl<T,true>       : public Type2Type<typename T::value_type>{};

    template<typename T> struct Pointer2Value                   : public Pointer2ValueImpl<T>{};
    template<typename T> struct Pointer2Value<stlSmartptr<T> >  : public Type2Type<T> {};

    template<typename T> struct Pointer2ValueFinal : If_Evl<IsPointer<T>,Pointer2ValueFinal<typename Pointer2Value<RAWTYPE(T)>::type>,Type2Type<T> >::type {};

    namespace Get
    {
        template<typename T>
        struct TestPointer : And_T<IsPointer<T>,Not_T<IsStringC<T> > >{};

        template<typename DataType>
        inline DataType& value(DataType& Obj,ENABLE_IF(!TestPointer<DataType>::value))
        {
            return Obj;
        }

        template<typename PDataType>
        inline VT(PDataType)& value(PDataType& Obj,ENABLE_IF(TestPointer<PDataType>::value))      //Not Tested, No test Code
        {
            return *Obj;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename DataType>
        inline typename Pointer2Value<DataType>::type* CPointer(DataType& rObj)      //Not Tested, No test Code
        {
            return &value(rObj);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename DataType>
        inline DataType& finalValue(DataType& Obj,ENABLE_IF(!TestPointer<DataType>::value))      //Not Tested, No test Code
        {
            return Obj;
        }

        template<typename PDataType>
        inline typename Pointer2ValueFinal<PDataType>::type& finalValue(PDataType& pObj,ENABLE_IF(TestPointer<PDataType>::value))      //Not Tested, No test Code
        {
            return finalValue(*pObj);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename DataType>
        inline typename Pointer2ValueFinal<DataType>::type* finalCPointer(DataType& Obj)      //Not Tested, No test Code
        {
            return &finalValue(Obj);
        }
    };
}


#endif // __POINTER2VALUE_HPP__
