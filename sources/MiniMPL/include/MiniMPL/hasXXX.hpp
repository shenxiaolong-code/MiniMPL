#ifndef __HASXXX_HPP__
#define __HASXXX_HPP__
/***********************************************************************************************************************
* Description         : test whether has embedded XXX type. borrow idea from boost lib(thanks).
*                       usage example: 
*                       HasXXXDef(type);
*                       Static_Assert(1 != Has_type<bool>::value);
*                       Static_Assert(1 == Has_type<MiniMPL::Type2Type<bool> >::value);
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/macroDef.h>

// detect whether a type S has a embed sub-type named M
#define HasXXXType(M)                                                                                                                                           \
    template<typename U,typename S=MiniMPL::NullType>    struct HasType_##M                                                          : MiniMPL::FalseType {};   \
    template<typename S>                                 struct HasType_##M <S,typename MiniMPL::sfinae_helper<typename S::M>::type> : MiniMPL::TrueType  {}

// detect whether a type T has a method named M , which the TF is signatue to recognize the function override. M2 is optional if the structure name is unique.
//M : methodName , TF : method signature , M2 : optional additional method flag to recognize function overload
#define HasXXXMethod(M,TF,M2)                                                                       \
template<typename T>  struct HasMethod##M2##_##M                                                    \
{                                                                                                   \
protected:                                                                                          \
    template <typename U,TF> struct sfinae_v_helper{};                                              \
    template <typename U>   static MiniMPL::Yes_Type test(sfinae_v_helper<U, &U::M > * );           \
    template <typename U>   static MiniMPL::No_Type  test(...);                                     \
                                                                                                    \
public:                                                                                             \
    enum {value =  sizeof(MiniMPL::Yes_Type)==sizeof(test<T>(0)) };                                 \
};

// detect whether a type S has a data member named M
#define HasXXXData(M)                                                                               \
template<typename T>  struct HasData_##M                                                            \
{                                                                                                   \
protected:                                                                                          \
    template <typename C> static MiniMPL::Yes_Type test( decltype( & C::M ) ) ;                     \
    template <typename C> static MiniMPL::No_Type  test(...);                                       \
                                                                                                    \
public:                                                                                             \
    enum {value =  sizeof(MiniMPL::Yes_Type)==sizeof(test<T>(0)) };                                 \
};


// detect if T has sequence T.M1.M2  member
#define HasXXXDataSequence( M1 , M2 )                                                                                       \
HasXXXData( M1 ) ;                                                                                                          \
HasXXXData( M2 ) ;                                                                                                          \
template<typename  T , bool bMember1 = HasData_##M1< T >::value>                                                            \
struct has_sequence_member            : public MiniMPL::FalseType {};                                                       \
template<typename  T>                                                                                                       \
struct has_sequence_member<T, true>   : public MiniMPL::BoolType<HasData_##M2<decltype( ((T*)0)->##M1 )>::value > {};       \

namespace MiniMPL
{
    template<typename T>                        struct sfinae_helper : Type2Type<NullType>   {}; 

    // test whether a type meets expected test bool sequence
    template<typename T1, typename T2>              struct IsSameType;
    template< template <class> class  ... Targs>    struct SequenceTestSet
    {
        template<bool ... Vals>     struct boolSequence {} ;
        template<typename T>        struct genBoolSequence : public MiniMPL::Type2Type< boolSequence< Targs<T>::value ... > >  {};	

        template<typename T , bool ... Vals > struct apply : public MiniMPL::IsSameType< boolSequence<Vals ... > , typename genBoolSequence<T>::type > {};	
    };
}

#endif // __HASXXX_HPP__
