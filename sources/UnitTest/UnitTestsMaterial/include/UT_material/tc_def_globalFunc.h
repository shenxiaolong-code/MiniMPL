#ifndef TC_DEF_GLOBALFUNC_H__
#define TC_DEF_GLOBALFUNC_H__

/************************************************************************************
	author:		Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
	purpose:	
*************************************************************************************/
#include <UT_material/tc_def_typeStruct.h>

namespace UnitTest
{
    int testParam0();
    int testParam1(MFStruct0_6& a1);
    int testParam2(MFStruct0_6& a1,char c2);
    int testParam3(MFStruct0_6& a1,char c2,char* s3);
    int testParam4(MFStruct0_6& a1,char c2,char* s3,int a4);
    int testParam5(MFStruct0_6& a1,char c2,char* s3,int a4,float f5);

    S3  getS3FromS4(S4& rS4);
    S3& getS3FromS4Ref(S4& rS4);
    int getIntFromS3Ref(S3& rS3);

    bool CallBackRoutineF();
    typedef   bool (*CallBackRoutineF_T)();

    bool CallBackRoutineF1(S4& obj);
    typedef   bool (*CallBackRoutineF1_T)(S4& obj);

    bool CallBackRoutineF2(S4& obj,int& b);
    typedef   bool (*CallBackRoutineF2_T)(S4& obj,int& b);


    bool CallBackRoutineF3(S4& obj,int b,char* pChar);
    typedef   bool (*CallBackRoutineF3_T)(S4& obj,int b,char* pChar);

    void funcP1(int a);

    void funcP2(int a,char& b);

    void funcP3(int a,char& b,DemoFunction3 c);

    void funcP3P(int a,char& b,stlSmartptr<DemoFunction3> pC);

    void funcP4(int a,char& b,DemoFunction3 c,char*);

    void funcP5(int a,char& b,DemoFunction3 c,char*,int);

    bool testPointer2CPointer(int* pInt,float* fFloat);


}

#endif // TC_DEF_GLOBALFUNC_H__
