#ifndef __TRAVERSETYPECONTAINER_HPP__
#define __TRAVERSETYPECONTAINER_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/innerDetail/traverseTypeContainer_detail.hpp>
#include <MiniMPL/innerDetail/traverseEnumRange_detail.hpp>
#include <MiniMPL/innerDetail/traverseTypeList_detail.hpp>
#include <MiniMPL/functionParams.hpp>
#include <MiniMPL/paramPackageCall.hpp>

namespace MiniMPL
{
    //bIncrease indicates increase lookup or decrease lookup
    //TypeContainer_T can be CEnumRange or Typelist, depends on traverseXXXX_detail.hpp
    template<typename TypeContainer_T,bool bIncrease=true>
    struct CTraverseTypeContainer : protected InnerDetail::CTraverseTypeContainerBase<TypeContainer_T,bIncrease>
    {
        template<typename Tester_T=TDefaultSelfAdaptedParam>
        struct applyTester   //Tester_T can be defined by Declare_Template_Tester
        {   //below interface need tester
            //Callback_T can be defined by TDeclare_Template_CallBack
            template<typename Callback_T,typename TesterParam_T>
            static typename Callback_T::type getFuncAddr(TesterParam_T testParms)
            {     
                if (checkOutOfRange((TypeContainer_T*)NULL,testParms))
                {
                    return NULL;  //rapid check enum out of enum range
                }

                typedef typename Callback_T::type CallbackFunc_T;
                CallbackFunc_T  pF = NULL;
                LongJump_Begin();
                apply<BoundaryFrom_T>::GetFuncAddrImpl<Callback_T,Tester_T,TesterParam_T>(testParms,pF LongJump_RParam);
                LongJump_End();
                return pF;
            }

            template<typename Callback_T,typename TesterParam_T,typename CallbackFuncParams_T>
            static FR(typename Callback_T::type) execute(TesterParam_T testParms,
                CallbackFuncParams_T& callbackParams,FR(typename Callback_T::type) defValue)
            {
                typedef typename Callback_T::type TF;
                TF pf = getFuncAddr<Callback_T,TesterParam_T>(testParms);
                if (pf)
                {
                    return MiniMPL::doPackCall(pf,callbackParams);
                }
                return defValue;            
            }

            template<typename Callback_T,typename TesterParam_T,typename CallbackFuncParams_T>
            static bool execute(TesterParam_T testParms,CallbackFuncParams_T& callbackParams)
            {
                typedef typename Callback_T::type TF;
                TF pf = getFuncAddr<Callback_T,TesterParam_T>(testParms);
                if (pf)
                {
                    MiniMPL::doPackCall(pf,callbackParams);
                    return true;
                }
                return false;            
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //any type version
            template<typename FromType_T,typename Callback_T,typename TesterParam_T,typename CallbackFuncParams_T>
            static bool executeFrom(TesterParam_T testParms,CallbackFuncParams_T& callbackParams)
            {
                typename Callback_T::type pf = NULL;
                LongJump_Begin();
                apply<FromType_T>::GetFuncAddrImpl<Callback_T,Tester_T,TesterParam_T>(testParms,pf LongJump_RParam);
                LongJump_End();
                if (pf)
                {
                    MiniMPL::doPackCall(pf,callbackParams);
                    return true;
                }
                return false;            
            }
            //enum type version
            template<typename TesterParam_T,TesterParam_T TVal,typename Callback_T,typename CallbackFuncParams_T>
            static bool executeFrom(TesterParam_T testParms,CallbackFuncParams_T& callbackParams)
            {
                typedef typename LoopTypeContainer_T::template MakeType<TVal>::type FromType;
                return executeFrom<FromType,Callback_T>(testParms,callbackParams);          
            }
        };
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename FuncID_T=TDefaultSelfAdaptedParam>
        struct applyFuncIdGenerator //FuncID_T can be defined by Declare_Template_FuncID
        {
            template<typename Callback_T,typename TKey,typename TValue>
            static int getAllFuncAddr(stlMap<TKey,TValue>& rMap)
            {
                LongJump_Begin();
                typedef InnerDetail::GetAllFuncAddrInterface<Callback_T,FuncID_T,TKey,TValue> GetAllFuncAddrInterface_T;
                forEach<GetAllFuncAddrInterface_T>(MiniMPL::makeParamPackage_Ref(rMap));
                LongJump_End();
                return rMap.size();
            }
        };
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename Callback_T,typename CallbackFuncParams_T>
        static void forEach(CallbackFuncParams_T& callbackParams)
        {
            LongJump_Begin();
            apply<BoundaryFrom_T>::ForEachImpl<Callback_T>(callbackParams LongJump_RParam);
            LongJump_End();
        }

        static stlString dump()
        {
            char strhead[128] = {0};
            sprintf_s(strhead,128,"[%s,%s]: " , bIncrease ? "Increase" : "Decrease", InnerDetail::TypeContainerName((TypeContainer_T*)NULL));

            stlString dumpStr = toString(strhead);
            forEach<InnerDetail::CDumpTypeContainer<TypeContainer_T> >(ParamPackageCall<stlString&>(dumpStr));
            dumpStr += TXT("\n");
            return dumpStr;
        }
    };

}


#endif // __TRAVERSETYPECONTAINER_HPP__
