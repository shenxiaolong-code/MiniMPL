#include <UT_material/tc_def_typeStruct.h>
#include <MiniMPL/productSpecialDef.h>
#include <MiniMPL/macroDef.h>
#include <MiniMPL/scanPrint.hpp>

namespace UnitTest
{
    using namespace std;

    S1::S1()
    {
        m_s1 = rand()%1000;    
    }

    int S1::total() const
    {
        return m_s1;
    }

    S1& S1::operator+=( S1 const& rOther )
    {
        m_s1 += rOther.m_s1;
        return *this;
    }

    S2::S2()
    {
        m_s2 = rand()%1000;    
    }

    int S2::total() const
    {
        return m_s2+m_ss1.total();
    }

    S2& S2::operator+=( S2 const& rOther )
    {
        m_s2 += rOther.m_s2;
        m_ss1 += rOther.m_ss1;
        return *this;
    }


    S3::S3()
    {
        m_s3 = rand()%1000;    
    }

    S3::~S3()
    {

    }

    int S3::total() const
    {
        return m_s3+m_ss2.total();
    }

    S3& S3::operator+=( S3 const& rOther )
    {
        m_s3 += rOther.m_s3;
        m_ss2+= rOther.m_ss2;
        return *this;
    }


    S4::S4()
    {
        m_s4    = rand()%1000;
        m_s4c   = 33+rand()%93;       //visible : 33-126
    }

    S4::~S4()
    {

    }

    void S4::print()
    {
        outputTxtV(TXT("[{%d,{%d,{%d,{%d}}}}] "),m_s4,m_ss3.m_s3,m_ss3.m_ss2.m_s2,m_ss3.m_ss2.m_ss1);    
    }

    void S4::print1Param( int iVAl )
    {
        S4 tmp=*this;
        tmp.m_s4 +=iVAl;
        printObject(tmp);
    }

    void S4::print2Params( int iVAl,char* pchVal )
    {
        print2ParamsConst(iVAl,pchVal);
    }

    void S4::print2ParamsConst( int iVAl,char* pchVal ) const
    {
        S4 tmp=*this;
        tmp.m_s4        += iVAl;
        tmp.m_ss3.m_s3  += pchVal ? *pchVal : 1;
        printObject(tmp);
    }

    void S4::print3Params( int iVAl,char* pchVal,S3 s3Val )
    {
        S4 tmp=*this;
        tmp.m_s4        += iVAl;
        tmp.m_ss3       = s3Val;
        tmp.m_ss3.m_s3  += pchVal ? *pchVal : 1;
        printObject(tmp);
    }

    void S4::printNoParam()
    {
        printObject(*this);
    }

    bool S4::compareBinaryFunction_const( int iLeft,int iRight ) const
    {
        return (iLeft+m_s4) >= iRight;
    }

    bool S4::compareBinaryFunction(int iLeft,int iRight)
    {
        return (iLeft+m_s4) >= iRight;
    }

    int S4::total() const
    {
        return m_s4+m_s4c+m_ss3.total();
    }

    S4& S4::operator+=( S4 const& rOther )
    {     
        m_s4 += rOther.m_s4;
        m_s4c += rOther.m_s4c;
        m_ss3 += rOther.m_ss3;
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CParameters1::CParameters1()
    {
        m_int   = 0;
        m_float = 0.0f;
        m_char  = '\0';    
    }

    CParameters1::CParameters1( S4 )
    {
        m_int   = 11;
        m_float = 0.0f;
        m_char  = '\0';    
    }

    CParameters1::CParameters1( int iVal )
    {
        m_int   = iVal;
        m_float = 0.0f;
        m_char  = '\0';    
    }

    CParameters1::CParameters1( float& fVal )
    {
        m_int   = 0;
        m_float = fVal;
        m_char  = '\0';    
    }

    CParameters1::CParameters1( int& iVal,char cVal )
    {
        m_int   = iVal;
        m_float = 0.0f;
        m_char  = cVal;
		iVal += 2;
    }

    void printBlockMem( S3& obj )
    {
        printObject(obj);
    }

    bool operator==( S1 const& p1,S1 const& p2 )
    {
        return p1.m_s1==p2.m_s1;
    }

    bool operator==( S3 const& p1,S4 const& p2 )
    {
        return p1 == p2.m_ss3;
    }

    bool operator<( S1 const& p1,S1 const& p2 )
    {
        return p1.m_s1 < p2.m_s1;
    }

    bool operator==( S2 const& p1,S2 const& p2 )
    {
        return (p1.m_s2==p2.m_s2) && (p1.m_ss1==p2.m_ss1);
    }
    bool operator<( S2 const& p1,S2 const& p2 )
    {
        return p1.m_s2<p2.m_s2;
    }

    bool operator==( S3 const& p1,S3 const& p2 )
    {
        return (p1.m_s3==p2.m_s3);
    }
    bool operator<( S3 const& p1,S3 const& p2 )
    {
        return p1.m_s3<p2.m_s3;
    }

    bool operator==( S4 const& p1,S4 const& p2 )
    {
        return (p1.m_s4==p2.m_s4);
    }
    bool operator<( S4 const& p1,S4 const& p2 )
    {
        return p1.m_s4 < p2.m_s4;
    }

    void printObject( S1 const& p1 )
    {
        outputTxtV(TXT("0x%p[%d] "),&p1,p1.m_s1);
    }

    void printObject( S2 const& p1 )
    {
        outputTxtV(TXT("0x%p[%d,{%d}] "),&p1,p1.m_s2,p1.m_ss1.m_s1);
    }

    void printObject( S3 const& p1 )
    {
        outputTxtV(TXT("0x%p[%d,{%d,{%d}}] "),&p1,p1.m_s3,p1.m_ss2.m_s2,p1.m_ss2.m_ss1.m_s1);
    }

    void printObject( S4 const& p1 )
    {
        outputTxtV(TXT("0x%p[%d,'%c',{%d,{%d,{%d}}}] "),&p1,p1.m_s4,p1.m_s4c,p1.m_ss3.m_s3,p1.m_ss3.m_ss2.m_s2,p1.m_ss3.m_ss2.m_ss1.m_s1);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DemoFunction3::DemoFunction3()
    {
        m_dat   = rand()%100;
    }

    void DemoFunction3::memFuncP0()
    {
    }

    void DemoFunction3::memFuncP1( int a )
    {
    }

    void DemoFunction3::memFuncP2( int a,char& b )
    {
    }

    void DemoFunction3::memFuncP3( int a,char& b,DemoFunction3 c )
    {
    }

    void DemoFunction3::memFuncP3P( int a,char& b,DemoFunction3* pC )
    {
    }

    void DemoFunction3::memFuncP4( int a,char& b,DemoFunction3 c,char* )
    {
    }

    void DemoFunction3::memFuncP5( int a,char& b,DemoFunction3 c,char*,int )
    {
    }

    structData::structData( int a )
    {
        m_a = a+2;
        m_c = a%128;
    }

    structData::structData()
    {
        m_a = rand()%1000;
        m_c = rand()%128;
    }

    structData::structData( structData const& rOther )
    {
        m_a = rOther.m_a;
        m_c = rOther.m_c;
    }

    structData::~structData()
    {
        m_a=0;
        m_c=0;
    }

    void structData::func()
    {
        outputTxtV(TXT("m_a=%d,m_c=%d"),m_a,m_c);
    }

    bool structData::operator==( structData const& rOther )
    {
        return m_a==rOther.m_a && m_c==rOther.m_c;
    }

}

namespace MiniMPL
{
    stlString toString ( UnitTest::S1 const& p1 )
    {
        stlChar buf[256]={0};
        printBuf(buf,TXT("0x%p[%d] "),&p1,p1.m_s1);
        return buf;
    }

    stlString toString ( UnitTest::S2 const& p1 )
    {
        stlChar buf[256]={0};
        printBuf(buf,TXT("0x%p[%d,{%d}] "),&p1,p1.m_s2,p1.m_ss1.m_s1);
        return buf;
    }
    stlString toString ( UnitTest::S3 const& p1 )
    {
        stlChar buf[256]={0};
        printBuf(buf,TXT("0x%p[%d,{%d,{%d}}] "),&p1,p1.m_s3,p1.m_ss2.m_s2,p1.m_ss2.m_ss1.m_s1);
        return buf;
    }
    stlString toString ( UnitTest::S4 const& p1 )
    {
        stlChar buf[256]={0};
        printBuf(buf,TXT("0x%p[%d,'%c',{%d,{%d,{%d}}}] "),&p1,p1.m_s4,p1.m_s4c,p1.m_ss3.m_s3,p1.m_ss3.m_ss2.m_s2,p1.m_ss3.m_ss2.m_ss1.m_s1);
        return buf;
    }
}


