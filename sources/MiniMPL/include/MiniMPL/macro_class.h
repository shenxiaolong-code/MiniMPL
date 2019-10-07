#ifndef __MACRO_CLASS_H__
#define __MACRO_CLASS_H__
/***********************************************************************************************************************
* Description         :
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/libConfig.h>

#define Disable_Class_Default_Constructor(x)	private:  x ( )
#define Disable_Class_Copy_Constructor(x)		private:  x ( x const& rOther )
#define Disable_Class_Assign(x)					private:  x & operator=( x const& rOther)

#define _ZeroMemory(Destination,Length)			memset((Destination),0,(Length))
template<typename T>							char _fDummy(T const*);

#define ZeroThis()								_ZeroMemory(this,sizeof(*this));
#define ZeroThisNo(B)							typedef char (_pDummy)[sizeof(_fDummy<B>(this))]; _ZeroMemory(this,sizeof(*this)-sizeof(B))
#define ZeroThisUntil(M)						_ZeroMemory(this,(char*)&M-(char*)this)			//offsetof(S,M)
#define ZeroArray(x)							_ZeroMemory(x,sizeof(x))

#endif // __MACRO_CLASS_H__
