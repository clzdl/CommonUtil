/*
 * JsonUtil.h
 *
 *  Created on: 2017年9月27日
 *      Author: cplusplus
 */

#ifndef INCLUDE_JSONUTIL_H_
#define INCLUDE_JSONUTIL_H_

#include <string>
#include "cJSON.h"

namespace CommonUtils
{
class JsonUtil
{
public:
	static std::string JsonToString(cJSON *root);
	static std::string JsonToUtf8String(cJSON *root);
	static void JsonDelete(cJSON *root);
private:
	JsonUtil();
	JsonUtil(const JsonUtil &ju);
	JsonUtil& operator = (const JsonUtil &ju);
};
}



#endif /* INCLUDE_JSONUTIL_H_ */
