#ifndef CmdLineParser_hpp__
#define CmdLineParser_hpp__

#ifndef CmdLineParser_h__
	#error you should include CmdLineParser.h , instead of CmdLineParser.hpp. here is template member function implement
#endif

template<typename T>  struct OutType		: public MiniMPL::Type2Type<T> {};
template<> struct OutType<char const*>		: public MiniMPL::Type2Type<std::wstring> {};
template<> struct OutType<wchar_t const*>	: public MiniMPL::Type2Type<std::wstring> {};

#ifdef NotUseMiniMPL
template<typename TO>
inline bool string2Val(std::wstring const pStr, TO& outVal, ENABLE_IF((MiniMPL::IsString<TO>::value)))
{
	outVal = pStr;
	return true;
}

template<typename TO>
inline bool string2Val(std::wstring const pStr, TO& outVal, ENABLE_IF((!MiniMPL::IsString<TO>::value)))
{
	std::wstringstream ss;
	ss << pStr;
	ss >> outVal;
	return ss.good();
}
#else
template<typename TO>
inline bool string2Val(std::wstring const pStr, TO& outVal)
{
	return MiniMPL::fromString(pStr, outVal);
}
#endif

template<typename TVal>
typename OutType<TVal>::type CmdLineParser::getOptionVal(wchar_t* const pOptName, const TVal defVal) const
{
	if (m_options.size()==0)
	{
		initOptions();
	}
	if (m_options.size()==0)
	{
		return defVal;
	}

	std::map<std::wstring, std::wstring >::iterator it = m_options.find(pOptName);
	if (it != m_options.end() && !it->second.empty())
	{
		typename OutType<TVal>::type  oRet;
		string2Val(it->second, oRet);
		return oRet;
	}
	else
	{
		return defVal;
	}
}

#endif // CmdLineParser_hpp__
