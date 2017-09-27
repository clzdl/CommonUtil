#ifndef _STRINGUTIL_
#define _STRINGUTIL_



#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/types.h>

namespace CommonUtils{
/**
 * @class StringUtil 
 *
 * @brief 字符串工具类.
 */


class StringUtil {
  public:

	/*@action:用于去掉字符串的左侧空格
	 *@param：
	 *		str--入参，字符串
	 *@return： 剔除空格后的字符串
	 */
    static std::string & ltrim(std::string & str) ;

    /*@action:用于去掉字符串的右侧空格
	 *@param：
	 *		str--入参，字符串
	 *@return： 剔除空格后的字符串
	 */
    static std::string & rtrim(std::string & str) ;
    
    /*@action:用于去掉字符串的两侧空格
   	 *@param：
   	 *		str--入参，字符串
   	 *@return： 剔除空格后的字符串
   	 */
    static std::string & trim(std::string & str) ;


    /*@action:用于去掉字符串的右侧空格
	 *@param：
	 *		str--入参，字符串
	 *@return： 剔除空格后的字符串
	 */
    static char* rtrim(char *str) ;
    
    /*@action:用于去掉字符串的左侧空格
   	 *@param：
   	 *		str--入参，字符串
   	 *@return： 剔除空格后的字符串
   	 */
    static char* ltrim(char *str) ;
    
    /*@action:用于去掉字符串的两侧空格
	 *@param：
	 *		str--入参，字符串
	 *@return： 剔除空格后的字符串
	 */
    static char* trim(char *str) ;



    /*@action:用于左对齐字符串
   	 *@param：
   	 *		str--入参，字符串
   	 *		strlength--入参，处理长度
   	 *		stuff--入参，填充字符
   	 *@return： 字符串长度
   	 */
    static int lalign(char *str, /// 待处理字符串
                      const int strlength, /// 处理的长度 
                      const char stuff = ' ' /// 填充的字符
                      );



    /*@action:用于右对齐字符串
	 *@param：
	 *		str--入参，字符串
	 *		strlength--入参，处理长度
	 *		stuff--入参，填充字符
	 *@return： 字符串长度
	 */
    static int ralign(char *str, /// 待处理字符串
                      const int strlength, /// 处理的长度 
                      const char stuff =' '  /// 填充的字符
                      );


    /*@action:用于删除特定字符
	 *@param：
	 *		str--入参，字符串
	 *		ch--入参，需删除的字符
	 *@return： 字符串长度
	 */
    static int eraseChar(char *str,
                         const char& ch=' ' /// 去除的字符
                         );


    /*@action:用于字符串转换成大写
	 *@param：
	 *		str--入参，字符串
	 *@return： 转换后的字符串
	 */
    static std::string & toUpperCase(std::string & str) ;
    
    /*@action:用于字符串转换成小写
	 *@param：
	 *		str--入参，字符串
	 *@return： 转换后的字符串
	 */
    static std::string & toLowerCase(std::string & str) ;
    
    /*@action:用于忽略字符串大小写比较
	 *@param：
	 *		s1--入参，字符串1
	 *		s2--入参，字符串2
	 *@return： true-相等，false-不等
	 */
    static bool equalsIgnoreCase(const std::string &s1, const std::string &s2) ;


    /*@action:用于测试是否是空字符串
   	 *@param：
   	 *		str--入参，待测试字符串
   	 *@return： true/false
   	 */
    static bool isBlank(const std::string &str) ;



    /*@action:用于简单模式匹配 Shell-Style
	 *@param：
	 *		str--入参，待匹配字符串
	 *		mask--入参，模式串
	 *@return： true/false
	 */
    static bool matches(const char* str, const char* mask) ;
    
    /*@action:用于获取按指定分割符分割后字符串的指定序号字段
     *@param：
     *		strSrc--入参，源字符串
     *		strDest--出参，结果字符串
     *		strSep--入参， 分割符
     *		iNO--入参，指定的字段号，从0开始
     *@return:true/false
     */
    static bool GetTextFld(const std::string &strSrc , std::string &strDest , std::string strSep , int iNO);

    /*@action:用于分割字符串
   	 *@param：
   	 *		str--入参，源字符串
   	 *		delim--入参，分割符
   	 *		result--入参，分割后结果集
   	 *		needTrim--入参，是否需要去空格
   	 *@return： 分割的字段数
   	 */
    static size_t split(const std::string &str, ///源字符串
                        const std::string &delim, ///分割字符
                        std::vector<std::string> &result, ///结果
                        bool needTrim = false ///是否去掉结果字串两边空格
                        ) ;



    /*@action:用于分割字符串,支持带汉字字符串分割
	 *@param：
	 *		str--入参，源字符串
	 *		delim--入参，分割符
	 *		result--入参，分割后结果集
	 *		needTrim--入参，是否需要去空格
	 *@return： 分割的字段数
	 */
    static size_t split4GB(const std::string &str, ///源字符串
                        const std::string &delim, ///分割字符
                        std::vector<std::string> &result, ///结果
                        bool needTrim = false ///是否去掉结果字串两边空格
                        ) ;



   
    /*@action:用于按关键字进行分割
	 *@param：
	 *		str--入参，源字符串
	 *		delim--入参，关键字
	 *		result--入参，分割后结果集
	 *		needTrim--入参，是否需要去空格
	 *@return： 分割的字段数
	 */
   static size_t tokenize(const std::string &str,std::vector<std::string>&result,
                          const std::string &delim,
                          bool needTrim = false ///是否去掉结果字串两边空格
                          ) ;
  
   //模板函数
   template <typename T>
   static std::string string_join(const T& arr, const std::string& delim) {
       if (arr.empty()) {
           return "";
       }
       std::string	result = arr.front();
       typename T::const_iterator   it	= arr.begin();
       size_t needed = result.size();
       while (++it != arr.end()) {
           needed += delim.size() + it->size();
       }
       result.reserve(needed);
       it = arr.begin();
       while (++it != arr.end()) {
           result += delim;
           result += *it;
       }
       return result;
   }

   /*@action:用于合并字符串
   	 *@param：
   	 *		arr--入参，字符串容器
   	 *		delim--入参，分隔符
   	 *@return： 合并后的字符串
   	 */
    static std::string join(const std::list<std::string> &arr, const std::string &delim) {
        return string_join(arr, delim);
    };
    
    /*@action:用于合并字符串
	 *@param：
	 *		arr--入参，字符串容器
	 *		delim--入参，分隔符
	 *@return： 合并后的字符串
	 */
    static std::string join(const std::vector<std::string> &arr, const std::string &delim ) {
        return string_join(arr, delim);
    };


    /*@action:用于替换字符串
	 *@param：
	 *		in--入参，字符串
	 *		search--入参，待替换字符串
	 *		replacement--入参，替换字符串
	 *@return： true/false
	 */
    static bool replace(std::string &in,
              	  	 const std::string &search,
                        const std::string &replacement);


    /*@action:用于替换字符串
   	 *@param：
   	 *		in--入参，字符串
   	 *		search--入参，待替换字符串
   	 *		replacement--入参，替换字符串
   	 *@return： 替换后的字符串
   	 */
    static std::string replace(const std::string &in,
                          const std::string &search,
                          const std::string &replacement) ;


    /*@action:用于替换字符串为指定字符  20151112
     *@param：
     *      in--入参，字符串
     *      search--入参，待替换字符串
     *      replacement--入参，替换字符
     *@return： 替换后的字符串
     */
    static bool replace(std::string &in,
                          const std::string &search,
                          char replaceChar) ;


    /*@action:用于填充字符串
	 *@param：
	 *		str--入参，源字符串
	 *		length--入参，预期长度
	 *		stuff--入参，要填充的字符
	 *		left--入参， 是否在左边填充到(反之在右边)
	 *@return： 替换后的字符串
	 */
    static std::string pad(const char *str,/// 源字符串
                      const int  length, /// 预期长度
                      const char *stuff = " ", /// 要填充的字符
                      const bool left = true /// 是否在左边填充到(反之在右边)
                      ) ;
    

    /*@action:用于将任何可以输出到流里的对象, 转换成字符串
	 *@param：
	 *		value--入参，对戏那个
	 *		sign--入参，是否显示符号（+-）
	 *@return： 转换后的字符串
	 */
    template <typename T>
    static std::string toString(T value, bool sign = false) {
    	std::ostringstream buffer;
    	if(sign)
    		buffer<<std::showpos;

    	buffer<<std::fixed<<value;

    	return buffer.str();
    }
    

    /*@action:用于 将字符串转换成对象；toValue<int>("123");
   	 *@param：
   	 *		str--入参，字符串
   	 *@return： 转换后的字符串
   	 */
    template <typename T>
    static T toValue(const std::string& str) {
    	std::stringstream buffer;
    	buffer<<str;
    	T value = T();
    	buffer >> value;
    	return value;
    }


    /*@action:用于将long转换成string
	 *@param：
	 *		value--入参，long值
	 *		sign--入参，是否显示符号（+-）
	 *@return： 转换后的字符串
	 */
    static std::string toString(long value, bool sign = false ) ;
    

    /*@action:用于将double转换成string
	 *@param：
	 *		value--入参，long值
	 *		sign--入参，是否显示符号（+-）
	 *@return： 转换后的字符串
	 */
    static std::string toString(double value, bool sign = false ) ;

    /*@action:用于将int转换成string
   	 *@param：
   	 *		value--入参，long值
   	 *		sign--入参，是否显示符号（+-）
   	 *@return： 转换后的字符串
   	 */
    static std::string toString(int value, bool sign = false ) ;
    
    /// A wrapper around the c-library sprintf routine.
    ///   Note: We attempt to perform the string formatting using a stack-based
    ///   buffer of a 1024 byte size.  If that fails then we return a null string.
    static std::string format(const char* fmt, /// format specifers string
    							...  /// strings
                         	 ) ;



    /// A wrapper around the c-library strftime function 
        /// A wrapper around the c-library strftime function 
    /// SunOS 5.9            Last change: 5 Feb 2001                    1
    ///      %%    Same as %.
    ///      %a    Locale's abbreviated weekday name.
    ///      %A    Locale's full weekday name.
    ///      %b    Locale's abbreviated month name.
    ///      %B    Locale's full month name.
    ///      %c    Locale's appropriate date and time representation.
    /// 
    /// Standard conforming
    ///      %C    Century number (the year divided by 100 and  truncated
    ///            to  an  integer  as  a  decimal number [1,99]); single
    ///            digits are preceded by 0; see standards(5).
    /// 
    ///      %d    Day of month [1,31]; single digits are preceded by 0.
    ///      %D    Date as %m/%d/%y.
    ///      %e    Day of month [1,31]; single digits are preceded  by  a
    ///            space.
    ///      %g    Week-based year within century [00,99].
    ///      %G    Week-based year, including the century [0000,9999].
    ///      %h    Locale's abbreviated month name.
    ///      %H    Hour (24-hour clock) [0,23]; single  digits  are  pre-
    ///            ceded by 0.
    ///      %I    Hour (12-hour clock) [1,12]; single  digits  are  pre-
    ///            ceded by 0.
    ///      %j    Day number of year [1,366]; single digits are preceded
    ///            by 0.
    ///      %k    Hour (24-hour clock) [0,23]; single  digits  are  pre-
    ///            ceded by a blank.
    ///      %l    Hour (12-hour clock) [1,12]; single  digits  are  pre-
    ///            ceded by a blank.
    ///      %m    Month number [1,12]; single digits are preceded by 0.
    ///      %M    Minute  [00,59];  leading  0  is  permitted  but   not
    ///            required.
    ///      %n    Insert a NEWLINE.
    ///      %p    Locale's equivalent of either a.m. or p.m.
    ///      %r    Appropriate time representation in 12-hour clock  for-
    ///            mat with %p.
    ///      %R    Time as %H:%M.
    ///      %S    Seconds [00,61]; the range of values is [00,61] rather
    ///            than  [00,59]  to allow for the occasional leap second
    ///            and even more occasional double leap second.
    ///      %t    Insert a TAB.
    ///      %T    Time as %H:%M:%S.
    ///      %u    Weekday as a decimal number [1,7], with 1 representing
    ///            Monday. See NOTES below.
    ///      %U    Week number of year as a decimal number [00,53],  with
    ///            Sunday as the first day of week 1.
    ///      %V    The ISO 8601 week number as a decimal number  [01,53].
    ///            In  the  ISO  8601 week-based system, weeks begin on a
    ///            Monday and week  1  of  the  year  is  the  week  that
    ///            includes  both  January  4th and the first Thursday of
    ///            the year.  If the first Monday of January is the  2nd,
    ///            3rd,  or  4th, the preceding days are part of the last
    ///            week of the preceding year.  See NOTES below.
    ///      %w    Weekday as a decimal number [0,6], with 0 representing
    ///            Sunday.
    ///      %W    Week number of year as a decimal number [00,53],  with
    ///            Monday as the first day of week 1.
    ///      %x    Locale's appropriate date representation.
    ///      %X    Locale's appropriate time representation.
    ///      %y    Year within century [00,99].
    ///      %Y    Year, including the century (for example 1993).
    ///      %Z    Time zone name or abbreviation, or no bytes if no time
    ///            zone information exists.
    /// 
    /// common usage
    ///      %Y    Year, including the century (for example 1993).
    ///      %m    Month number [1,12]; single digits are preceded by 0.
    ///      %d    Day of month [1,31]; single digits are preceded by 0.     
    ///      %H    Hour (24-hour clock) [0,23]; single  digits  are  pre-
    ///            ceded by 0.
    ///      %M    Minute  [00,59];  leading  0  is  permitted  but   not
    ///            required.
    ///      %S    Seconds [00,61]; the range of values is [00,61] rather
    ///            than  [00,59]  to allow for the occasional leap second
    ///            and even more occasional double leap second.
    static std::string format(time_t timet = 0, /// 要格式化的时间字符串
							   const char* specifers = 0 /// conversion specifers
							   );


    /// Tests if the passed string contains only hexadecimal characters
    /// [0-9], [a-f], [A-F]
    /// 
    /// @param in the string to test
    /// @returns true if the passed String contains hexadecimal characters only;
    ///         false otherwise
    static bool isHexString(const std::string &in);



    /// 
    /// Creates and returns a String containing each character from @c str in
    /// hexadecimal notation.
    /// 
    /// @param str a String containing Unicode characters encoded according to the
    /// internal convention.
    /// 
    /// @returns a hexadecimal representation of the Unicode characters within @c str
    /// 
    //==============================================================================
    static std::string toHexString(const std::string &str);

    

    /*@action:用于得到一个命令执行的输出行
  	 *@param：
  	 *		cmd--入参，命令串
  	 *		lines--入参，命令输出行
  	 *@return：vector size
  	 */
    static int command(const std::string  cmd,  ///命令
                	std::vector< std::string > & lines ///命令输出行
					) ;


private:
    StringUtil();
    StringUtil(const StringUtil &su);
    StringUtil& operator = (const StringUtil &su);

};

}
#endif //_STRINGUTIL_

