#include <win32/CmdLineParser.h>
#include <windows.h>
#include <algorithm>
//#include <regex>

/*/
#include <vector>
std::vector<std::wstring> SplitCmdlineByBlank(const std::wstring & commandLine)
{	//use windows API to split the command line string by blank char
	std::vector<std::wstring>  opts;

	LPWSTR	*szArglist	= nullptr;
	int		nArgs		= 0;
	szArglist = CommandLineToArgvW(commandLine.c_str(), &nArgs);
	for (int i=0; i< nArgs; ++i)
	{
		opts.push_back(szArglist[i]);
	}
	LocalFree(szArglist);

	return opts;
}
//*/

CmdLineParser::CmdLineParser(const wchar_t* pLine/*=NULL*/)
{
	m_line = pLine ? pLine : ::GetCommandLineW();
	setSplitChar();
}

bool CmdLineParser::setSplitChar(wchar_t optSplitChar/*=' '*/, wchar_t keyValSplitChar/*=':'*/)
{
	m_optSplitChar		= optSplitChar;
	m_valueSplitChar		= keyValSplitChar;
	return true;
}

bool CmdLineParser::init()
{
	unsigned noSelf = nextHead(m_line,0);
	m_exe = m_line.substr(0, noSelf);
	m_exe.erase(m_exe.find_last_not_of(L"\t\n\v\f\r ") + 1);  //trim right
	if (noSelf != m_line.size())
	{
		m_parms = m_line.substr(noSelf);
	}
	return true;
}

unsigned CmdLineParser::nextHead(std::wstring const& str,unsigned iFrom /*= 0*/)
{  //std::wregex/std::wsmatch is hard to process some case , e.g. : /file:"c:/linuxStylePath/myfile.txt"
	while (str[iFrom] == ' ' || str[iFrom] == '\t') iFrom++;

	unsigned quateNum = 0;
	while (str[iFrom] != 0)
	{
		if (str[iFrom] == '\"')
		{
			quateNum++;
		}

		if (str[iFrom] == m_optSplitChar && (quateNum % 2) == 0)
		{
			break;
		}
		iFrom++;
	}
	while (str[iFrom] == ' ' || str[iFrom] == '\t') iFrom++;
	return iFrom;
}

unsigned CmdLineParser::initOptions()
{
	if (!m_parms.empty() && m_options.size()==0)
	{
		unsigned iCur = 0;
		while (iCur < m_parms.size())
		{
			unsigned iNext = nextHead(m_parms, iCur);
			parseOption(m_parms.substr(iCur, iNext - iCur));
			iCur = iNext;
		}
	}
	return m_options.size();
}

bool CmdLineParser::parseOption(std::wstring opt)
{
	opt.erase(opt.find_last_not_of(L"\t\n\v\f\r ") + 1);  //trim right
	if (opt.empty())
	{
		return false;
	}

	std::wstring sKey;
	std::wstring sVal;
	auto iPos = std::find_if(opt.begin(), opt.end(), [this](std::wstring::value_type ch) { return ch == ' ' || ch == '\t' || ch == m_valueSplitChar; });
	if (std::end(opt) != iPos)
	{
		sKey = opt.substr(0, iPos - opt.begin());
		iPos = std::find_if(iPos, opt.end(), [this](std::wstring::value_type ch) { return ch != ' ' && ch != '\t' && ch != m_valueSplitChar; });
		if (std::end(opt) != iPos)
		{
			sVal = &*iPos;
			if (sVal[0] == '"' && sVal.back() == '"')
			{
				sVal = sVal.substr(1, sVal.size() - 2);
			}
		}
	}
	else
	{
		sKey = opt;
	}
	m_options.insert(std::make_pair(sKey, sVal));
	return true;
}