#ifndef __CLASSOBJECTCREATER_HPP__
#define __CLASSOBJECTCREATER_HPP__
/***********************************************************************************************************************
* Description         : ClassRegister/ClassRegisterEx user interfaces, simply usage.
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL/innerDetail/classObjectCreater_detail.hpp>

namespace MiniMPL
{
    //search ClassRegister interface 
    template<typename B>                        ClassRegisterEx<B>* getClassRegisterByName(stlString const& sClsName); 
    template<typename B,typename K>             ClassRegisterEx<B>* getClassRegisterByTraitType(unsigned int iNo=0); 
    template<typename B,typename K>             ClassRegisterEx<B>* getClassRegister(const K&);
    template<typename B,typename S,typename K>  ClassRegisterEx<B>* getClassRegister(K const& kVal,bool (*IsIt)(S, K const&));
    template<typename B,typename S,typename M>  ClassRegisterEx<B>* getClassRegister(M const& CmpKey,M S::* pMember,bool (*IsIt)(M const&,M const&));	//MPTR: Pointer_to_Member type, e.g.MemberPtrImpl 

    //create object interface
    template<typename B,typename K> 
    inline B* createObject(K const& CmpKey)
    {    
        return createObjectImpl(getClassRegister<B>(CmpKey));
    }

    template<typename B>
    inline B* createObjectByName(const  stlString& strClassName )
    {  
        return createObjectImpl(getClassRegisterByName<B>(strClassName));
    }

    template<typename B,typename K>
    inline B* createObjectByTraitType()
    {
        return createObjectImpl(getClassRegisterByTraitType<B,K>());
    }

    template<typename B,typename K,typename F> 
    inline B* createObject(K const& CmpKey,F IsIt)
    {
        return createObjectImpl(getClassRegister<B>(CmpKey,IsIt));
    }

    template<typename B,typename S,typename M>
    inline B* createObject(M const& CmpKey,M S::* pMember)
    {
        return createObjectImpl(getClassRegister<B>(CmpKey,pMember,&equal<M,M>));
    }

    //////////////////////////////////////////statistics interface/////////////////////////////////////
    template<typename B,typename S>
    inline unsigned int getClassRegisterNumberByTraitType()
    {
        unsigned int iSum = 0;
        ClassRegisterEx<B>*  pList   = ClassRegisterEx<B>::m_pHeaderEx;
        while(NULL!=pList)
        {     
            if (pList->isTraitType<S>())
                iSum++;

            pList   = pList->m_pNextClassEx;
        }
        return iSum;
    }

    //dump all (dump<void>)  or specified user class (dump<userBaseClass>).
    template<typename T>    inline void dump()
    {
        typedef RAWTYPE(T)  TP;

        typename ClassListHead<TP>::type pNode = *(ClassListHead<TP>::value);
        while(pNode)
        {
            pNode->dump();
            pNode   = pNode->*(ClassListNext<TP>::value);
        }
        TRACE_INFO((TXT("\n")));
    }
}


#endif // __CLASSOBJECTCREATER_HPP__
