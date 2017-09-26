/*
 * RegUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */


#include "RegUtil.h"
#include <regex.h>

namespace CommonUtils
{

bool RegUtil::is_match(const std::string& str, const std::string& pattern)
{
	regex_t re;
	if(pattern == "*")
		return true;

	bool match = (	(0 == regcomp(&re, pattern.c_str(), REG_EXTENDED|REG_NOSUB))
						&& (0 == regexec(&re, str.c_str(), (size_t)0, NULL, 0)));

	regfree(&re);
	return match;
}

}

