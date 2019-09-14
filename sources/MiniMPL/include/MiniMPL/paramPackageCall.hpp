#ifndef __PARAMPACKAGECALL_HPP__
#define __PARAMPACKAGECALL_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/paramPackageCall_detail.hpp>

namespace MiniMPL 
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T> struct TToParamPackageCall : public InnerDetail::TPackCallParamsImpl<T>{};
    template<typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
    struct ParamPackageSize<ParamPackageCall<TP1,TP2,TP3,TP4,TP5,TP6,TP7> > 
        : public ParamPackageSize<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7>>{};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename F,typename TP>
    inline FR(F) doPackCall(F f,TP& p,ENABLE_IF(!InnerDetail::IsPack<RAWTYPE(TP)>::value))
    {
        return f(p);
    }
    
    template<typename F,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
    inline FR(F) doPackCall(F f,ParamPackageCall<TP1,TP2,TP3,TP4,TP5,TP6,TP7>& rObj)
    {
        return rObj.packCall(f);
    }
    template<typename F,typename TP1,typename TP2,typename TP3,typename TP4,typename TP5,typename TP6,typename TP7>
    inline FR(F) doPackCall(F f,ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7>& rObj)
    {
        typedef typename TToParamPackageCall<ParamPackage<TP1,TP2,TP3,TP4,TP5,TP6,TP7> >::type  TCallPack;
        return static_cast<TCallPack&>(rObj).packCall(f);
    }
}

#endif // __PARAMPACKAGECALL_HPP__
