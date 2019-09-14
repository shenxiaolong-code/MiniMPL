////////////////////////////////////////////////////////////////////////////////
// The Loki Library
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
#ifndef LOKI_TYPELIST_INC_
#define LOKI_TYPELIST_INC_
#include <MiniMPL/typeLogic.hpp>
#include <MiniMPL/isXXXEx.hpp>

// $Id: Typelist.h 749 2006-10-17 19:49:26Z syntheticpp $

namespace MiniMPL/*Loki*/     //keep accordant namespace, Copyright belongs to Andrei
{
    ////////////////////////////////////////////////////////////////////////////////
    // class template Typelist
    // The building block of typelists of any length
    // Use it through the LOKI_TYPELIST_NN macros
    // Defines nested types:
    //     Head (first element, a non-typelist type by convention)
    //     Tail (second element, can be another typelist)
    ////////////////////////////////////////////////////////////////////////////////

    template <class T, class U>
    struct Typelist
    {
        typedef T Head;
        typedef U Tail;
    };

    template<typename T>        struct IsTypeList                   : public FalseType  {};
    template <class T, class U> struct IsTypeList<Typelist<T,U> >   : public TrueType   {};

    // Typelist utility algorithms
    namespace TL
    {

        ////////////////////////////////////////////////////////////////////////////////
        // class template MakeTypelist
        // Takes a number of arguments equal to its numeric suffix
        // The arguments are type names.
        // MakeTypelist<T1, T2, ...>::type
        // returns a typelist that is of T1, T2, ...
        ////////////////////////////////////////////////////////////////////////////////

        template
            <   
            typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
            typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
            typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
            typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
            typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
            typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
            > 
        struct MakeTypelist : public Type2Type<Typelist<T1,typename MakeTypelist<T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>::type> >{};
        template<> struct MakeTypelist<> : public Type2Type<NullType> {};

        ////////////////////////////////////////////////////////////////////////////////
        // class template Length
        // Computes the length of a typelist
        // Invocation (TList is a typelist):
        // Length<TList>::value
        // returns a compile-time constant containing the length of TList, not counting
        //     the end terminator (which by convention is NullType)
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList> struct Length;
        template <> struct Length<NullType> : public Int2Type<0>{};

        template <class T, class U>
        struct Length< Typelist<T, U> > : public Int2Type<1 + Length<U>::value>{};

        ////////////////////////////////////////////////////////////////////////////////
        // class template TypeAt
        // Finds the type at a given index in a typelist
        // Invocation (TList is a typelist and index is a compile-time integral 
        //     constant):
        // TypeAt<TList, index>::type
        // returns the type in position 'index' in TList
        // If you pass an out-of-bounds index, the result is a compile-time error
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, unsigned int index> struct TypeAt;

        template <class Head, class Tail>
        struct TypeAt<Typelist<Head, Tail>, 0> : public Type2Type<Head>{};

        template <class Head, class Tail, unsigned int i>
        struct TypeAt<Typelist<Head, Tail>, i> : public Type2Type<typename TypeAt<Tail, i - 1>::type>{};

        ////////////////////////////////////////////////////////////////////////////////
        // class template TypeAtNonStrict
        // Finds the type at a given index in a typelist
        // Invocations (TList is a typelist and index is a compile-time integral 
        //     constant):
        // a) TypeAt<TList, index>::type
        // returns the type in position 'index' in TList, or NullType if index is 
        //     out-of-bounds
        // b) TypeAt<TList, index, D>::type
        // returns the type in position 'index' in TList, or D if index is out-of-bounds
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, unsigned int index,typename DefaultType = NullType>
        struct TypeAtNonStrict : public Type2Type<DefaultType>{};

        template <class Head, class Tail, typename DefaultType>
        struct TypeAtNonStrict<Typelist<Head, Tail>, 0, DefaultType>: public Type2Type<Head>{};

        template <class Head, class Tail, unsigned int i, typename DefaultType>
        struct TypeAtNonStrict<Typelist<Head, Tail>, i, DefaultType>: public Type2Type<typename TypeAtNonStrict<Tail, i - 1, DefaultType>::type>{};

        ////////////////////////////////////////////////////////////////////////////////
        // class template IndexOf
        // Finds the index of a type in a typelist
        // Invocation (TList is a typelist and T is a type):
        // IndexOf<TList, T>::value
        // returns the position of T in TList, or NullType if T is not found in TList
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T> struct IndexOf;

        template <class T>
        struct IndexOf<NullType, T> : public Int2Type<-1>{};

        template <class T, class Tail>
        struct IndexOf<Typelist<T, Tail>, T>: public Int2Type<0>{};

        template <class Head, class Tail, class T>
        struct IndexOf<Typelist<Head, Tail>, T>
        {
        private:
            enum { temp = IndexOf<Tail, T>::value };
        public:
            enum { value = (temp == -1 ? -1 : 1 + temp) };
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //test whether type is in TypeList
        template<typename L,typename T>        struct TypeInList                    : public IsSameRawType<L,T>     {};    
        template <class H, class U,typename T> struct TypeInList<Typelist<H,U>,T>   : public BoolType<-1!=IndexOf<Typelist<H,U>,T>::value> {};

        ////////////////////////////////////////////////////////////////////////////////
        // class template Append
        // Appends a type or a typelist to another
        // Invocation (TList is a typelist and T is either a type or a typelist):
        // Append<TList, T>::type
        // returns a typelist that is TList followed by T and NullType-terminated
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T> struct Append;        
        template <> struct Append<NullType, NullType>   : public Type2Type <NullType> {};        
        template <class T> struct Append<NullType, T>   : public Type2Type <Typelist<T,NullType> > {}; 
        template <class Head, class Tail>
        struct Append<NullType, Typelist<Head, Tail> >  : public Type2Type <Typelist<Head, Tail> > {};

        template <class Head, class Tail, class T>
        struct Append<Typelist<Head, Tail>, T> : public Type2Type <Typelist<Head,typename Append<Tail, T>::type> > {};

        ////////////////////////////////////////////////////////////////////////////////
        // class template Erase
        // Erases the first occurence, if any, of a type in a typelist
        // Invocation (TList is a typelist and T is a type):
        // Erase<TList, T>::type
        // returns a typelist that is TList without the first occurence of T
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T> struct Erase;         
        template <class T>                         // Specialization 1
        struct Erase<NullType, T>           : public Type2Type <NullType> {};
        template <class T, class Tail>             // Specialization 2
        struct Erase<Typelist<T, Tail>, T>  : public Type2Type <Tail> {};
        template <class Head, class Tail, class T> // Specialization 3
        struct Erase<Typelist<Head, Tail>, T>: public Type2Type <Typelist<Head,typename Erase<Tail, T>::type> > {};
        template<typename Head1,typename Tail1,typename Head2,typename Tail2>
        struct Erase<Typelist<Head1,Tail1>,Typelist<Head2,Tail2> > 
            : public Type2Type<typename Erase<typename Erase<Typelist<Head1,Tail1>,Head2>::type ,Tail2 >::type >{};

        ////////////////////////////////////////////////////////////////////////////////
        // class template EraseAll
        // Erases all first occurences, if any, of a type in a typelist
        // Invocation (TList is a typelist and T is a type):
        // EraseAll<TList, T>::type
        // returns a typelist that is TList without any occurence of T
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T> struct EraseAll;
        template <class T>
        struct EraseAll<NullType, T>            : public Type2Type <NullType> {};
        template <class T, class Tail>  // Go all the way down the list removing the type
        struct EraseAll<Typelist<T, Tail>, T>   : public Type2Type <typename EraseAll<Tail, T>::type> {}; 
        template <class Head, class Tail, class T>  // Go all the way down the list removing the type
        struct EraseAll<Typelist<Head, Tail>, T>: public Type2Type <Typelist<Head,typename EraseAll<Tail, T>::type> > {}; 

        ////////////////////////////////////////////////////////////////////////////////
        // class template NoDuplicates
        // Removes all duplicate types in a typelist
        // Invocation (TList is a typelist):
        // NoDuplicates<TList, T>::type
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList> struct NoDuplicates;

        template <> struct NoDuplicates<NullType>: public Type2Type <NullType> {};
        template <class Head, class Tail>
        struct NoDuplicates< Typelist<Head, Tail> >
        {
        private:
            typedef typename NoDuplicates<Tail>::type       L1;
            typedef typename Erase<L1, Head>::type          L2;
        public:
            typedef Typelist<Head, L2> type;
        };

        ////////////////////////////////////////////////////////////////////////////////
        // class template Replace
        // Replaces the first occurence of a type in a typelist, with another type
        // Invocation (TList is a typelist, T, U are types):
        // Replace<TList, T, U>::type
        // returns a typelist in which the first occurence of T is replaced with U
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T, class U> struct Replace;

        template <class T, class U>
        struct Replace<NullType, T, U>: public Type2Type <NullType> {};
        template <class T, class Tail, class U>
        struct Replace<Typelist<T, Tail>, T, U>: public Type2Type <Typelist<U, Tail> > {};
        template <class Head, class Tail, class T, class U>
        struct Replace<Typelist<Head, Tail>, T, U>: public Type2Type <Typelist<Head,typename Replace<Tail, T, U>::type> > {};

        ////////////////////////////////////////////////////////////////////////////////
        // class template ReplaceAll
        // Replaces all occurences of a type in a typelist, with another type
        // Invocation (TList is a typelist, T, U are types):
        // Replace<TList, T, U>::type
        // returns a typelist in which all occurences of T is replaced with U
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T, class U> struct ReplaceAll;
        template <class T, class U>
        struct ReplaceAll<NullType, T, U>           : public Type2Type <NullType> {};
        template <class T, class Tail, class U>
        struct ReplaceAll<Typelist<T, Tail>, T, U>  : public Type2Type <Typelist<U, typename ReplaceAll<Tail, T, U>::type> > {};        
        template <class Head, class Tail, class T, class U>
        struct ReplaceAll<Typelist<Head, Tail>, T, U>: public Type2Type <Typelist<Head,typename ReplaceAll<Tail, T, U>::type> > {};

        ////////////////////////////////////////////////////////////////////////////////
        // class template Reverse
        // Reverses a typelist
        // Invocation (TList is a typelist):
        // Reverse<TList>::type
        // returns a typelist that is TList reversed
        ////////////////////////////////////////////////////////////////////////////////

        template <class TList> struct Reverse;

        template <>
        struct Reverse<NullType>: public Type2Type <NullType> {};        
        template <class Head, class Tail>
        struct Reverse< Typelist<Head, Tail> >: public Type2Type <typename Append<typename Reverse<Tail>::type, Head>::type> {};
    }   // namespace TL
}   // namespace Loki


#endif // end file guardian

