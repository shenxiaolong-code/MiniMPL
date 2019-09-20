#ifndef __STDWRAPPER_HPP__
#define __STDWRAPPER_HPP__
/***********************************************************************************************************************
* Description         : pack some std feature to use easily.
* Author              : Shen.Xiaolong (2009-Tue ) , xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <limits>
#include <MiniMPL/innerDetail/macro_traitimpl.hpp>

namespace MiniMPL
{
	namespace StdWrapper
	{
		struct MaxValue				{ template<typename T>  CompileValue	     operator T() { return (std::numeric_limits<T>::max)(); } };
		struct MinValue				{ template<typename T>  CompileValue	     operator T() { return (std::numeric_limits<T>::min)(); } };
		
		struct sharedPtrGenerater   { template<typename T>  operator STDTRNS::shared_ptr<T>() { return STDTRNS::shared_ptr<T>(new T()); } };
		struct sharedPtrArray
		{
			struct arrayInfo
			{
				size_t	m_iSize;
				arrayInfo(size_t iSize) :m_iSize(iSize) {};

				template<typename T> operator STDTRNS::shared_ptr<T>()
				{
					return STDTRNS::shared_ptr<T>(new T[m_iSize](), [](T* p) { delete[] p; });
				}
			};
			arrayInfo operator()(size_t iSize) { return arrayInfo(iSize); }
		};
	}
}

static MiniMPL::StdWrapper::MaxValue					_maxValue;
static MiniMPL::StdWrapper::MinValue					_minValue;

static MiniMPL::StdWrapper::sharedPtrGenerater			_sharedPtrGenerater;
static MiniMPL::StdWrapper::sharedPtrArray				_sharedPtrArray;

#endif // __STDWRAPPER_HPP__
