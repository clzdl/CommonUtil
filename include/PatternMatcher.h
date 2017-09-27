
#ifndef __PATTERNMATCHER_H__
#define __PATTERNMATCHER_H__

namespace CommonUtils{

///
/// @class PatternMatcher 
/// 
/// @brief 字符串模式匹配器
///
/// 
class PatternMatcher
{
public:
    /**
     * 匹配字符串
     * @pattern 匹配模式字符串  *?[]\
     * @str 验证的字符串
     */
	static bool matches(const char *pattern, const char *str);

private:
	PatternMatcher();
	PatternMatcher(const PatternMatcher& pm);
	PatternMatcher& operator = (const PatternMatcher &pm);
};

}

#endif  /* __PATTERNMATCHER_H__  */


