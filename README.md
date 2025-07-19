# Project Introduction
This library focuses on high-performance, zero-dependency, C++03-and-above compatible template metaprogramming infrastructure, suitable for advanced template metaprogramming, type traits, CRTP, and cross-platform infrastructure scenarios.

## Goals
1. Provide high-value foundational components for C++ template metaprogramming, with core features depending only on C++03 compilers, and no reliance on any standard or third-party libraries.
2. Offer basic system components (threading, synchronization, communication, etc.) to facilitate cross-platform application development.

The initial version of this library was developed under C++03 (VS2008) + WinCE, and all template code does not require C++11 or later standards.
- Use MiniMPL::ParamPackage to implement variadic template arguments
- Use MiniMPL::CGetType::xxx to provide type deduction for multiple input types (similar to C++11 decltype)

Full support for C++03 is being phased out, as C++11 compilers provide more concise and powerful language features. (However, variadic templates and type deduction are still available on C++03)

# MiniMPL
This library provides efficient and flexible template metaprogramming tools for large-scale C++ projects.
[Core Component] Developed since April 2009 (before C++11), project-driven, implemented in VS2008 (C++03) + WinCE, with no dependency on any standard or third-party libraries, providing high-value template metaprogramming tools:
- Non-recursive implementation of flat variadic template parameter ([paramPack.hpp](./sources/MiniMPL/include/MiniMPL/paramPack.hpp)) support, with meta-functions for deleting/inserting/updating template type packs
- Concept-based programming template meta-components ([functionParams](./sources/MiniMPL/include/MiniMPL/functionParams.hpp)), template callback support ([traverseCallbackMacro.hpp](./sources/MiniMPL/include/MiniMPL/traverseCallbackMacro.hpp))
- Templated object factory—similar to MFC's DYNAMIC_CREATE, but without requiring inheritance from a specific base class ([classRegister.hpp](./sources/MiniMPL/include/MiniMPL/classRegister.hpp))
- Meta-components for converting multi-argument functions to unary and binary functions ([unaryFunction.hpp](./sources/MiniMPL/include/MiniMPL/unaryFunction.hpp))
- Comprehensive built-in type traits for type extraction and transformation, with no dependency on standard or third-party libraries, only requiring a C++03 compiler ([addRemove.hpp](./sources/MiniMPL/include/MiniMPL/addRemove.hpp), [isXXX.hpp](./sources/MiniMPL/include/MiniMPL/isXXX.hpp), [isXXXEx.hpp](./sources/MiniMPL/include/MiniMPL/isXXXEx.hpp))
- Basic meta-programming components for enum reflection ([enumTrait](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp), [CEnumRange](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp), [CEnumValue](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp))
- Type-safe, compile-time computation, static dispatch, zero runtime overhead, traversing type containers ([traverseTypeContainer.hpp](./sources/MiniMPL/include/MiniMPL/traverseTypeContainer.hpp))
- Unified container initialization and re-initialization interfaces, not requiring C++11 ([containerInitializer.hpp](./sources/MiniMPL/include/MiniMPL/containerInitializer.hpp))
- Automatic compression of different enum values into a built-in data type, with static boundary checks and dynamic value conversion checks ([bitsetEnum.hpp](./sources/MiniMPL/include/MiniMPL/bitsetEnum.hpp))
- Multi-level data member pointers for structs, providing a generic and fast way to access data members ([memberPtr.hpp](./sources/MiniMPL/include/MiniMPL/memberPtr.hpp))
- Unified conversion interface between "any type and string" (toString/fromString), using base class static dispatch, with better performance than std::cin/std::cout ([fromToString.hpp](./sources/MiniMPL/include/MiniMPL/fromToString.hpp))
- Supporting tools for unified generation of new source code frameworks, test code frameworks, and automatic updating of test configurations ([creatNewFiles.bat](./sources/mlir-crtp-proposal/tools/creatNewFiles.bat))

After the advent of C++11, a few features based on C++11 were added, mainly to simplify code, improve performance, and readability.
You can run UT_MiniMPL in Visual Studio to check usage and examples.

## OsBase
Provides OS-based cross-platform runtime features (OsBase), offering C++ wrappers for some basic functionalities. [Non-core component, optional]
- Provides basic system wrappers such as threading, synchronization, async calls, networking, and serial ports
- Provides some common OS-based tools, such as Windows registry tools
- You can run UT_OsBase in Visual Studio to check usage and examples

## crtp_trait_bind
- Uses CRTP to demonstrate the feasibility of replacing MLIR tabgen with C++ ([1_base_crtp.hpp](./sources/mlir-crtp-proposal/1_base_crtp.hpp))
- Uses CRTP + trait bind to show how users can non-invasively enhance external platform framework features ([2_enhanced_crtp_trait_bind.hpp](./sources/mlir-crtp-proposal/2_enhanced_crtp_trait_bind.hpp))
- Uses value-type trait methods to convert arbitrarily complex long symbols into fixed-length short symbols, solving the symbol bloat problem in large-scale template projects (such as mlir) ([3_symbol_bloat_optimize.hpp](./sources/mlir-crtp-proposal/3_symbol_bloat_optimize.hpp))
- Provides symbol optimization and extensibility support for large-scale template projects such as MLIR

---

**Compatibility Note**: The library is gradually moving towards C++11 and above; some new features are only available in C++11 and above.

**Contribution & Open Source**: Contributions via issues and PRs are welcome. See [CONTRIBUTING.md](./CONTRIBUTING.md) and [LICENSE](./LICENSE) for details.

For detailed usage and examples, please refer to the [README](./README.md) in each subdirectory and the source code comments.
