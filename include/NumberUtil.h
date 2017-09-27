/*
 * NumberUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_NUMBERUTIL_H_
#define INCLUDE_NUMBERUTIL_H_

#include <string>

namespace CommonUtils
{

class NumberUtil
{
public:
	/*@action:非浮点型数字转换为字符串
	 *@param：
	 *		lValue--入参，待转换数字
	 *@return：数字字符串
	 */
	static std::string Number2String(long lValue);

	/*@action:浮点型数字转换为字符串
	 *@param：
	 *		lValue--入参，待转换数字
	 *@return：数字字符串
	 */
	static std::string Float2String(double dValue);

	/*@action: 用于判断字符串是否全数字判断
	 *@param:
	 *      strSrc--入参，带判断字符串
	 *@return：  true/ false
	 */
	static bool IsDigitString(std::string strSrc);

private:
	NumberUtil();
	NumberUtil(const NumberUtil &nu);
	NumberUtil& operator = (const NumberUtil &nu);
};

}



#endif /* INCLUDE_NUMBERUTIL_H_ */
