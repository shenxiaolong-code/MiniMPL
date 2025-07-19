
#pragma once

// ========== MLIR-like type definitions ==========

namespace mlir_demo_types {
    enum class Signedness { Signed, Unsigned };
    template<int Width, Signedness S>
    struct IntegerType {
        static void dump_symbol_info() {
            printf("IntegerType<%d, %s>\n", Width, S == Signedness::Signed ? "Signed" : "Unsigned");
        }
    };
    template<int Width>
    struct FloatType {
        static void dump_symbol_info() {
            printf("FloatType<%d>\n", Width);
        }
    };
    template<typename ElemType, int Rank>
    struct MemRefType {
        static void dump_symbol_info() {
            printf("MemRefType<ElemType, %d>\n", Rank);
            ElemType::dump_symbol_info();
        }
    };
    template<typename ElemType, int Rank>
    struct RankedTensorType {
        static void dump_symbol_info() {
            printf("RankedTensorType<ElemType, %d>\n", Rank);
            ElemType::dump_symbol_info();
        }
    };
    template<typename T1, typename T2>
    struct AddIOp {
        static void dump_symbol_info() {
            printf("AddIOp<...>\n");
            T1::dump_symbol_info();
            T2::dump_symbol_info();
        }
    };
    template<typename T1, typename T2>
    struct LoadOp {
        static void dump_symbol_info() {
            printf("LoadOp<...>\n");
            T1::dump_symbol_info();
            T2::dump_symbol_info();
        }
    };
    template<typename T1>
    struct StoreOp {
        static void dump_symbol_info() {
            printf("StoreOp<...>\n");
            T1::dump_symbol_info();
        }
    };
    template<typename T1>
    struct BranchOp {
        static void dump_symbol_info() {
            printf("BranchOp<...>\n");
            T1::dump_symbol_info();
        }
    };
}