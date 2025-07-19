
#pragma once

#undef CPP_STD
#define CPP_STD 11

#include <MiniMPL/typeList_cpp11.hpp>
#include <MiniMPL/kitType.hpp>

// ========== TRACE_HERE_INFO macro ==========
#define TRACE_SRC(X) { \
    printf("[TRACE] %s:%d: %s\n", __FILE__, __LINE__, X); \
}

namespace mlir_crtp {
    
// =================== Fundamental Type Manipulation Infrastructure ===================

template <typename T>
using Type2Type = MiniMPL::Type2Type<T>;

template <typename T, T val>
using Value2Type = MiniMPL::ValueType<T, val>;

template <typename... Args>
using TypeList = MiniMPL::TypeList<Args...>; // Declaration only - size optimization

// =================== TypeList Operations ===================

// Get Nth type from TypeList
template<unsigned idx, typename TList>
using GetNthTypeInTypeList = MiniMPL::FindNthTypeInTypeList<idx, TList>;
template<unsigned idx, typename TList>
using GetNthTypeInTypeList_t = typename GetNthTypeInTypeList<idx, TList>::type;

// Replace wrapper template
template <typename T1, template <typename...> class dst>
using ReplaceWrapperTemplate = MiniMPL::ReplaceWrapperTemplate<T1, dst>;

template<unsigned idx, typename R, typename TList>
using ReplaceNthTypeInList= MiniMPL::ReplaceNthTypeInTypeList<idx, R, TList>;
template<unsigned idx, typename R, typename TList>
using ReplaceNthTypeInList_t = typename ReplaceNthTypeInList<idx, R, TList>::type;

}