#ifndef __UNARYFUNCTIONPARAMTRANSFER_H__
#define __UNARYFUNCTIONPARAMTRANSFER_H__
/***********************************************************************************************************************
* Description         : auto convert when convertable.e.g.
*                       T   =>  T*
*                       T*  =>  T
*                       stlSmartptr<T> => T / stlSmartptr<T> => T*
*                       vector<T>::iterator =>  T  /  vector<T>::iterator => T*
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/convert_enable_if.hpp>

#if ENABLE_TRACE
    #include <MiniMPL/macroDef.h>
    #define TRACE_CVT_ENABLEIF(X)     outputTxt(TXT(X) HEREINFO_POS())
#else
    #define TRACE_CVT_ENABLEIF(X)
#endif // ENABLE_TRACE

#define AutoConvertUnaryFunctionParam(UF,Param_T,Return_T)                                                  \
template<typename T>                                                                                        \
Return_T UF (T& obj,ENABLE_IF((MiniMPL::ConvertEnableIf<T,Param_T>::ImplicitConstructDiffObj::value)))       \
{                                                                                                           \
    TRACE_CVT_ENABLEIF("\nImplicitConstructDiffObj\n");                                                       \
    typename MiniMPL::RemoveRef<Param_T>::type cvtObj = obj; /*implicit Construct */                        \
    return  UF (cvtObj);                                                                                    \
}                                                                                                           \
                                                                                                            \
template<typename T>                                                                                        \
Return_T UF (T pObj,ENABLE_IF((MiniMPL::ConvertEnableIf<T,Param_T>::Pointer2Value::value)))                  \
{   /*  Pointer => Object   */                                                                              \
    TRACE_CVT_ENABLEIF("\nPointer2Value\n");                                                                  \
    return UF (*pObj);                                                                                      \
}                                                                                                           \
                                                                                                            \
template<typename T>                                                                                        \
Return_T UF (stlSmartptr<T>& pObj,ENABLE_IF((MiniMPL::ConvertEnableIf<T,Param_T>::Pointer2Value::value)))    \
{   /*  stl smart Pointer => Object   */                                                                    \
    TRACE_CVT_ENABLEIF("\nstlSmartptr Pointer2Value\n");                                                      \
    return UF (*pObj);                                                                                      \
}                                                                                                           \
                                                                                                            \
template<typename T>                                                                                        \
Return_T UF (T& rObj,ENABLE_IF((MiniMPL::ConvertEnableIf<T,Param_T>::Value2CPointer::value)))                \
{   /*  Object => CPointer (T*)     */                                                                      \
    TRACE_CVT_ENABLEIF("\nValue2CPointer\n");                                                                 \
    T* pObj = &rObj; /*resolve reference to hard-code address if UF (T*&) */                                \
    return UF (pObj);                                                                                       \
}                                                                                                           \
                                                                                                            \
template<typename T>                                                                                        \
Return_T UF (T pObj,ENABLE_IF((MiniMPL::ConvertEnableIf<T,Param_T>::DiffPointer2CPointer::value)))           \
{   /*  Pointer Obecjt (smartPointer/Iterator) => CPointer (T*)     */                                      \
    TRACE_CVT_ENABLEIF("\nDiffPointer2CPointer\n");                                                           \
    return UF (*pObj);                                                                                      \
}   

#endif // __UNARYFUNCTIONPARAMTRANSFER_H__
