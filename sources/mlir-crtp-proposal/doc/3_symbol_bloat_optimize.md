# Advanced Value-to-Type Binding: An Independent Solution to MLIR Symbol Bloat

**Author**: Xiaolong Shen <xlshen2002@hotmail.com>  
**Repo**: https://github.com/shenxiaolong-code/mlir-crtp-proposal  
**Date**: June 2025

[**中文版**](./3_symbol_bloat_optimize_cn.md) | **English Version**

## 🎯 Demo Purpose
This technique is an independent symbol optimization solution, unrelated to TableGen alternatives.
- Understand **value-to-type** mapping to reduce symbol length in practice
- MLIR is a major victim of template symbol bloat; this method can effectively alleviate the problem

> **🔗 Main Reference**: If you are looking for a modern C++ alternative to TableGen, see [**Enhanced CRTP + trait_binding Demo Guide**](./2_enhanced_crtp_trait_bind_demo.md). The symbol optimization technique in this document can be used as an optional enhancement.

## 🔥 The Symbol Bloat Crisis in MLIR

### Traditional MLIR Template Instantiation Problem

In current MLIR implementations, complex operations generate symbols like:
```cpp
// Traditional method - generates huge symbols
mlir::arith::AddIOp<
    mlir::IntegerType<32, mlir::Signedness::Signed>,
    mlir::MemRefType<mlir::FloatType<32>, 4>
>
```

This creates **hundreds of characters** in mangled symbols:
```
_ZN4mlir5arith6AddIOpINS_11IntegerTypeILi32ELNS_11SignednessE0EENS_10MemRefTypeINS_9FloatTypeILi32EEELi4EEEEEEvv
```

### Industrial Impact

- **Binary size**: Symbol tables in industrial MLIR apps can reach 300-500MB
- **Link time**: Grows exponentially with template complexity
- **Debugging**: Unintelligible symbol names
- **Compile speed**: Template instantiation becomes a bottleneck
- **Memory usage**: Large-scale template instantiation overhead

## 💡 Key Technique: Value-Based Type Binding

### Core Approach
- Do not use complex types as template parameters, but use **compile-time constant IDs** (e.g., uint64_t)
- Map IDs to actual types via template specialization
- Framework code remains unchanged, users only register types and specialize TypeFetcher

### Code Structure & Demo

#### 1. Complex Type Definition & Registration
```cpp
// MLIR-style complex types
using complexMLIRType_1 = AddIOp<IntegerType<32, Signedness::Signed>, MemRefType<FloatType<32>, 4>>;
using complexMLIRType_2 = LoadOp<MemRefType<IntegerType<64, Signedness::Unsigned>, 2>, RankedTensorType<FloatType<32>, 2>>;
using complexMLIRType_3 = BranchOp<RankedTensorType<IntegerType<16, Signedness::Signed>, 1>>;

// Register type ID to type
template<> struct SimpleTypeRegister<1001> : public Type2Type<complexMLIRType_1> {};
template<> struct SimpleTypeRegister<1002> : public Type2Type<complexMLIRType_2> {};
template<> struct SimpleTypeRegister<1003> : public Type2Type<complexMLIRType_3> {};
```

#### 2. Complex Type Family Registration & Grouping
```cpp
enum class OpGroup_1 : uint64_t { Arithmetic = 1 };
enum class OpGroup_2 : uint64_t { Memory = 2 };
enum class OpGroup_3 : uint64_t { Control = 3 };

// TypeFetcher registration
// ...e.g. ArithmeticTypeFetcher/MemoryTypeFetcher/ControlFlowTypeFetcher ...

// Group registration
// template<> struct RegisteredTypeFetcher<OpGroup_1, OpGroup_1::Arithmetic> : public TypeFetcherRegister<ArithmeticTypeFetcher>{};
// ...
```

#### 3. Demo & Symbol Comparison

- Directly call `dump_type_info_simple_raw<complexMLIRType_1>()` etc. to generate long template symbols.
- Use `dump_type_info_simple_optimized<1001>()` with only a short ID for a much shorter symbol.
- Use `dump_type_info_complex_optimized<OpGroup_1, OpGroup_1::Arithmetic, 1001>()` to show further shortening with group+ID.

#### 4. nm Tool Comparison

Automatically executed in the Makefile:
```makefile
nm -s ${output_dir}/3_symbol_bloat_optimize_demo | grep "dump_type_info_" | sort -t'_' -k3
```
Sample output:
```
0000000000001750 W _Z32dump_type_info_complex_optimizedI9OpGroup_1LS0_1ELm1001EEvv
0000000000001670 W _Z26dump_type_info_complex_rawIN15mlir_demo_types6AddIOpINS0_11IntegerTypeILi32ELNS0_10SignednessE0EEENS0_10MemRefTypeINS0_9FloatTypeILi32EEELi4EEEEEEvv
0000000000001600 W _Z31dump_type_info_simple_optimizedILm1003EEvv
0000000000001530 W _Z25dump_type_info_simple_rawIN15mlir_demo_types8BranchOpINS0_16RankedTensorTypeINS0_11IntegerTypeILi16ELNS0_10SignednessE0EEELi1EEEEEEvv
```
Note: For any complexity, the optimized symbol length is fixed, so the more complex the type, the more significant the optimization. (For extremely complex MLIR symbols, the effect is dramatic)

- Traditional complex type symbol length: 180+ chars. In CUDA/CUTLASS, some single symbol lengths can reach 2MB+, while after optimization, they are usually around 40 bytes—a huge improvement.
- Optimized ID-based symbol length: 30-50 chars

## ⚡ Industrial-Grade Advantages
- Zero-intrusion framework; users only register types and IDs
- Supports type families/grouping, suitable for large-scale MLIR projects
- Fully compatible with standard C++ toolchains, easy to integrate
- Directly analyzable with nm/objdump/c++filt, etc.

## 📝 Summary
- This solution has been validated in real MLIR and CUDA projects, greatly alleviating symbol bloat
- Recommended for large-scale template metaprogramming/MLIR/AI compiler projects
- See source and demo:
  - [`3_symbol_bloat_optimize_demo.cpp`](../demo/3_symbol_bloat_optimize_demo.cpp)
  - [`3_symbol_bloat_optimize.hpp`](../3_symbol_bloat_optimize.hpp)

---

*This document is part of the MLIR CRTP proposal project, exploring advanced alternatives to traditional MLIR TableGen methods.*