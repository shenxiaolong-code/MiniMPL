
////////////////////////////////////////////////////////////////////////////////
// The MiniMPL Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////
#ifndef MAKE_TYPELISTMACROS_INC_
#define MAKE_TYPELISTMACROS_INC_
#include <MiniMPL/typeList.hpp>

// $Id: TypelistMacros.h 749 2006-10-17 19:49:26Z syntheticpp $


//#define LOKI_DISABLE_TYPELIST_MACROS
#ifndef LOKI_DISABLE_TYPELIST_MACROS

////////////////////////////////////////////////////////////////////////////////
// macros MAKE_TYPELIST_1, MAKE_TYPELIST_2, ... MAKE_TYPELIST_50
// Each takes a number of arguments equal to its numeric suffix
// The arguments are type names. MAKE_TYPELIST_NN generates a typelist containing 
//     all types passed as arguments, in that order.
// Example: MAKE_TYPELIST_2(char, int) generates a type containing char and int.
////////////////////////////////////////////////////////////////////////////////

#define MAKE_TYPELIST_1(T1) ::MiniMPL::Typelist<T1, ::MiniMPL::NullType>

#define MAKE_TYPELIST_2(T1, T2) ::MiniMPL::Typelist<T1, MAKE_TYPELIST_1(T2) >

#define MAKE_TYPELIST_3(T1, T2, T3) ::MiniMPL::Typelist<T1, MAKE_TYPELIST_2(T2, T3) >

#define MAKE_TYPELIST_4(T1, T2, T3, T4) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_3(T2, T3, T4) >

#define MAKE_TYPELIST_5(T1, T2, T3, T4, T5) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_4(T2, T3, T4, T5) >

#define MAKE_TYPELIST_6(T1, T2, T3, T4, T5, T6) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_5(T2, T3, T4, T5, T6) >

#define MAKE_TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_6(T2, T3, T4, T5, T6, T7) >

#define MAKE_TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >

#define MAKE_TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >

#define MAKE_TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

#define MAKE_TYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_10(T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >

#define MAKE_TYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_11(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12) >

#define MAKE_TYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_12(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13) >

#define MAKE_TYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_13(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14) >

#define MAKE_TYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_14(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15) >

#define MAKE_TYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_15(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16) >

#define MAKE_TYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_16(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17) >

#define MAKE_TYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_17(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18) >

#define MAKE_TYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_18(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19) >

#define MAKE_TYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_19(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >

#define MAKE_TYPELIST_21(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_20(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >

#define MAKE_TYPELIST_22(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_21(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >

#define MAKE_TYPELIST_23(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_22(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >

#define MAKE_TYPELIST_24(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_23(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >

#define MAKE_TYPELIST_25(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_24(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25) >

#define MAKE_TYPELIST_26(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_25(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26) >

#define MAKE_TYPELIST_27(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_26(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27) >

#define MAKE_TYPELIST_28(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_27(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28) >

#define MAKE_TYPELIST_29(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_28(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29) >

#define MAKE_TYPELIST_30(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_29(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >

#define MAKE_TYPELIST_31(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_30(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) >

#define MAKE_TYPELIST_32(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_31(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) >

#define MAKE_TYPELIST_33(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_32(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) >

#define MAKE_TYPELIST_34(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_33(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) >

#define MAKE_TYPELIST_35(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_34(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35) >

#define MAKE_TYPELIST_36(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_35(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36) >

#define MAKE_TYPELIST_37(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_36(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37) >

#define MAKE_TYPELIST_38(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_37(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38) >

#define MAKE_TYPELIST_39(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_38(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39) >

#define MAKE_TYPELIST_40(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_39(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) >

#define MAKE_TYPELIST_41(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_40(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) >

#define MAKE_TYPELIST_42(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_41(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) >

#define MAKE_TYPELIST_43(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_42(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) >

#define MAKE_TYPELIST_44(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_43(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) >

#define MAKE_TYPELIST_45(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_44(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45) >

#define MAKE_TYPELIST_46(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_45(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46) >

#define MAKE_TYPELIST_47(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_46(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47) >

#define MAKE_TYPELIST_48(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_47(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48) >

#define MAKE_TYPELIST_49(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48, T49) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_48(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48, T49) >

#define MAKE_TYPELIST_50(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) \
    ::MiniMPL::Typelist<T1, MAKE_TYPELIST_49(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
    T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
    T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
    T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) >

#endif //LOKI_DISABLE_TYPELIST_MACROS

#endif // end file guardian

