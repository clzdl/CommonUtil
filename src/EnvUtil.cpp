/*
 * EnvUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#include "EnvUtil.h"
#include "stdlib.h"

namespace CommonUtils
{

void EnvUtil::EnvVarReplace(std::string &value)
{
	std::string result;

	std::string::size_type left = 0;
	std::string::size_type right = value.find("${", left);
	if (right == std::string::npos)
		return;

	while(true)
	{

		result += value.substr(left, right - left);
		if (right == std::string::npos)
			break;

		left = right + 2;
		right = value.find('}', left);
		if (right == std::string::npos)
		{
			// no close tag, use string literally
			result += value.substr(left - 2);
			break;
		}
		else
		{
			const std::string key = value.substr(left, right - left);
			if (key == "${")
				result += "${";
			else
			{
				char* value = getenv(key.c_str());
				if (value)
					result += value;

			}
			left = right + 1;
		}

		right = value.find("${", left);
	}

	value = result;

}


}


