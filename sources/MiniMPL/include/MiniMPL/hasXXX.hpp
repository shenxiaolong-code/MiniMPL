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

#define HasXXXType(M)                                                                                                                           \
    template<typename U,typename S=MiniMPL::NullType>    struct MAKEVAR(HasType_,M) : MiniMPL::FalseType {};                                    \
    template<typename S> struct MAKEVAR(HasType_,M)<S,typename MiniMPL::sfinae_helper<typename MAKEVAR(S::,M)>::type> : MiniMPL::TrueType  {}

//M : methodName , TF : method signature , M2 : optional additional method flag to recognize function overload
#define HasXXXMethod(M,TF,M2)                                                                       \
template<typename T>  struct HasMethod##M2##_##M                                                    \
{                                                                                                   \
protected:                                                                                          \
    template <typename U,TF> struct sfinae_v_helper{};                                              \
    template <typename U>   static MiniMPL::Yes_Type test(sfinae_v_helper<U,MAKEVAR(&U::,M)> * );   \
    template <typename U>   static MiniMPL::No_Type  test(...);                                     \
                                                                                                    \
public:                                                                                             \
    enum {value =  sizeof(MiniMPL::Yes_Type)==sizeof(test<T>(0)) };                                 \
};

#define HasXXXMember(M)                                                                             \
template<typename T>  struct HasMember_##M                                                          \
{                                                                                                   \
protected:                                                                                          \
    template <typename C> static MiniMPL::Yes_Type test( decltype( & C::M ) ) ;                     \
    template <typename C> static MiniMPL::No_Type  test(...);                                       \
                                                                                                    \
public:                                                                                             \
    enum {value =  sizeof(MiniMPL::Yes_Type)==sizeof(test<T>(0)) };                                 \
};

namespace MiniMPL
{
    template<typename T>                        struct sfinae_helper : Type2Type<NullType>   {}; 
}

#endif // __HASXXX_HPP__
