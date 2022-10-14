#ifndef __ANY_CAST_HPP__
#define __ANY_CAST_HPP__
/***********************************************************************************************************************
* Description         : static_cast/reinterpret_cast and directly type cast can't process some type conversion.
*                       e.g. function pointer type, data member pointer type.
*                       Note: convertable correctness MUST be confirmed by user.                              
* Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
* Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
namespace MiniMPL
{
    //[ warning ] float/double and int/int-similar cast will cause the wrong result because of their different storage mechanism.
    /*
    static_assert( And_T< Not_T< Xor_T< std::is_floating_point< TP >,std::is_floating_point< TR > > > ,
                          Not_T< Xor_T< std::is_integral< TP >,std::is_integral< TR > > > >::value ,
                          "int and float cast" );
    */
    struct CAnyCast
    {
    protected:
        template <typename TP>
        struct Impl
        {
            Impl(TP p) : m_p(p){};

            template <typename TR> 
            operator TR()
            {                
                union
                {
                    TP m_p;
                    TR m_r;
                } castImpl;

                castImpl.m_p = m_p;
                return castImpl.m_r;
            }

            TP m_p;
        };

    public:
        template<typename TP> 
        static Impl<TP> make(TP p)
        {
            return Impl<TP>(p);
        }

        template<typename TP> 
        Impl<TP> operator ()(TP p)
        {
            return make(p);
        }
    };

    template<typename TP> inline CAnyCast::Impl<TP> any_cast(TP p)
    {
        return _anycast(p);     // or return CAnyCast::make(p);
    } 
}

static MiniMPL::CAnyCast      _anycast;


#endif // __ANY_CAST_HPP__
