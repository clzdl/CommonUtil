/*
 * DateUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_DATEUTIL_H_
#define INCLUDE_DATEUTIL_H_

namespace CommonUtils
{

class DateUtil
{
public:
	/*@action:用于增加月数
	 *@param：
	 *		yearmonth--入参，年月
	 *		addmonth--入参，增减的差值
	 *@return：增减后的月份
	 */
	int AddMonth(int yearmonth, int addmonth);

	/*@action: 用于当前时间的字符串精确到微妙
	 *@param:
	 *      *strSrc--入参，带判断字符串
	 *@return： char*
	 */
	char* GetSysdateUsec(char *info);

	/*@action: 根据时间格式串生成系统时间
	 *@param:
	 *      format-入参，
	 *      stime-初参；
	 *@retrun:
	 */
	char* GetCurrentTime(int format, char* stime);
};


}



#endif /* INCLUDE_DATEUTIL_H_ */
