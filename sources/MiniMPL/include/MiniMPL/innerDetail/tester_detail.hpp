#ifndef TESTER_DETAIL_H__
#define TESTER_DETAIL_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/macroDef.h>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/sameQualifier.hpp>

namespace MiniMPL
{       
    namespace InnerDetail
    {
        template<char c>    struct ApplyOperation;
        template<> struct ApplyOperation<'&'>
        {
            template<typename UT1,typename UT2,typename T> 
            static bool impl(UT1& ut1,UT2& ut2,T& p)  { return ut1(p) && ut2(p); }
        };
        template<> struct ApplyOperation<'|'>
        {
            template<typename UT1,typename UT2,typename T>
            static bool impl(UT1& ut1,UT2& ut2,T& p)  { return ut1(p) || ut2(p); }
        };
        template<> struct ApplyOperation<'^'>
        {
            template<typename UT1,typename UT2,typename T> 
            static bool impl(UT1& ut1,UT2& ut2,T& p)  { return ut1(p) ^ ut2(p);  }
        };
    }

    //TestImpl : for runtime performance optimization
    template<typename Ref_T,class TCmp/*,bool bPointer=IsPointer<Ref_T>::value*/>
    struct UnaryComparer
    {
        template<typename T>
        struct CmpDirectly : Or_T<Not_T<IsPointer<T> >,IsSameRawType<T,Ref_T> > {};

        Ref_T       m_cmpRef;
        TCmp        m_cmp; 

        UnaryComparer(TPP(Ref_T) cmpRef,TPP(TCmp) rCmp)
            :m_cmpRef(cmpRef),m_cmp(rCmp){};

        template<typename T>
        bool test(T& rObj,ENABLE_IF(CmpDirectly<T>::value))
        {
            return m_cmp(m_cmpRef,rObj);
        }

        template<typename T>
        bool test(T& rObj,ENABLE_IF(!CmpDirectly<T>::value))
        {
            return m_cmp(m_cmpRef,Get::finalValue(rObj));
        }
    };
    /*
    template<typename Ref_T,class TCmp> struct UnaryComparer<Ref_T,TCmp,true>
    {  
        Ref_T       m_cmpRef;
        TCmp        m_cmp;

        UnaryComparer(TPP(Ref_T) cmpRef,TPP(TCmp) rCmp)
            :m_cmpRef(cmpRef),m_cmp(rCmp){};

        template<typename T>
        bool test(T& rObj,ENABLE_IF(!IsPointer<T>::value))
        {
            return m_cmp(Get::finalValue(m_cmpRef),rObj);
        }

        template<typename T>
        bool test(T& rObj,ENABLE_IF(IsPointer<T>::value))
        {
            return m_cmp(Get::finalValue(m_cmpRef),Get::finalValue(rObj));
        }
    };
    */
}

#endif // TESTER_DETAIL_H__
