#ifndef TRAVERSETYPEDETAIL_H__
#define TRAVERSETYPEDETAIL_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	detail implement for traverseTypeContainer
*************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/macro_longJump.h>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/fromToString.hpp>

namespace MiniMPL
{
    template <class T, class U> struct Typelist;                                                //fw declare
    template<typename CEnumRange_T,typename CEnumRange_T::Enum_T TVal>    struct CEnumValue;    //fw declare

    struct TDefaultSelfAdaptedParam; //In general, it is OK for enum/int type

    //default graceful way, and use can override this interface
    template<typename Range_T,typename Param_T> 
    inline bool checkOutOfRange(Range_T*,Param_T& p) { return false; }

    namespace InnerDetail
    {
        template<typename T> struct CDumpTypeContainer;
        template<typename T> inline const char* TypeContainerName(T*) { return "unknown"; }

        //TypeContainer fw declare
        template<typename TypeContainer,bool bIncrease> struct TypeContainerProperty; 

        //test whether type is matched with one val.
        template<typename UserTest_T>   struct IsTypeMatched
        {   //user defined case,user tester : UserTest_T
            template<typename Current_T,typename TestParam_T>
            static bool test(Current_T*,TestParam_T& p)
            {
                return UserTest_T::test<Current_T>(p);
            }
        }; 

        template<typename FuncId_T>
        struct FuncAddrProperty
        {
            template<typename TR,typename T> static TR getInterfaceID(T*) {return FuncId_T::getId<TR,T>();}
        };

        template<typename TypeContainer_T,bool bIncrease>
        struct CTraverseTypeContainerBase
        {
            typedef TypeContainerProperty<TypeContainer_T,bIncrease>        LoopTypeContainer_T;
            //MUST typedef BoundaryFrom_T because current LoopTypeContainer_T::BoundaryFrom_T is not visible
            typedef typename LoopTypeContainer_T::BoundaryFrom_T            BoundaryFrom_T;
            typedef typename LoopTypeContainer_T::BoundaryGuard_T           BoundaryGuard_T;

            template<typename Current_T>
            struct apply
            {
                typedef typename LoopTypeContainer_T::template Next<Current_T>::type  Next_T;

                template<typename Callback_T,typename Tester_T,typename TestParam_T>
                static void GetFuncAddrImpl(TestParam_T testParms,typename Callback_T::type& pFunc LongJump_FParam)
                {
                    if (IsTypeMatched<Tester_T>::test((Current_T*)NULL,testParms))
                    {    
                        pFunc = Callback_T::getInterface((Current_T*)NULL);
                        LongJump_Return0();
                    }
                    else
                    {
                        apply<Next_T>::GetFuncAddrImpl<Callback_T,Tester_T,TestParam_T>(testParms,pFunc LongJump_RParam);
                    }
                }
                template<typename Callback_T,typename TParams>
                static void ForEachImpl(TParams& callbackParams LongJump_FParam)
                {
                    typename Callback_T::type f=Callback_T::getInterface((Current_T*)NULL); //help compiler deduce
                    MiniMPL::doPackCall(f,callbackParams);
                    apply<Next_T>::ForEachImpl<Callback_T>(callbackParams LongJump_RParam);
                }
            };

            template<typename subHead,typename Tail>
            struct apply<Typelist<subHead,Tail> >
            {  
                typedef Typelist<subHead,Tail>                                              SubTypeList_T;
                typedef CTraverseTypeContainerBase<SubTypeList_T,bIncrease >                SubLoopTypeContainer_T;
                typedef typename LoopTypeContainer_T::template Next<SubTypeList_T>::type    Next_T;

                template<typename Callback_T,typename Tester_T,typename TestParam_T>
                static void GetFuncAddrImpl(TestParam_T testParms,typename Callback_T::type& pFunc LongJump_FParam)
                {
                    LongJump_Begin2();
                    SubLoopTypeContainer_T::apply<subHead>::GetFuncAddrImpl<Callback_T,Tester_T>(testParms,pFunc LongJump_RParam2);
                    LongJump_End();
                    if (pFunc)
                    {
                        LongJump_Return0();
                    }
                    else
                    {   //continue parent loop
                        apply<Next_T>::GetFuncAddrImpl<Callback_T,Tester_T>(testParms,pFunc LongJump_RParam);
                    }
                }
                template<typename Callback_T,typename CallbackFuncParams_T>
                static void ForEachImpl(CallbackFuncParams_T& callbackParams LongJump_FParam)
                {
                    LongJump_Begin2();
                    SubLoopTypeContainer_T::apply<subHead>::ForEachImpl<Callback_T>(callbackParams LongJump_RParam2);
                    LongJump_End();
                    //continue parent loop
                    apply<Next_T>::ForEachImpl<Callback_T>(callbackParams LongJump_RParam);
                }
            };
//...................................................................................................................//
            template<>
            struct apply<BoundaryGuard_T>
            {
                template<typename Callback_T,typename Tester_T,typename TestParam_T>
                static void GetFuncAddrImpl(TestParam_T testParms,typename Callback_T::type& pFunc LongJump_FParam)
                {
                    pFunc = NULL;
                    LongJump_Return0();
                }
                template<typename Callback_T,typename CallbackFuncParams_T>
                static void ForEachImpl(CallbackFuncParams_T& callbackParams LongJump_FParam)
                {
                    LongJump_Return0();
                }
            };
        };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename TypeContainer_T,typename TestParam_T>
        void warningOutOfRange(TestParam_T testParms)
        {
            outputTxtV(TXT("\n[Warning]Type value[%s] is out of range,available enum list:\n"),toString(val).c_str());
            outputTxtV(TXT("%s%s\n"),CTraverseTypeContainer<TypeContainer_T,bIncrease>::dump().c_str(),HEREINFO());                    
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename Callback_T,typename FuncID_T,typename TKey,typename TValue>
        struct GetAllFuncAddrInterface : protected FuncAddrProperty<FuncID_T>,public Type2Type<void (*)(stlMap<TKey,TValue>&)>
        {  
            template<typename T>
            static void execute(stlMap<TKey,TValue>& rMap)
            { 
                T* p=NULL;    //help to type recognize in template function
                MapInsert(rMap,getInterfaceID<TKey>(p), Callback_T::getInterface(p) );
            }

            template<typename T>
            static type getInterface(T*)
            {
                return & execute<T>;
            }
        };
    }
}

#endif // TRAVERSETYPEDETAIL_H__
