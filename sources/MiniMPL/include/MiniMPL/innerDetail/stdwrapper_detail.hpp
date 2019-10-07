#ifndef stdwrapper_detail_h__
#define stdwrapper_detail_h__
/***********************************************************************************************************************
* Description         : pack implement detail for stdwrapper_detail.hpp.
* Author              : Shen.Xiaolong (2009-Tue ) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/tupleUnpacker.hpp>

namespace MiniMPL
{
	namespace StdWrapper
	{
		namespace InnerDetail
		{
			template<typename T>
			struct newObjectGenerater
			{
				template<typename... TArgs>
				T* operator()(TArgs&&... args)
				{
					return new T(std::forward<TArgs>(args)...);
				}
			};

			template<typename ... TArgs>
			struct tupleParameterTransfer
			{
				std::tuple<TArgs...>						m_arg;
				tupleParameterTransfer(TArgs&&... args) :	m_arg(std::forward<TArgs>(args)...) {};

				template<typename T> operator std::shared_ptr<T>()
				{
					return std::shared_ptr<T>(unpackCall(newObjectGenerater<T>(), m_arg));
				}
			};

			//////////////////////////////////////////////////////////////////////////
			struct sharedPtrGeneraterImpl
			{
				template<typename T>
				operator std::shared_ptr<T>()
				{
					return std::shared_ptr<T>(new T());
				}

				template<typename ... TArgs>
				tupleParameterTransfer<TArgs...> operator()(TArgs&&... args)
				{
					return tupleParameterTransfer<TArgs...>(std::forward<TArgs>(args)...);
				}
			};

			struct sharedPtrArrayImpl
			{
				struct arrayInfo
				{
					size_t	m_iSize;
					arrayInfo(size_t iSize) :m_iSize(iSize) {};

					template<typename T> operator std::shared_ptr<T>()
					{
						return std::shared_ptr<T>(new T[m_iSize](), [](T* p) { delete[] p; });
					}
				};

				arrayInfo operator()(size_t iSize) { return arrayInfo(iSize); }
			};
		}
	}
}

#endif // stdwrapper_detail_h__
