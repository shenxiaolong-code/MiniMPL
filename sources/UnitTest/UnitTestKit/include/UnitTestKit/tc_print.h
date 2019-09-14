#ifndef TC_PRINT_H__
#define TC_PRINT_H__
/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	print one container
*************************************************************************************/
#include <MiniMPL\fromToString.hpp>

namespace MiniMPL
{
    template<typename Stl_T> struct TContainer;
}

namespace UnitTest
{
    template<typename T>
    struct TMoveIterator
    {
        template<typename TIterator>
        static TIterator execute(TIterator& rIt,size_t pos)
        {
            for (size_t idx=0;idx<pos;++idx)
            {
                rIt++;
            }

            return rIt;
        }
    };
    template<typename T>
    struct TMoveIterator<stlVector<T> >
    {
        template<typename TIterator>
        static TIterator execute(TIterator& rIt,size_t pos)
        {
            return rIt+pos;
        }
    };
    template<typename T>
    struct TMoveIterator<::MiniMPL::TContainer<T> >
    {
        template<typename TIterator>
        static TIterator execute(TIterator& rIt,size_t pos)
        {
            return rIt+pos;
        }
    };

    template<typename T>
    typename MiniMPL::SameConst<typename T::reference,T>::type randomAccess(T& rContainer,size_t pos)
    {    
        ChkExceptionb(pos<rContainer.size());
        return *TMoveIterator<T>::execute(rContainer.begin(),pos);
    }

    template<typename T>
    void printContainer(T& rContainer,char const* pInfo=NULL)
    {   
        using namespace MiniMPL;
        using namespace UnitTest;
        if (pInfo)
        {
            outputTxt(pInfo);
        }

        for(typename T::iterator idx=rContainer.begin();idx != rContainer.end();++idx)
        {
            stlString str=toString(*idx);
            int iPos= str.find('%');  // % has special meaning when parse format
            while(-1!=iPos)
            {
                str.insert(iPos,1,'%');
                iPos = str.find('%',iPos+2);
            }
            outputTxt((str+TXT(" ")).c_str());
        }
        outputTxt(TXT("\n"));
    }
}

#endif // TC_PRINT_H__
