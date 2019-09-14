#ifndef __ADDREMOVE_DETAIL_HPP__
#define __ADDREMOVE_DETAIL_HPP__
/***********************************************************************************************************************
* Description         : implemented for addRemove_detail.hpp
                        add/remove qualifier : reference,const,CPointer,Volatile
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/macro_traitimpl.hpp>
#include <MiniMPL/kitType.hpp>

namespace MiniMPL
{
    namespace InnerDetail
    {
        //////////////////////////////////AddRef/RemoveRef////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>    struct add_reference           : public Type2Type<T&>  {};
        template<typename T>    struct add_reference<T&>       : public Type2Type<T&>  {};
        template<>              struct add_reference<void>     : public Type2Type<void>{};
        template<typename T,unsigned int LEN>   struct add_reference<T(&)[LEN]>    : public Type2Type<T(&)[LEN]>  {};
        template<typename T,unsigned int LEN>   struct add_reference<T[LEN]>       : public Type2Type<T(&)[LEN]>  {};

        template<typename T>    struct remove_reference        : public Type2Type<T>   {};
        template<typename T>    struct remove_reference<T&>    : public Type2Type<T>   {};
        template<>              struct remove_reference<void>  : public Type2Type<void>{};
        template<typename T,unsigned int LEN>   struct remove_reference<T(&)[LEN]>    : public Type2Type<T[LEN]>  {};
        template<typename T,unsigned int LEN>   struct remove_reference<T[LEN]>       : public Type2Type<T[LEN]>  {};

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>    struct add_pointer          : Type2Type<T*>                                 {};
        template<typename T>    struct add_pointer<T&>      : Type2Type<T*&>                                {};
        template<typename T>    struct add_pointer<T*&>     : Type2Type<T*&>                                {};

        template<typename T>    struct remove_pointer       : Type2Type<T>                                  {};
        template<typename T>    struct remove_pointer<T*>   : Type2Type<T>                                  {};
        template<typename T>    struct remove_pointer<T*&>  : Type2Type<T&>                                 {};

        //////////////////////////////////AddConst/RemoveConst///////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>                    struct add_const                     : Type2Type<T const>    {}; 
        template<typename T>                    struct add_const<T&>                 : Type2Type<T const&>   {}; 

        template<typename T>                    struct remove_const                  : Type2Type<T>          {};
        template<typename T>                    struct remove_const<T const>         : Type2Type<T>          {};
        template<typename T>                    struct remove_const<T const&>        : Type2Type<T&>         {}; 
        template<typename T>                    struct remove_const<T const*>        : Type2Type<T*>         {};	    //pointer point to constant ,pointer can be moved.
        template<typename T>                    struct remove_const<T const* const>  : Type2Type<T const*>   {};	    //pointer point to constant ,pointer can be moved.
        template<typename T,unsigned int LEN>   struct remove_const<const T[LEN]>    : Type2Type<T[LEN]>     {};     //array style
        template<typename T,unsigned int LEN>   struct remove_const<const T(&)[LEN]> : Type2Type<T (&)[LEN]> {};	    //array ref style
        template<typename T,unsigned int LEN>   struct remove_const<const T(*)[LEN]> : Type2Type<T (*)[LEN]> {};	    //array pointer style
        ////////////////////////////////////AddVolatile/RemoveVolatile/////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>    struct add_volatile                  : Type2Type<volatile T> {};
        template<typename T>    struct add_volatile<volatile T>      : Type2Type<volatile T> {};

        template<typename T>    struct remove_volatile               : Type2Type<T> {};
        template<typename T>    struct remove_volatile<volatile T>   : Type2Type<T> {}; 

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>    struct GetRawType : public TRAITNS::remove_volatile<typename TRAITNS::remove_const<typename TRAITNS::remove_reference<T>::type>::type>  {};
    }
}


#endif // __ADDREMOVE_DETAIL_HPP__
