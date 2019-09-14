#ifndef rand_h__
#define rand_h__
/********************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*********************************************************************/
#include <stdlib.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/swap.hpp>
#include <limits>

///////////////////////////////////// declare  ////////////////////////////////////////////////////////////////////
template<typename T>			inline T RandInRange(T a, T b);
template<typename T>			inline T RandInRange(T r);
template<typename T,int LEN>	inline bool RandSequence(T (&arr)[LEN],int iSize=LEN);

///////////////////////////////////// Implement  ////////////////////////////////////////////////////////////////////
void checkRandomSeed();	

template<typename T> inline void Rand(T& val,ENABLE_IF(!MiniMPL::isBuildinFloat<T>::value))
{
    val = T(rand())%(std::numeric_limits<T>::max)();
}
template<typename T> void inline Rand(T& val,ENABLE_IF(MiniMPL::isBuildinFloat<T>::value))
{
    val = T(rand())/255;
}

#define abs_(x)     ((x)>=0 ? (x) : -(x) )
template<typename T> inline  T RandInRange(T a, T b)
{
	checkRandomSeed();
	return  T(min(a,b) + abs_(b-a)*((rand() % 100) / 100.0 ));
}

template<typename T> inline T RandInRange(T r)
{
	return RandInRange(-r,r);
}

template<typename T,int LEN> inline bool genRandSequence(T (&arr)[LEN])
{  
    unsigned idx=LEN;
    while(idx-- >=1)
    {
        Rand(arr[idx]);
    }

    return true;
}

template<typename T,int LEN> inline bool RandSequence(T (&arr)[LEN],int iSize)
{
	ASSERT_AND_LOG(iSize<=LEN);

	while(iSize-- >1)
	{
		MiniMPL::swap(arr[RandInRange(0,LEN-1)],arr[iSize]);
	}

	return true;
}

#endif // rand_h__

