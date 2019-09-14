#ifndef test_data_def_h__
#define test_data_def_h__
/********************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	data structure for test 
*********************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Test Data Structure Definition////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <MiniMPL/libconfig.h>
#include <iostream>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/fromToString.hpp>
#include <MiniMPL/containerInitializer.hpp>

#define ContainerSize10        10
#define ContainerSize20        20

//extern volatile __enative_startup_state __native_startup_state;

#if 1==USE_UNICODE_STRING
   static  std::wostream& tout = std::wcout;    
#else
   static  std::ostream& tout =  std::cout;     
#endif

namespace UnitTest
{
    struct MFStruct0_6
    {
        MFStruct0_6()                                                               {   m_I = 0;  };
        MFStruct0_6(MFStruct0_6& a1)                                                {   m_I = 1;  };
        MFStruct0_6(MFStruct0_6& a1,char c2)                                        {   m_I = 2;  };
        MFStruct0_6(MFStruct0_6& a1,char c2,char* s3)                               {   m_I = 3;  };
        MFStruct0_6(MFStruct0_6& a1,char c2,char* s3,int a4)                        {   m_I = 4;  };
        MFStruct0_6(MFStruct0_6& a1,char c2,char* s3,int a4,float f5)               {   m_I = 5;  };
        MFStruct0_6(MFStruct0_6& a1,char c2,char* s3,int a4,float f5, double d6)    {   m_I = 6;  };

        int testMFParam0()                                                          {   return 0;  };
        int testMFParam1(char c2)                                                   {   return 1;  };
        int testMFParam2(char c2,char* s3)                                          {   return 2;  };
        int testMFParam3(char c2,char* s3,int a4)                                   {   return 3;  };
        int testMFParam4(char c2,char* s3,int a4,float f5)                          {   return 4;  };
        int testMFParam5(char c2,char* s3,int a4,float f5, double d6)               {   return 5;  };

        int m_I;
    };

    struct ConstStruct
    {
        ConstStruct()
        {
            MiniMPL::makeInitializer(m_Chars)='1','2','3','4','5','6','7';
        }

        int m_a;
        std::vector<char>  m_Chars;
    };

    struct structData
    {
        typedef int int_T;

        int		m_a;
        char    m_c;
        structData(int a);
        structData();
        structData(structData const& rOther);
        ~structData();
        void func();
        bool operator==(structData const& rOther);
    };

    struct S1
    {
        S1();
        int total() const;
        S1& operator+=(S1 const& rOther);
        int m_s1;
    };
    bool operator==(S1 const& p1,S1 const& p2);
    bool operator<(S1 const& p1,S1 const& p2); 
    void printObject(S1 const& p1);

    struct S2
    {
        S2();
        S1	m_ss1;
        int m_s2;
        int total() const;
        S2& operator+=(S2 const& rOther);
    };
    bool operator==(S2 const& p1,S2 const& p2);
    bool operator<(S2 const& p1,S2 const& p2); 
    void printObject(S2 const& p1);

    struct S3
    {
        S3();
        ~S3();
        int m_s3;
        S2	m_ss2;

        S3& operator+=(S3 const& rOther);

        int total() const;
    };
    bool operator==(S3 const& p1,S3 const& p2); 
    bool operator<(S3 const& p1,S3 const& p2); 
    void printObject(S3 const& p1);

    struct S4
    {
        S4(); 
        ~S4();
        int total() const;

        S4& operator+=(S4 const& rOther);

        void print();
        void print1Param(int iVAl); 
        void print2Params(int iVAl,char* pchVal); 
        void print2ParamsConst(int iVAl,char* pchVal) const; 
        void print3Params(int iVAl,char* pchVal,S3 s3Val); 
        void printNoParam();
        bool compareBinaryFunction_const(int iLeft,int iRight) const;
        bool compareBinaryFunction(int iLeft,int iRight);

        char    m_s4c;
        S3	    m_ss3;
        int     m_s4;
    };
    bool operator==(S3 const& p1,S4 const& p2); 
    bool operator==(S4 const& p1,S4 const& p2); 
    bool operator<(S4 const& p1,S4 const& p2); 
    void printObject(S4 const& p1);

    struct S5: public S4
    {};

    template <typename T>
    void printObject(T* p) { if(p) printObject(*p); else outputTxt(TXT("[NULL] ")); };

	template <typename T>
	void printBuildData(T p) { std::cout<<p<<" "; };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //binary function
    template<typename S>    bool  binSN1N2(S l, S r)                    { return l < r ;} ; 
    template<typename S>    bool  binSN1R2(S l, S& r)                   { return l < r ;} ; 
    template<typename S>    bool  binSR1R2(S& l, S& r)                  { return l < r ;} ; 
    template<typename S>    bool  binSCR1R2(S const& l, S& r)           { return l < r ;} ;  
    template<typename S>    bool  binSCR1C2(S const& l, const S r)      { return l < r ;} ; 

    //unary
    template<typename S>    bool  unaryObjN(S l)                        { return l.total() < 1500 ;}
    template<typename S>    bool  unaryObjR(S& r)                       { return l.total() < 1500 ;}
    template<typename S>    bool  unaryObjRC(S const& l)                { return l.total() < 1500 ;}
    template<typename S>    bool  unaryObjC(const S r)                  { return l.total() < 1500 ;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct CParameters1
    {
        CParameters1();
        CParameters1(S4);

        explicit CParameters1(int iVal);;
        explicit CParameters1(float& fVal);;
        explicit CParameters1(int& iVal,char cVal);;

        int     m_int;
        float   m_float;
        char    m_char;
    };

    struct DemoFunction3
    { 
        DemoFunction3();
        void memFuncP0();
        void memFuncP1(int a);
        void memFuncP2(int a,char& b);
        void memFuncP3(int a,char& b,DemoFunction3 c);
        void memFuncP3P(int a,char& b,DemoFunction3* pC);
        void memFuncP4(int a,char& b,DemoFunction3 c,char*);
        void memFuncP5(int a,char& b,DemoFunction3 c,char*,int);

        int     m_dat;
    };
}

namespace MiniMPL
{                
    stlString toString (UnitTest::S1 const& p1);
    stlString toString (UnitTest::S2 const& p1);
    stlString toString (UnitTest::S3 const& p1);
    stlString toString (UnitTest::S4 const& p1);
}

#endif // test_data_def_h__
