#ifndef CmdLineParser_h__
#define CmdLineParser_h__
#include <string>
#include <map>
#include "MiniMPL\kitType.hpp"

template<typename T>	struct OutType;	//fw declare

//parse parameter spitted by special char.
//if parameter includes blank char, quote them with ""
//e.g  below bin.exe with 5 parameter.  -n  | /f  |  /g  | /o:myfile  | /l:"C:\\my logs\log_1.txt"
//bin.exe  -n  /f  /g  /o:myfile /l:"C:\\my logs\\log_1.txt"
// /cmd /file:"c:\file" /file2:c:\file /comments:"hello world" /contact:"abc@mail.com" /type:"other" /type:4
struct CmdLineParser
{
	std::wstring					m_line;
	std::wstring					m_exe;
	std::wstring					m_parms;

	CmdLineParser(const wchar_t* pLine=NULL);
	bool setSplitChar(wchar_t optSplitChar='/', wchar_t keyValSplitChar=':');
	bool init();

	template<typename TVal>
	typename OutType<TVal>::type getOptionVal(wchar_t* const pOptName, const TVal defVal) const;	//Note : pOptName is case sensitive

protected:
	unsigned	nextHead(std::wstring const& str,unsigned iFrom = 0);
	unsigned	initOptions();
	bool		parseOption(std::wstring opt);

private:
	wchar_t										m_optSplitChar;
	wchar_t										m_valueSplitChar;
	std::map<std::wstring, std::wstring>		m_options;
};

#include "win32/CmdLineParser.hpp"

#endif // CmdLineParser_h__
