#ifndef __MINIMPL_TUPLEUNPACKER_HPP__
#define __MINIMPL_TUPLEUNPACKER_HPP__
/***********************************************************************************************************************
* Description         : unpack all parameter in tuple container and call specified function/functor
* Author              : Shen.Xiaolong (at Mon 10/07/2019) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <utility>

//variadic template function is not real function before it is instanced, so the template argument is not deduced
#define declare_variadic_template_function(X) struct X##_f						\
{																				\
	template<typename... TArgs> auto operator()(TArgs... args)					\
	{																			\
		return X (std::forward<TArgs>(args)...);								\
	}																			\
}

namespace MiniMPL
{
	template<typename T>
	struct tuple_Unpacker
	{
		T&	m_functor;
		tuple_Unpacker(T& f) : m_functor(f) {};		

		template<typename... TArgs>
		inline auto apply(std::tuple<> const &, TArgs&&... args)
		{
			return m_functor(std::forward<TArgs>(args)...);
		}

		template<typename... TArgs1, typename... TArgs2>
		inline auto apply(std::tuple<TArgs2...> const & ps, TArgs1&&... args)
		{
			return apply(ps._Get_rest(), std::forward<TArgs1>(args)..., std::get<0>(ps));
		}

		template<typename T1, typename... TArgs>
		inline auto apply(std::tuple<T1, TArgs...> const & ps)
		{
			return apply(ps._Get_rest(), std::get<0>(ps));
		}
	};

	template<typename T>
	inline	tuple_Unpacker<T> make_tuple_Unpacker(T& obj)
	{
		return tuple_Unpacker<T>(obj);
	}

	template<typename T,typename... TArgs>
	inline auto unpackCall(T& obj,std::tuple<TArgs...> const & ps)
	{		
		return make_tuple_Unpacker(obj).apply(ps);
	}
}

#endif // __MINIMPL_TUPLEUNPACKER_HPP__
