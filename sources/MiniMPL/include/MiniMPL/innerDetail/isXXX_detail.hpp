#ifndef __ISXXX_DETAIL_HPP__
#define __ISXXX_DETAIL_HPP__
/***********************************************************************************************************************
* Description         : implemented for isXXX.hpp
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/macro_traitimpl.hpp>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/typeLogic.hpp>
#include <MiniMPL/InnerDetail/isFuncPointer_detail.hpp>

namespace MiniMPL
{
    namespace InnerDetail
    {
        ////////////////////////////////////////////////////IsRef interfaces /////////////////////////////////////////////////////////////////////
        template<typename T>    struct is_reference         : public FalseType {}; 
        template<typename T>    struct is_reference<T&>     : public TrueType  {};

        //////////////////////////////////////////IsConst interfaces///////////////////////////////////////////////////////////////////////////////
        //const pointer and const value     : const int* const / int const * const
        //const pointer and non-const value : int* const
        //non_const pointer and const value : int const*       / const int*    
        template<typename T>                    struct is_const                      : public FalseType {}; 
        template<typename T>                    struct is_const<const T>             : public TrueType  {};
        template<typename T>                    struct is_const<const T&>            : public TrueType  {};
        template<typename T>                    struct is_const<T const*>            : public FalseType {}; //pointer point to constant ,pointer can be moved.        
        template<typename T>                    struct is_const<T const* const>      : public TrueType  {}; //constant pointer point to constant ,pointer can't be moved.
        template<typename T>                    struct is_const<T* const>            : public TrueType  {}; //const pointer point to variable, pointer can't be moved
        template<typename T,unsigned int LEN>   struct is_const<T[LEN]>              : public FalseType {}; //array style
        template<typename T,unsigned int LEN>   struct is_const<const T[LEN]>        : public TrueType  {}; //array style
        template<typename T,unsigned int LEN>   struct is_const<T(&)[LEN]>           : public FalseType {}; //array ref style
        template<typename T,unsigned int LEN>   struct is_const<const T(&)[LEN]>     : public TrueType  {}; //array ref style

        ////////////////////////////////////////IsVolatile interfaces/////////////////////////////////////////////////////////////////////////////////
        template<typename T>    struct is_volatile                   : public FalseType {}; 
        template<typename T>    struct is_volatile<volatile T>       : public TrueType{};

        ///////////////////////////////////////////////////IsPointer interfaces /////////////////////////////////////////////////////////////////
        // IsCPointer MUST accept rule : (memberFunc/func/dataMember can't accept this "T tObj;")
        // T tObj; 
        // T* pObj = &tObj; 
        // T& rObj = *pObj; 
        template<typename T>    struct _Is_pointer                       : public FalseType {};    
        template<typename T>    struct _Is_pointer<T*>                   : public Not_T<Or_T<FunctionPointerTester<T*>,MemberFunctionPointerTester<T*> > >  {};  //replace IsFunctionPointer to resolve across include   
        template<typename T>    struct _Is_pointer<T*&>                  : public _Is_pointer<T*>  {};
        template<typename T>    struct _Is_pointer<T* const>             : public _Is_pointer<T*>  {};    
        template<typename S,typename M>    struct _Is_pointer<M S::*>    : public FalseType       {};  
    }
}


#endif // __ISXXX_DETAIL_HPP__
