#ifndef TRAVERSEENUMRANGE_DETAIL_H__
#define TRAVERSEENUMRANGE_DETAIL_H__
/***********************************************************************************************************************
Description         : 
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/enumTrait.hpp>

namespace MiniMPL
{
    template<typename F,F F_min,F F_max>
    inline bool checkOutOfRange(::MiniMPL::CEnumRange<F,F_min,F_max>*,F& p) { return p<F_min || p>F_max; }

    namespace InnerDetail
    {
        template<typename F,F F_min,F F_max>
        inline const char* TypeContainerName(::MiniMPL::CEnumRange<F,F_min,F_max>*) { return typeid(F).name(); }

        template<>  //can override IsTypeMatched<> to resolve specified case
        struct IsTypeMatched<TDefaultSelfAdaptedParam>
        {   //default tester , it is suitable for enum value and int
            template<typename F,F F_min,F F_max,F TVal>
            static bool test(CEnumValue<CEnumRange<F,F_min,F_max>,TVal>*,F p)
            {
                return TVal==p;
            }
        };

        template<typename TypeContainer,bool bIncrease> struct TypeContainerProperty; //TypeContainer fw declare
        template<typename F,F F_min,F F_max,bool bIncrease>
        struct TypeContainerProperty<CEnumRange<F,F_min,F_max>,bIncrease> : public CEnumRange<F,F_min,F_max>
        {   //handle CEnumRange
            typedef typename If_T<bIncrease,Min_T,Max_T>::type          Head_T;
            typedef typename If_T<bIncrease,Max_T,Min_T>::type          Tail_T;
            typedef Head_T                                              BoundaryFrom_T;
            typedef typename Tail_T::template Next<bIncrease>::type     BoundaryGuard_T;

            template<typename T>    struct Next     : public T::template Next<bIncrease>{};
            template<F TVal>        struct MakeType : public Type2Type<CEnumValue<CEnumRange,TVal> >{};
        };

        template<>
        struct FuncAddrProperty<TDefaultSelfAdaptedParam>
        {  
            template<typename TR,typename F,F F_min,F F_max,F TVal>
            static TR getInterfaceID(CEnumValue<CEnumRange<F,F_min,F_max>,TVal>*) {return TVal;}
        };

        template<typename F,F F_min,F F_max>
        struct CDumpTypeContainer<CEnumRange<F,F_min,F_max> > : public Type2Type< void (*)(stlString&) >
        {
            typedef CEnumRange<F,F_min,F_max>   EnumRange_T;
            typedef F                           Enum_T;

            template<typename T,T TVal>
            static void dumpEnum(stlString& rDumpInfo)
            { 
                char buf[8] = {0};
                sprintf_s(buf,8," %d ",TVal);
                rDumpInfo += toString(buf);
            }

            template<typename EnumRange_T,typename EnumRange_T::Enum_T TVal>
            static type getInterface(CEnumValue<EnumRange_T,TVal>*)
            {
                return & CDumpTypeContainer::dumpEnum<typename EnumRange_T::Enum_T,TVal>;
            }
        };
    }
}

#endif // TRAVERSEENUMRANGE_DETAIL_H__
