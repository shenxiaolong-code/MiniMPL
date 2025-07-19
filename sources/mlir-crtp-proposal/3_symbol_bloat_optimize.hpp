#pragma once
#include <cstdint>
#include <type_traits>
#include <cstdio>
#include <typeinfo>
#include <cstring>
#include <mpl_api.hpp>

// ========== SimpleTypeRegister main template ==========
template<uint64_t type_id>  struct SimpleTypeRegister;

// ========== ComplexTypeRegister template family ==========
template <template <uint64_t type_id> class TypeFetcher>
struct TypeFetcherRegister 
{
    template<uint64_t type_id>  struct apply_type_id : public TypeFetcher<type_id> {};
};

template <typename Enum, Enum eVal> struct RegisteredTypeFetcher;

template <typename Enum, Enum eVal>  struct ComplexTypeRegister {
    template<uint64_t type_id> using apply_type_id = typename RegisteredTypeFetcher<Enum, eVal>::template apply_type_id<type_id>;
};

// ========== dump_xxx_info implementations ==========
template <typename T>
__attribute__((noinline)) void dump_type_info_simple_raw() {
    TRACE_SRC("dump_raw_type_info");
    printf("[RawTypeInfo] pretty: %s\n", __PRETTY_FUNCTION__);
    printf("[RawTypeInfo] function symbol: %s, length: %zu\n", __func__, strlen(__func__));
    T::dump_symbol_info();
    printf("\n");
}
template <uint64_t type_id>
__attribute__((noinline)) void dump_type_info_simple_optimized() {
    TRACE_SRC("dump_optimized_type_info");
    printf("[OptimizedTypeInfo] pretty: %s\n", __PRETTY_FUNCTION__);
    using T = typename SimpleTypeRegister<type_id>::type;    
    printf("[OptimizedTypeInfo] function symbol: %s, length: %zu\n", __func__, strlen(__func__));    
    dump_type_info_simple_raw<T>();
}
template <typename T>
__attribute__((noinline)) void dump_type_info_complex_raw() {
    TRACE_SRC("dump_type_info_complex_raw");
    printf("[ComplexRawTypeInfo] pretty: %s\n", __PRETTY_FUNCTION__);
    printf("[ComplexRawTypeInfo] function symbol: %s, length: %zu\n", __func__, strlen(__func__));
    T::dump_symbol_info();
    printf("\n");
}
template <typename Enum, Enum eVal , uint64_t type_id> 
__attribute__((noinline)) void dump_type_info_complex_optimized() {
    TRACE_SRC("dump_type_info_complex_optimized");
    printf("[ComplexOptimizedTypeInfo] pretty: %s\n", __PRETTY_FUNCTION__);
    using T = typename ComplexTypeRegister<Enum, eVal>::template apply_type_id<type_id>::type;
    printf("[ComplexOptimizedTypeInfo] function symbol: %s, length: %zu\n", __func__, strlen(__func__));
    dump_type_info_complex_raw<T>();
}