#ifndef TRAVERSETYPELIST_DETAIL_H__
#define TRAVERSETYPELIST_DETAIL_H__

/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/typeList.hpp>

namespace MiniMPL
{
    namespace InnerDetail
    {
        template<typename U,typename T> 
        inline const char* TypeContainerName(Typelist<U,T>*) { return "TypeList<...>"; }

        template<typename Head,typename Tail,bool bIncrease>
        struct TypeContainerProperty<Typelist<Head,Tail>,bIncrease>
        {   //handle general case
            typedef Typelist<Head,Tail>                         OriginalList_T;
            typedef typename If_T<bIncrease,OriginalList_T,typename TL::Reverse<OriginalList_T>::type>::type    IncreaseList; 

            typedef typename TL::TypeAt<IncreaseList,0>::type   BoundaryFrom_T;
            typedef NullType                                    BoundaryGuard_T;

            template<typename T> struct Next : public TL::TypeAtNonStrict<IncreaseList,1+TL::IndexOf<IncreaseList,T>::value> {};
        };

        template<typename U,typename T>
        struct CDumpTypeContainer<Typelist<U,T> > : public Type2Type< void (*)(stlString&) >
        {
            template<typename T>
            static void dumpType(stlString& rDumpInfo)
            {  
                char buf[256] = {0};
                sprintf_s(buf,256," %s ",typeid(T).name());
                rDumpInfo += toString(buf);
            }

            template<typename T>
            static type getInterface(T*)
            {
                return & CDumpTypeContainer::dumpType<T>;
            }
        };
    }
}

#endif // TRAVERSETYPELIST_DETAIL_H__
