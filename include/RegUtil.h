/*
 * RegUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_REGUTIL_H_
#define INCLUDE_REGUTIL_H_

#include <string>

namespace CommonUtils
{
class RegUtil
{
public:
	/*@action:用于正则匹配
	 *@param：
	 *		str--入参，待匹配字符串
	 *		pattern--入参，正则串
	 *@return：true/false
	 */
	bool is_match(const std::string& str, const std::string& pattern);
};

}



#endif /* INCLUDE_REGUTIL_H_ */
