# Valuable libs:
1. provide high-value base component for C++ meta-programming.  
2. provide C++ objects of basic services (thread, sync, and communication) for application development.

This lib begins from VS2008, all template codes needn't C++11 compiler support. initial in vs2008 :
-  use MiniMPL::ParamPackage implement the variant template.
-  use MiniMPL::CGetType::xxx to implement decltype of C++11 from multiple input types.

Now I might need to discard full VS2008 support because the C++11 compiler provides more simply&powerful features.

# MiniMPL
1. provide high-value basic componment for C++ meta-programming. 
 * it is the core componment in this lib.
 * run project UT_MiniMPL to check the usage and examples.
   - many type traits outside of std/boost, type manipulate function - addRemove.hpp/isXXX.hpp/isXXXEx.hpp/enumTrait.hpp.
   - general templated object factory - classRegister.hpp
   - container initializer and repeat batch assigner without C++11 compiler support - containerInitializer.hpp
   - convert multiple-parameters into unary function - unaryFunction.hpp
   - callback template function without C++11 compiler support - traverseCallbackMacro.hpp
   - traverse type container supporter - traverseTypeContainer.hpp
   - general two string convert function 'toString/fromString' for all built-type with any variant. - fromToString.hpp
   - general any member collector in any type container - collector.hpp
   - any object package - anyObject.hpp.
   - link data member pointer - memberPtr.hpp.
   - paramter package without C++11 compiler support - paramPack.hpp.
   ...

# OsBse
2. provide basic service (thread,sync and communication) for application development.
   it is not core componment. here provide some general utilities for daily development.
*  run project UT_OsBase to check the usage and examples.

# other supporting tools
- UnitTestKit project  -- for unit test
- tools folder  -- provide some script tools to general templated source file framework and VCS config.
