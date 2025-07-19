#ifndef __STDWRAPPER_HPP__
#define __STDWRAPPER_HPP__
/***********************************************************************************************************************
* Description         : pack some std feature to use easily. e.g. replace std::make_shared
* Author              : Shen.Xiaolong (2009-Tue ) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/stdwrapper_detail.hpp>
#include <MiniMPL/innerDetail/macro_traitimpl.hpp>
#include <MiniMPL/kitType.hpp>

namespace MiniMPL
{
#if CPP_STD >= 11
	template <typename... Ts>					struct Max_T;
	template <typename T1, typename T2>			struct Max_T<T1, T2> 	: public If_T< (sizeof(T1) > sizeof(T2)), T1, T2 >	{};
	template <typename T1, typename... Ts>		struct Max_T<T1, Ts...>	: public Max_T<T1, typename Max_T<Ts...>::type >	{};

	template <typename T1, typename T2> typename Max_T<T1,T2>::type Maxs(T1 const& p1, T2 const& p2)
	{
		return p1 > p2 ? p1 : p2;
	}

	template <typename T1, typename... Ts> typename Max_T<T1, Ts...>::type  Maxs(T1 const& p1, Ts const&... pargs)
	{
		return Maxs(p1, Maxs(pargs...));
	}

	template <typename T1, typename T2> typename Max_T<T1, T2>::type Mins(T1 const& p1, T2 const& p2)
	{
		return p1 > p2 ? p2 : p1;
	}

	template <typename T1, typename... Ts> typename Max_T<T1, Ts...>::type  Mins(T1 const& p1, Ts const&... pargs)
	{
		return Mins(p1, Mins(pargs...));
	}
#endif  // CPP_STD >= 11

	namespace StdWrapper
	{
		struct maxValue		: public InnerDetail::ValueComparer<maxValue>
		{ 
			template<typename T>  CompileValue	operator T() const { return (std::numeric_limits<T>::max)(); } 
		};		

		struct minValue		: public InnerDetail::ValueComparer<minValue>
		{ 
			template<typename T>  CompileValue	operator T() const { return (std::numeric_limits<T>::min)(); } 
		};

		struct sharedPtrGenerater	: public InnerDetail::sharedPtrGeneraterImpl		 {};	//replace std::make_shared interface except return base pointer when creating derived class object.
		struct sharedPtrArray		: public InnerDetail::sharedPtrArrayImpl			 {};		
	}	
}

static MiniMPL::StdWrapper::maxValue					_maxValue;
static MiniMPL::StdWrapper::minValue					_minValue;
static MiniMPL::StdWrapper::sharedPtrGenerater			_sharedPtrGenerater;	//it is not suitable to create derived class, return base class pointer
static MiniMPL::StdWrapper::sharedPtrArray				_sharedPtrArray;

#endif // __STDWRAPPER_HPP__
