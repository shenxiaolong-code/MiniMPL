//UT_OsBase.cpp : Defines the entry point for the console application.
#include <MiniMPL/macroDef.h>
#include <UT_material/tc_def_thread.h>

int main(int argc, char* argv[])
{ 
   TRACE_COMPILE();

   UnitTest::waitAllThreadExit(0);
   return 0;
}

