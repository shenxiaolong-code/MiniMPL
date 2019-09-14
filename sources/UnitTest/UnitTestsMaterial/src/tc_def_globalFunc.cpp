#include <UT_material/tc_def_globalFunc.h>
#include <MiniMPL\macroDef.h>

namespace UnitTest
{
    using namespace std;

    int testParam0()
    {
        return 0;
    }

    int testParam1( MFStruct0_6& a1 )
    {
        return 1;
    }

    int testParam2( MFStruct0_6& a1,char c2 )
    {
        return 2;
    }

    int testParam3( MFStruct0_6& a1,char c2,char* s3 )
    {
        return 3;
    }

    int testParam4( MFStruct0_6& a1,char c2,char* s3,int a4 )
    {
        return 4;
    }

    int testParam5( MFStruct0_6& a1,char c2,char* s3,int a4,float f5 )
    {
        return 5;
    }

    S3 getS3FromS4( S4& rS4 )
    {
        return rS4.m_ss3;
    }

    S3& getS3FromS4Ref( S4& rS4 )
    {
        return rS4.m_ss3;
    }

    int getIntFromS3Ref( S3& rS3 )
    {
        return rS3.m_s3;
    }

    bool CallBackRoutineF()
    {
#if 1==USE_UNICODE_STRING
        wcout << TXT("I am ") << HEREINFO() << endl;
#else
        cout << TXT("I am ") << HEREINFO() << endl;
#endif

        return true;
    }

    bool CallBackRoutineF1( S4& obj )
    {
        obj.printNoParam();
        return true;
    }

    bool CallBackRoutineF2( S4& obj,int& b )
    {
        obj.printNoParam();
        return true;
    }

    bool CallBackRoutineF3( S4& obj,int b,char* pChar )
    {
        obj.printNoParam();
        return true;
    }

    void funcP1( int a )
    {
    }

    void funcP2( int a,char& b )
    {
    }

    void funcP3( int a,char& b,DemoFunction3 c )
    {
    }

    void funcP3P( int a,char& b,stlSmartptr<DemoFunction3> pC )
    {
    }

    void funcP4( int a,char& b,DemoFunction3 c,char* )
    {
    }

    void funcP5( int a,char& b,DemoFunction3 c,char*,int )
    {
    }

    bool testPointer2CPointer( int* pInt,float* fFloat )
    {
        return *pInt > *fFloat;
    }

}