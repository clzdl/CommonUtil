/*
 * EnvUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_ENVUTIL_H_
#define INCLUDE_ENVUTIL_H_

#include <string>

namespace CommonUtils
{

class EnvUtil
{
public:
	/*@action:用于替换字符串中的环境变量 ${name}
	 *@param：
	 *		value--入参，待替换字符串
	 *@return：none
	 */
	void EnvVarReplace(std::string &value);
};


}



#endif /* INCLUDE_ENVUTIL_H_ */
