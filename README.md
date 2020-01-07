# MiniMPL
1. provide high-value basic componment for C++ meta-programming. 
 * it is the core componment in this lib.
 * run project UT_MiniMPL to check the usage and examples.
```  
   many type traits outside of std/boost, type manipulate function - addRemove.hpp/isXXX.hpp/isXXXEx.hpp/enumTrait.hpp.
   general templated object factory - classRegister.hpp
   container initializer and repeat batch assigner without C++11 compiler support - containerInitializer.hpp
   convert multiple-parameters into unary function - unaryFunction.hpp
   callback template function without C++11 compiler support - traverseCallbackMacro.hpp
   traverse type container supporter - traverseTypeContainer.hpp
   general two string convert function 'toString/fromString' for all built-type with any variant. - fromToString.hpp
   general any member collector in any type container - collector.hpp
   any object package - anyObject.hpp.
   link data member pointer - memberPtr.hpp.
   paramter package without C++11 compiler support - paramPack.hpp.
   ...   
```   

# OsBse
2. provide basic service (thread,sync and communication) for application development.
   it is not core componment. here provide some general utilities for daily development.
*  run project UT_OsBase to check the usage and examples.
*  e.g.  max general generator
```   
   MiniMPL::StdWrapper::maxValue _maxValue;
   const int iMax = _maxValue;
   AssertB((iMax == 0x7fffffff));
   const unsigned int iuMax = _maxValue;
   AssertB((iuMax == 0xffffffff));

   AssertB((_maxValue == GetMaxChar()));
   AssertB((_maxValue == GetMaxInt()));
   AssertB((_maxValue == GetAnyBuiltTypeMaxValue()));
```
*  e.g.  std::shared_ptr general generator
```   
   MiniMPL::StdWrapper::sharedPtrGenerater _sharedPtrGenerater;
   //generate different type std::shared_ptr
   std::shared_ptr<S3>	          pS3	          = _sharedPtrGenerater;
   std::shared_ptr<S4>	          pS4	          = _sharedPtrGenerater;
   std::shared_ptr<CParameters1>	pCParameters1 = _sharedPtrGenerater;

   int val = 5;
   //generate different type std::shared_ptr with differnet constructure parameter.
   std::shared_ptr<CParameters1> pCParameters2    = _sharedPtrGenerater(val);
   AssertB((5== val));
   std::shared_ptr<CParameters1> pCParameters2_1  = _sharedPtrGenerater(55);
   std::shared_ptr<CParameters1> pCParameters3    = _sharedPtrGenerater(*pS4);
   std::shared_ptr<CParameters1> pCParameters4    = _sharedPtrGenerater(val, '6');     
```   
*  e.g.  memory array general generator
``` 
   //it will call delete [] p ; when free array automatically.
   MiniMPL::StdWrapper::sharedPtrArray _sharedPtrArray;
   std::shared_ptr<int> p = _sharedPtrArray(3);
   std::shared_ptr<int[3] > p1 = _sharedPtrArray;
``` 

# other supporting tools
- UnitTestKit project  -- for unit test
- tools folder  -- provide some script tools to general templated source file framework and VCS config.
