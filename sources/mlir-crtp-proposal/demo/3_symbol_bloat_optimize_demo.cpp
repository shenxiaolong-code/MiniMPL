#include <3_symbol_bloat_optimize.hpp>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <mpl_api.hpp>
#include "mlir_demo_types.h"

// =================== Advanced Value-to-Type Binding Demo ===================
// Author: Shen Xiaolong <xlshen2002@hotmail.com>
// Purpose: Demonstrate industrial-grade MLIR CRTP solutions

using namespace mlir_demo_types;
using namespace mlir_crtp;

// =================== demo simple value to type ===================
using complexMLIRType_1 = AddIOp<IntegerType<32, Signedness::Signed>, MemRefType<FloatType<32>, 4>>;
using complexMLIRType_2 = LoadOp<MemRefType<IntegerType<64, Signedness::Unsigned>, 2>, RankedTensorType<FloatType<32>, 2>>;
using complexMLIRType_3 = BranchOp<RankedTensorType<IntegerType<16, Signedness::Signed>, 1>>;


template<> struct SimpleTypeRegister<1001> : public Type2Type<complexMLIRType_1> {};
template<> struct SimpleTypeRegister<1002> : public Type2Type<complexMLIRType_2> {};
template<> struct SimpleTypeRegister<1003> : public Type2Type<complexMLIRType_3> {};

// =================== demo complex value to type ===================


using namespace mlir_demo_types;
// ========== SimpleTypeRegister specializations ==========
template<>  struct SimpleTypeRegister<2001> { using type = IntegerType<32, Signedness::Signed>; };
template<>  struct SimpleTypeRegister<2002> { using type = FloatType<32>; };
template<>  struct SimpleTypeRegister<2003> { using type = MemRefType<IntegerType<32, Signedness::Signed>, 4>; };
template<>  struct SimpleTypeRegister<2004> { using type = RankedTensorType<FloatType<32>, 2>; };

// ========== ComplexTypeRegister specializations ==========
enum class OpGroup_1 : uint64_t { Arithmetic = 1                            };
enum class OpGroup_2 : uint64_t {                 Memory = 2                };
enum class OpGroup_3 : uint64_t {                             Control = 3   };

// register type 
template <uint64_t type_id>  struct ArithmeticTypeFetcher ;
template <>                  struct ArithmeticTypeFetcher<1001> : public Type2Type<complexMLIRType_1> {};
template <>                  struct ArithmeticTypeFetcher<1002> : public Type2Type<complexMLIRType_2> {};

template <uint64_t type_id>  struct MemoryTypeFetcher ;
template <>                  struct MemoryTypeFetcher<1005>     : public Type2Type<complexMLIRType_2> {};
template <>                  struct MemoryTypeFetcher<1006>     : public Type2Type<complexMLIRType_3> {};

template <uint64_t type_id>  struct ControlFlowTypeFetcher ;
template <>                  struct ControlFlowTypeFetcher<1001> : public Type2Type<complexMLIRType_1> {};
template <>                  struct ControlFlowTypeFetcher<1008> : public Type2Type<complexMLIRType_3> {};

// register type fetchers
template<>  struct RegisteredTypeFetcher<OpGroup_1, OpGroup_1::Arithmetic> : public TypeFetcherRegister<ArithmeticTypeFetcher>{}; 
template<>  struct RegisteredTypeFetcher<OpGroup_2, OpGroup_2::Memory>     : public TypeFetcherRegister<MemoryTypeFetcher>{}; 
template<>  struct RegisteredTypeFetcher<OpGroup_3, OpGroup_3::Control>    : public TypeFetcherRegister<ControlFlowTypeFetcher>{};


void demo_simple_value_to_type()
{
    TRACE_SRC("demo_simple_value_to_type")
    std::cout << "======= Simple Value to Type Binding Demo =======" << std::endl;
    
    // Demonstrate simple value to type binding
    // std::cout << "\n=== Simple raw type ===";
    // dump_type_info_simple_raw<complexMLIRType_1>();
    // dump_type_info_simple_raw<complexMLIRType_2>();
    // dump_type_info_simple_raw<complexMLIRType_3>();
    
    // Demonstrate complex value to type binding
    std::cout << "\n=== Simple value to type optimized type ===\n";
    // dump_type_info_simple_optimized<1001>();
    // dump_type_info_simple_optimized<1002>();
    dump_type_info_simple_optimized<1003>();   

}

void demo_complex_value_to_type()
{
    TRACE_SRC("demo_complex_value_to_type")
    std::cout << "======= Complex Value to Type Binding Demo =======" << std::endl;

    // std::cout << "\n=== complex raw type ===";
    // dump_type_info_complex_raw<complexMLIRType_1>();
    // dump_type_info_complex_raw<complexMLIRType_2>();
    // dump_type_info_complex_raw<complexMLIRType_3>();
    
    // Demonstrate complex value to type binding
    std::cout << "\n=== Complex value to type optimized type ===\n";
    dump_type_info_complex_optimized<OpGroup_1, OpGroup_1::Arithmetic, 1001>();
    // dump_type_info_complex_optimized<OpGroup_1, OpGroup_1::Arithmetic, 1002>();

    // dump_type_info_complex_optimized<OpGroup_2, OpGroup_2::Memory, 1005>();
    // dump_type_info_complex_optimized<OpGroup_2, OpGroup_2::Memory, 1006>();

    // dump_type_info_complex_optimized<OpGroup_3, OpGroup_3::Control, 1001>();
    // dump_type_info_complex_optimized<OpGroup_3, OpGroup_3::Control, 1008>();
}

void demo_main()
{
    printf("=== optimize symbol bloat ===\n");
    printf("Author: Shen Xiaolong\n");
    printf("Repository: https://github.com/shenxiaolong-code/mlir-crtp-proposal\n\n");
    
    std::cout << "======= Advanced Value-to-Type Binding Demo =======" << std::endl;
    
    // Demonstrate simple value to type binding
    demo_simple_value_to_type();

    // Demonstrate complex value to type binding
    demo_complex_value_to_type();
}

// Main function must be in global namespace
int main() {
    demo_main();
}