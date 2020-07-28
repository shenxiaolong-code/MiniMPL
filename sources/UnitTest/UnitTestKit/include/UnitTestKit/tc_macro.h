#pragma once
#include <assert.h>
#include <sstream>
#include <debugapi.h>
#include <iostream>

#ifndef __max
    #define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
	#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef ARRAYSIZE
    #define  ARRAYSIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

//#define EnableAssert
#ifdef EnableAssert
    #define TriggerAssert(x)        if(!(x)) DebugBreak()
#else
    #define TriggerAssert(x)
#endif // EnableAssert

#define Code_Position()             std::endl << __FUNCTION__ << std::endl << __FILE__ "(" << __LINE__ << ")" << std::endl << std::endl

#define output_debugger(x)          { std::stringstream ss ; ss << x ; OutputDebugStringA(ss.str().c_str());    }
#define Output_Text(x)              if(IsDebuggerPresent()) { output_debugger(x); }  else { std::cout << x;    }

#define Check_result(x)             { bool b = (x); Output_Text("Check reulst : " << ( b ? "successfully." : "fails." ) << " | " << #x << Code_Position() );TriggerAssert(b);}
#define Verify_Parameter(x,r)       if(!(x)) { Output_Text("Fails to verify input parameter :" << #x << Code_Position() ) ; TriggerAssert(0); return r ; }
