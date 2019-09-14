#ifndef __ISXXX_HPP__
#define __ISXXX_HPP__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           :free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/isXXX_detail.hpp>

namespace MiniMPL
{
    ////////////////////////////////////////////////////IsRef interfaces /////////////////////////////////////////////////////////////////////
    template<typename T>    struct IsRef        : public TRAITNS::is_reference<T> {}; 

    //////////////////////////////////////////IsConst interfaces///////////////////////////////////////////////////////////////////////////////
    //const pointer and const value     : const int* const / int const * const
    //const pointer and non-const value : int* const
    //non_const pointer and const value : int const*       / const int*    
    template<typename T>    struct IsConst      : public TRAIT_MPL::is_const<T> {}; 

    ////////////////////////////////////////IsVolatile interfaces/////////////////////////////////////////////////////////////////////////////////
    template<typename T>    struct IsVolatile   : public TRAITNS::is_volatile<T>{}; 

    ///////////////////////////////////////////////////IsPointer interfaces /////////////////////////////////////////////////////////////////
    // IsCPointer MUST accept rule : (memberFunc/func/dataMember can't accept this "T tObj;")
    // T tObj; 
    // T* pObj = &tObj; 
    // T& rObj = *pObj; 
    template<typename T>    struct IsCPointer   : public TRAIT_MPL::_Is_pointer<T> {};    
}


#endif // __ISXXX_HPP__
