#include <string.h>
#include <algorithm>
#include "StringUtil.h"
#include "PatternMatcher.h"


namespace CommonUtils{

std::string & StringUtil::ltrim(std::string &str)
{
	std::string::iterator iter=std::find_if(str.begin(),str.end(),std::not1(std::ptr_fun<int>(::isspace)));
	str.erase(str.begin(),iter);
	return  str;
};

std::string& StringUtil::rtrim(std::string &str)
{
	std::string::reverse_iterator  rev_iter=std::find_if(str.rbegin(),str.rend(),std::not1(std::ptr_fun<int>(::isspace)));
	str.erase(rev_iter.base(),str.end());
	return   str;
};
    
std::string& StringUtil::trim(std::string &str)
{
	return ltrim(rtrim(str));
};


char* StringUtil::rtrim(char *str)
{
	int nLen;
	nLen = strlen( str );
	if ( nLen <= 0 )
	{
		return str;
	}
	while( nLen > 0 && isspace( (int)str[ nLen - 1 ] ) )
		nLen--;
	str[nLen] = '\0';
	return str;
};
    
char* StringUtil::ltrim(char *str)
{
	char * pLoc;
	pLoc = str;
	while( isspace( (int)*pLoc ) )
		pLoc++;
	strcpy( str, pLoc );
	str[strlen(pLoc)] = '\0';
	return str ;
};
    
char* StringUtil::trim(char *str)
{
	return ltrim(rtrim(str));
};


int StringUtil::lalign(char *str, const int strlength,  const char stuff )
{
	int i,length;
	ltrim(str);

	length=strlen(str);
	if (length == strlength)
		return 1;

	if (length < strlength)
	{
		for(i=1;i <= strlength-length;i++)
		  str[i+length-1] = stuff;

		str[i+length-1] = '\0';
	}
	else
	{
		str[strlength] = '\0';
	}
	return strlen(str);
};



int StringUtil::ralign(char *str, const int strlength,const char stuff )
{
	int i,j,length;
	trim(str);
	length=strlen(str);
	if (length == strlength)
		return 1;

	if (length < strlength)
	{
		str[strlength] = '\0';
		for(j=length-1,i=strlength-1;j>=0;i--,j--)
		{
		  str[i] = str[j];
		}

		for(i=strlength-length-1;i>=0;i--)
		{
		  str[i] = stuff;
		}
	}
	else
	{
		str[strlength] = '\0';
	}

	return 1;
};

int StringUtil::eraseChar(char *str,const char& ch)
{
	int i,j,length;

	length=strlen(str);
	for(i=0,j=0;i<length;i++)
	{
		if ((str[i]!=ch))
		{
			if (i!=j)
			  str[j]=str[i];
			j++;
		}
	}
	str[j]='\0';
	return (j+1);
};

std::string& StringUtil::toUpperCase(std::string &str)
{
	for (std::string::iterator pos=str.begin(); pos != str.end(); pos++)
		*pos = toupper(*pos);
	return str;
};
    
std::string& StringUtil::toLowerCase(std::string &str)
{
	for (std::string::iterator pos=str.begin(); pos != str.end(); pos++)
		*pos = tolower(*pos);
	return str;
};

bool StringUtil::equalsIgnoreCase(const std::string &s1, const std::string &s2)
{
	if(s1.length() != s2.length())
		return false;
	std::string::const_iterator it1=s1.begin();
	std::string::const_iterator it2=s2.begin();
	for(; it1 != s1.end(); it1++, it2++)
	{
		if(tolower(*it1) != tolower(*it2))
		{
			return false;
		}
	}
	return true;
};


bool StringUtil::isBlank(const std::string &str)
{
	size_t i;
	for ( i=0; i<str.length(); ++i) {
		if (!isspace(str[i]))
			return false;
	}
	return true;
};

bool StringUtil::matches(const char* str, const char* mask)
{
	return PatternMatcher::matches(mask,str);
};

bool StringUtil::GetTextFld(const std::string &strSrc , std::string &strDest , std::string strSep , int iNO)
{
	int iBegPos = 0;
	int iCurPos = 0;
	int iCnt = 0;
	while((iCurPos = strSrc.find(strSep , iBegPos)) != std::string::npos)
	{
		if(++iCnt > iNO)
			break;
		iBegPos = (iCurPos + strSep.length());
	}

	if(iCnt == iNO ) ///最后一个字段
		strDest = strSrc.substr(iBegPos);
	else if(iCnt > iNO )
		strDest = strSrc.substr(iBegPos , iCurPos - iBegPos);
	else
		return false;

	return true;
}


size_t StringUtil::split(const std::string &str, const std::string &delim, std::vector<std::string> &result,bool needTrim)
{
	if(str.length() == 0) return 0;

	if (delim.length() <=0) {
	   result.push_back(str);
	   return 1;
	}

	size_t c = 0;
	for (size_t i, pos=0; ; pos = i+delim.length()) {
		i = str.find(delim, pos);

		if (i == std::string::npos)
			result.push_back(str.substr(pos));
		else
			result.push_back(str.substr(pos,i - pos));

		if(needTrim)
		  trim(result[result.size()-1]);

		c++;
		if (i == std::string::npos) break;
	}
	return c;
};

size_t StringUtil::split4GB(const std::string &str, const std::string &delim, std::vector<std::string> &result, bool needTrim )
{
	if(str.length() == 0) return 0;

	if (delim.length() <=0) {
	   result.push_back(str);
	   return 1;
	}
	size_t c=0;
	int i=0;
	std::string field;
	while (i<str.length() )
	{

		field="";
		while (i<str.length())
		{
			if (strncmp(str.c_str()+i,delim.c_str(),delim.length())==0)
			{
				i+=delim.length();
				break;
			}
			else
			{
				//因为根据GB18030-2000的规定，双字节编码字符的第一个字节的编码范围在0x81 ~ 0xFE之间；
				//第二个字节的编码范围在0x40 ~ 0x7E和0x80 ~ 0xFE之间
				//简化统一判断 第一个字节> 0x80 就认为是双字节
				if (str[i]>=0x81)
				{
					//取两位
					field += str[i];
					i++;
					field += str[i];
					i++;
				}
				else
				{
					field += str[i];
					i++;
				}
			}
		}
		if(needTrim)
		  trim(field);
		result.push_back(field);
		c++;
	}
	return c;
};

size_t StringUtil::tokenize(const std::string &str,std::vector<std::string> &result,const std::string &delim,bool needTrim )
{
	if(str.length() == 0) return 0;

	if (delim.length() <=0)
	{
		result.push_back(str);
		return 1;
	}

	size_t c = 0;
	for (size_t i, pos=0; ; pos = i+1)
	{
		i = str.find_first_of(delim, pos);

		if (i == std::string::npos)
			result.push_back(str.substr(pos));
		else
			result.push_back(str.substr(pos,i - pos));

		if(needTrim)
			trim(result[result.size()-1]);

		c++;
		if (i == std::string::npos)
			break;
	}
	return c;
};
  



bool StringUtil::replace(std::string &in, const std::string &search, const std::string &replacement)
{
	bool bRet = false;
	std::string::size_type pos = 0;
	while( pos < in.length() && (pos=in.find(search, pos)) != std::string::npos )
	{
		bRet = true;
		in.replace(pos, search.length(), replacement);
		pos += replacement.length();
	}
	return bRet;
};

std::string StringUtil::replace(const std::string &in, const std::string &search, const std::string &replacement)
{
	std::string i =in;
	replace(i, search, replacement);
	return i;
};

bool StringUtil::replace(std::string &in,  const std::string &search, char replaceChar)
{
    bool bRet = false;
    std::string::size_type pos = 0;
    while( pos < in.length() && (pos=in.find(search, pos)) != std::string::npos )
    {
        bRet = true;
        in.replace(pos, search.length(), 1 ,replaceChar);
        ++pos;
    }
    return bRet;
}

std::string StringUtil::pad(const char *str, const int  length, const char *stuff ,const bool left )
{
	size_t len = strlen(str);
	if (len >= length )
		return str;

	if ( strlen(stuff)<=0 )
		return str;

	size_t len_stuff = strlen(stuff);
	std::string buffer;
	for (int i = 0; i < ((length-len) / len_stuff) ; ++i)
		buffer += stuff;

	buffer += stuff;
	buffer = std::string(buffer.c_str(),buffer.c_str()+ (length-len));

	return (left ? (buffer+str) : (str+buffer));
};
    

std::string StringUtil::toString(long value, bool sign )
{
	return format(sign ? "%+ld" : "%ld", value);
};
    
std::string StringUtil::toString(double value, bool sign )
{
  return format(sign ? "%+lf" : "%lf", value);
};

std::string StringUtil::toString(int value, bool sign )
{
	return format(sign ? "%+ld" : "%ld", value);
};
    
/// A wrapper around the c-library sprintf routine.
///   Note: We attempt to perform the string formatting using a stack-based
///   buffer of a 1024 byte size.  If that fails then we return a null string.
std::string StringUtil::format(const char* fmt, /// format specifers string
								... )
{
	#ifdef _MSC_VER
	#define VSNPRINTF _vsnprintf
	#else
	#define VSNPRINTF vsnprintf
	#endif

	std::string ret;
	const int stackBufferSize = 1024;
	char stackBuffer[stackBufferSize];

	va_list ap;
	va_start(ap, fmt);
	int n = VSNPRINTF(stackBuffer, stackBufferSize, fmt, ap);
	va_end(ap);

	/* If that worked, return the string. */
	if (n > -1 && n < stackBufferSize)
	{
		return std::string((const char*)stackBuffer, n);
	}

	return "";
};


std::string StringUtil::format(time_t timet , /// 要格式化的时间字符串
		   	   	   	   	   const char* specifers  /// conversion specifers
		   	   	   	   )
{
	time_t t = timet;
	if (timet==0)  // get now time
		t = time((time_t*)0);

	struct tm * tmptr = localtime(&t);

	if (specifers == 0)
		return asctime(tmptr);

	char buffer[1024];
	strftime(buffer,sizeof(buffer),specifers,tmptr);
	return buffer;
};


bool StringUtil::isHexString(const std::string &in)
{
	for(std::string::const_iterator i=in.begin(); i!=in.end(); ++i)
	{
		const char x = (*i);
		if(!isxdigit(x))
		{
			return false;
		}
	}
	return !in.empty();
};


std::string StringUtil::toHexString(const std::string &str)
{
	std::string::const_iterator i(str.data());
	std::string::const_iterator end(str.data()+str.size());
	std::string ret;

	while(i != end)
	{
		ret += ("\\x");
		ret += (format("%04X", (unsigned int)(*i++)));
	}
	return ret;
};

    
int StringUtil::command(const std::string cmd,	std::vector< std::string > & lines )
{
	FILE *pipe;
	char buffer[2048] = {0};

	lines.clear();

	if((pipe=popen(cmd.c_str(),"r"))==NULL)
	{
		return -1;
	}

	while( fgets( buffer,sizeof(buffer),pipe ) != NULL )
	{

		lines.push_back(buffer);
		memset(buffer,0 , sizeof(buffer));
	}
	if( -1 == pclose(pipe))
	    return -1;

	return lines.size();
};

}
    

