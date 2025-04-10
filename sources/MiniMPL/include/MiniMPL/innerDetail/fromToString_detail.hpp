#ifndef STLSTRINGCONVERTDETAIL_H__
#define STLSTRINGCONVERTDETAIL_H__
/************************************************************************************
Description		: implement of fromToString.hpp , consist of 3 parts:
				  1. non-string variable          => string (T*,T[],stl string)
				  2. string (T*,T[],stl string)   => non-string variable
				  3. string <=> string
author			: Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose			: detail implement for fromToString.hpp
refer to:   scanf function from MSDN
*************************************************************************************/
#include <MiniMPL/libConfig.h>
#include <MiniMPL/valueCompare.hpp>
#include <MiniMPL/scanPrint.hpp>
#include <MiniMPL/addRemove.hpp>
#include <MiniMPL/kitType.hpp>
#include <MiniMPL/isXXXEx.hpp>
#include <MiniMPL/arrayTrait.hpp>
#include <limits>
#include <MiniMPL/stringtrait.hpp>

namespace MiniMPL
{
    //when one array is Degenerated to pointer, we can't capture its length
    template<typename T>    struct NoDegeneratedArray;
    template<typename T,unsigned TLEN>
    struct NoDegeneratedArray<T[TLEN]> : Type2Type<T(&)[TLEN]>
    {
        explicit NoDegeneratedArray(type arr):m_arr(arr){};
        type m_arr;
    };

    namespace InnerDetail
    {
        template<typename T>    struct IsInnerFloat
        {   
            enum {value = Or_T<IsSameRawType<T,float>,IsSameRawType<T,double>,IsSameRawType<T,long double> >::value };
        };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
        //fix bug : Run-Time Check Failure #2 - Stack around the variable 'xxx' was corrupted.
        //if data type size is lesser than sizeof(int), scanf/sscanf with format "%d" will cause that padding memory is overwritten.  
        //for example :
        void demo_Run_Time_Check_Failure_2()
        {
            short sVal=0;
            sscanf("32","%d",&sVal);
        } //Run-Time Check Failure #2 - Stack around the variable 'sVal' was corrupted when demo_Run_Time_Check_Failure_2 return
        */
        template<typename T> struct CGetScanValueType                 : public Type2Type<typename AddRef<T>::type>    {};
        template<>           struct CGetScanValueType<bool>           : public Type2Type<int>                         {};
        template<>           struct CGetScanValueType<char>           : public Type2Type<wchar_t>                     {};
        template<>           struct CGetScanValueType<signed char>    : public Type2Type<wchar_t>                     {};
        template<>           struct CGetScanValueType<unsigned char>  : public Type2Type<wchar_t>                     {};
        template<>           struct CGetScanValueType<short>          : public Type2Type<int>                         {};
        template<>           struct CGetScanValueType<unsigned short> : public Type2Type<unsigned int>                {};

        template<typename T>
        struct CScanBufSameSize : public BoolType<sizeof(T)==sizeof(typename CGetScanValueType<RAWTYPE(T)>::type)>{};
        //only for scanf(char*,signed char/unsigned char/char) , efficiency is not optimal, but result is correct.
        template<typename T,bool bSameSize=CScanBufSameSize<T>::value> struct CScanBuf;
        template<typename T> struct CScanBuf<T,true> 
        {
            typedef typename AddRef<T>::type        Buffer_T;
            CScanBuf(typename AddRef<T>::type val) : m_buf(val){};
            Buffer_T            m_buf;            
        };
        template<typename T> struct CScanBuf<T,false> 
        {
            typedef typename AddRef<T>::type                value_raw_T;
            typedef typename CGetScanValueType<T>::type     Buffer_T;

            CScanBuf(typename AddRef<T>::type val) : m_val(val){};
            ~CScanBuf(){setValue(m_buf,m_val);};

            template<typename TDst>
            void setValue(Buffer_T& src,TDst& val){ val = TDst(src);    };
            void setValue(Buffer_T& src,bool& val){ val = (0!=src);     };  //remove performance warning C4800

            Buffer_T            m_buf;
            value_raw_T         m_val;            
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename TStr>     inline bool isInvalidBuf(TStr& rStr)           { return false;                              }
        template<typename Char_T>   inline bool isInvalidBuf(Char_T const* pStr)   { return !pStr;                              }

        template<typename Char_T>   inline bool isNullStr(const stlStringPack<Char_T>& rStr) { return rStr.size()==0;           }
        template<typename Char_T>   inline bool isNullStr(Char_T const* pStr)   { return isInvalidBuf(pStr) || *pStr==Char_T('\0'); }

        template<typename TStr>     void zeroStr(TStr&){};
        template<typename Char_T>   void zeroStr(Char_T* pStr) { if (pStr) { *pStr = Char_T('\0');  }   };

        namespace ValidParamter
        {
            template<typename TStr>     struct ResultString;
            template<typename Char_T>   struct ResultString<Char_T*>
            {
                Char_T* m_pStr;
                ResultString(Char_T* pStr):m_pStr(pStr){};

                inline bool recvString(Char_T const* pFrom)
                {
                    memcpy(m_pStr,pFrom,std::char_traits<Char_T>::length(pFrom)*sizeof(Char_T));
                    return true;
                }

                inline bool recvString(stlStringPack<Char_T> const& rFrom)
                {
                    memcpy(m_pStr,rFrom.c_str(),rFrom.size()*sizeof(Char_T));
                    return true;
                }

                template<unsigned iLEN>
                inline bool recvString( const Char_T(&rFrom)[iLEN])
                {
                    memcpy(m_pStr,rFrom,iLEN*sizeof(Char_T));
                    return true;
                }
            };
            template<typename Char_T> struct ResultString<stlStringPack<Char_T>>
            {
                stlStringPack<Char_T>& m_rStr;
                ResultString(stlStringPack<Char_T>& rStr):m_rStr(rStr){};

                template<typename FromStr>
                inline bool recvString(FromStr const& pFrom)
                {
                    m_rStr = pFrom; 
                    return true;
                }
            };
            template<typename Char_T,unsigned iLEN> struct ResultString<Char_T[iLEN]>
            {
#define CheckBufTooSmall(s,b)    ASSERT_AND_LOG_INFO(((b)>(s)),(TXT("buffer is too small,String is truncated!")))

                Char_T  (&m_rStr)[iLEN];
                ResultString(Char_T (&rStr)[iLEN]):m_rStr(rStr){};

                inline bool recvString(Char_T const* pFrom)
                {
                    unsigned iSize=std::char_traits<Char_T>::length(pFrom);
                    CheckBufTooSmall(iSize,iLEN);
                    memcpy(m_rStr,pFrom,min(iSize,iLEN)*sizeof(Char_T));
                    if (iLEN>iSize)
                    {
                        m_rStr[iSize]=Char_T('\0');
                    }
                    return iLEN>=iSize;
                }
                inline bool recvString(stlStringPack<Char_T> const& rFrom)
                {
                    unsigned iSize=rFrom.size();
                    CheckBufTooSmall(iSize,iLEN);
                    memcpy(m_rStr,rFrom.c_str(),min(iSize,iLEN)*sizeof(Char_T));
                    if (iLEN>iSize)
                    {
                        m_rStr[iSize]=Char_T('\0');
                    }
                    return iLEN>=iSize;
                }
            };

            template<typename Form_T,typename To_T>
            struct Str2StrImpl
            {
                template<typename ToStr>
                static inline bool execute(Form_T const* pFrom,ToStr& rTo)
                {
                    TStlStringStream<To_T>::type ss;
                    ss << pFrom;
                    return Str2StrImpl<To_T,To_T>::execute(ss.str(),rTo);
                }

                template<typename ToStr>
                static inline bool execute(stlStringPack<Form_T> const& rFrom,ToStr& rTo)
                {
                    return execute(rFrom.c_str(),rTo);
                }
            };

            template<typename char_T>
            struct Str2StrImpl<char_T,char_T>
            {
                template<typename FromStr,typename ToStr>
                static inline bool execute(FromStr const& rFrom,ToStr& rTo)
                {
                    ResultString<ToStr>   recvStr(rTo);
                    return recvStr.recvString(rFrom);
                }
            };
        }        

        struct Str2Str
        {
            template<typename FromStr,typename ToStr>
            static inline bool execute(FromStr const& rFrom,ToStr& rTo)
            {  
                if (isInvalidBuf(rTo))
                {
                    return false;
                }

                if (isNullStr(rFrom))
                {
                    zeroStr(rTo);
                    return true;
                }

                typedef typename getCharType<FromStr>::type     Form_T;
                typedef typename getCharType<ToStr>::type       To_T;

                return ValidParamter::Str2StrImpl<Form_T,To_T>::execute(rFrom,rTo);
            }
        };
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /********************************************************************
        CFromString  :  convert string into suitable variable
                        implement by sscanf
        *********************************************************************/
        template<typename TString,typename To_T,bool bToString=IsString<RAWTYPE(To_T)>::value> struct CFromString;
        //string to string
        template<typename TString,typename To_T> struct CFromString<TString,To_T,true> : public Str2Str{};
        //from string to non-string
        template<typename TString,typename To_T> struct CFromString<TString,To_T,false>
        {
            template<typename T>
            static inline bool applyNullStr(T& val)             {return false;          } 
            static inline bool applyNullStr(char& val)          {val = 0; return true;  }
            static inline bool applyNullStr(signed char& val)   {val = 0; return true;  }
            static inline bool applyNullStr(unsigned char& val) {val = 0; return true;  }
            static inline bool applyNullStr(wchar_t& val)       {val = 0; return true;  }

            template<typename char_T>
            static inline bool execute(char_T const* pStr,To_T& val)   
            {
                if (!pStr) { return false; }
                if (char_T('\0') == *(pStr))
                {
                    return applyNullStr(val);
                }
                CScanBuf<To_T> buf(val);
                return 1==GetScanfFuncS<char_T>::value(pStr,GetFmtArr<char_T>::value[CFormatIdx<To_T>::value],&(buf.m_buf));
            };

            template<typename char_T>
            static inline bool execute(stlStringPack<char_T> const& rStr,To_T& val)   
            { 
                return execute(rStr.c_str(),val);
            };
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T,bool bFloat=IsInnerFloat<T>::value> struct EraseFloatTail0;
        template<typename T> struct EraseFloatTail0<T,false> 
        {
            template<typename TBuf> static inline void eraseTail0(TBuf&) { };
        };
        template<typename T> struct EraseFloatTail0<T,true> 
        {
            //when float => string, erase tail unmeaning zero. e.g. float(6.341300)=>"6.3413"
            template<typename char_T,unsigned iSIZE>
            static inline void eraseTail0(char_T (&arr)[iSIZE])
            {
                char_T const* pDot= std::char_traits<char_T>::find(arr,iSIZE-1,char_T('.'));
                if (pDot)
                {
                    size_t iIdxOfTail=std::char_traits<char_T>::length(arr)-1;
                    CHECK_TRUE_ELSE_RETURN_VAL(iIdxOfTail<iSIZE,);
                    char_T* pTail = &arr[iIdxOfTail];
                    while(pTail>pDot && char_T('0')==*pTail) *pTail--=char_T('\0');
                    if (pTail==pDot)
                    {
                        *pTail=char_T('\0');
                    }
                }
            }
        }; 

        /********************************************************************
        CToString  : convert suitable variable into string. 
                     implement by sprintf
        *********************************************************************/
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template<typename From_T,typename TStlString,bool bFromString=IsString<RAWTYPE(From_T)>::value> struct CToString;
        //from non-string to string
        template<typename From_T,typename char_T> struct CToString<From_T,stlStringPack<char_T>,false> : protected EraseFloatTail0<From_T> 
        {
            template<typename From_T>
            static inline stlStringPack<char_T> execute(From_T const& dst)
            {
                char_T buf[128] ={0};  //for max unsigned int64, 128 should be enough
                GetPrintfFuncS<char_T>::value(buf,128,GetFmtArr<char_T>::value[CFormatIdx<From_T>::value],dst);
                eraseTail0(buf);
                return stlStringPack<char_T>(buf);
            }
        };
        
        //from string to string
        template<typename From_T,typename TStlString> struct CToString<From_T,TStlString,true> : protected Str2Str
        {
            static inline TStlString execute(From_T const& from)
            {    
                TStlString to;
                Str2Str::execute(from,to);
                return to;
            }
        }; 

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct AutoConstruct
        {
            template<typename From_T,typename To_T>
            static bool execute(From_T& rFrom,To_T& rTo)
            {                                          
                rTo = To_T(rFrom);
                return true;
            }
        };

        //TSupportToString : support user override for customized type.
        template<typename T> struct TSupportToString : TrueType{};

        template<typename From_T,typename To_T,bool bFromStr=IsString<From_T>::value,bool bToStr=IsString<To_T>::value>
        struct TFromTo;

        //str => str
        template<typename From_T,typename To_T>
        struct TFromTo<From_T,To_T,true,true> 
            : public If_Evl<And_T<IsStringStl<To_T>,IsConvertable<From_T,To_T> >,AutoConstruct,Str2Str>::type{};

        //non str => str
        template<typename From_T,typename To_T>
        struct TFromTo<From_T,To_T,false,true> 
            : public If_Evl<And_T<TSupportToString<From_T>,IsClassStruct<From_T>,IsConvertable<From_T,To_T> >,AutoConstruct,CToString<From_T,To_T> >::type {};
        
        //str => non str
        template<typename From_T,typename To_T>
        struct TFromTo<From_T,To_T,true,false> 
            : public If_Evl<And_T<IsClassStruct<To_T>,IsConvertable<From_T,To_T> >,AutoConstruct,CFromString<From_T,To_T> >::type {};
    }
}

#endif // STLSTRINGCONVERTDETAIL_H__
