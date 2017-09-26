#ifndef _HASH_UTIL_H_
#define _HASH_UTIL_H_
#include <string>

namespace CommonUtils
{

class HashUtil
{
public:

	/*
	* 函数介绍：hash字符串
	* 输入参数：char *str 需hash化的字符串
	* 输出参数：无
	* 返回值  ：字符串得到的hash值
	*/
	unsigned  int  ELFHash(const char   * str);

};
}

#endif
