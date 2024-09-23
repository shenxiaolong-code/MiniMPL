#ifndef __ADDREMOVE_HPP__
#define __ADDREMOVE_HPP__
/***********************************************************************************************************************
* Description         : add/remove qualifier : reference,const,CPointer,Volatile
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/addRemove_detail.hpp>

#define RAWTYPE(X)		typename MiniMPL::GetRawType<X>::type       // same with std::decay_t<T>

#define RT(X)           typename MiniMPL::AddRef<X>::type           //always get reference type
#define NR(X)           typename MiniMPL::RemoveRef<X>::type        //always get non-reference type
#define CT(X)           typename MiniMPL::AddConst<X>::type         //always get const type

namespace MiniMPL
{
    //////////////////////////////////AddRef/RemoveRef////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct AddRef           : public Type2Type<T&>  {};
    template<typename T>    struct AddRef<T&>       : public Type2Type<T&>  {};
    template<>              struct AddRef<void>     : public Type2Type<void>{};
    template<typename T,unsigned int LEN>   struct AddRef<T(&)[LEN]>    : public Type2Type<T(&)[LEN]>  {};
    template<typename T,unsigned int LEN>   struct AddRef<T[LEN]>       : public Type2Type<T(&)[LEN]>  {};

    template<typename T>    struct RemoveRef        : public Type2Type<T>   {};
    template<typename T>    struct RemoveRef<T&>    : public Type2Type<T>   {};
    template<>              struct RemoveRef<void>  : public Type2Type<void>{};
    template<typename T,unsigned int LEN>   struct RemoveRef<T(&)[LEN]>    : public Type2Type<T[LEN]>  {};
    template<typename T,unsigned int LEN>   struct RemoveRef<T[LEN]>       : public Type2Type<T[LEN]>  {};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct AddCPointer          : Type2Type<T*>                                 {};
    template<typename T>    struct AddCPointer<T&>      : Type2Type<T*&>                                {};
    template<typename T>    struct AddCPointer<T*&>     : Type2Type<T*&>                                {};

    template<typename T>    struct RemoveCPointer       : Type2Type<T>                                  {};
    template<typename T>    struct RemoveCPointer<T*>   : Type2Type<T>                                  {};
    template<typename T>    struct RemoveCPointer<T*&>  : Type2Type<T&>                                 {};

    //////////////////////////////////AddConst/RemoveConst///////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>                    struct AddConst                     : Type2Type<T const>    {}; 
    template<typename T>                    struct AddConst<T&>                 : Type2Type<T const&>   {}; 

    template<typename T>                    struct RemoveConst                  : Type2Type<T>          {};
    template<typename T>                    struct RemoveConst<T const>         : Type2Type<T>          {};
    template<typename T>                    struct RemoveConst<T const&>        : Type2Type<T&>         {}; 
    template<typename T>                    struct RemoveConst<T const*>        : Type2Type<T*>         {};	    //pointer point to constant ,pointer can be moved.
    template<typename T>                    struct RemoveConst<T const* const>  : Type2Type<T const*>   {};	    //pointer point to constant ,pointer can be moved.
    template<typename T,unsigned int LEN>   struct RemoveConst<const T[LEN]>    : Type2Type<T[LEN]>     {};     //array style
    template<typename T,unsigned int LEN>   struct RemoveConst<const T(&)[LEN]> : Type2Type<T (&)[LEN]> {};	    //array ref style
    template<typename T,unsigned int LEN>   struct RemoveConst<const T(*)[LEN]> : Type2Type<T (*)[LEN]> {};	    //array pointer style
    ////////////////////////////////////AddVolatile/RemoveVolatile/////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct AddVolatile                  : Type2Type<volatile T> {};
    template<typename T>    struct AddVolatile<const T>         : AddVolatile<T>        {};
    template<typename T>    struct AddVolatile<volatile T>      : Type2Type<volatile T> {};
    template<typename T>    struct AddVolatile<T&>              : Type2Type<T&> {};

    template<typename T>    struct RemoveVolatile               : Type2Type<T> {};
    template<typename T>    struct RemoveVolatile<volatile T>   : Type2Type<T> {}; 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//refer to std::decay but different with std::decay in cpp11
    template<typename T>    struct GetRawType : public RemoveVolatile<typename RemoveConst<typename RemoveRef<T>::type>::type>  {};
}


#endif // __ADDREMOVE_HPP__
