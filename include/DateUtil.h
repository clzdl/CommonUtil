/*
 * DateUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_DATEUTIL_H_
#define INCLUDE_DATEUTIL_H_
#include "Exception.h"

namespace CommonUtils
{
DECLARE_EXCEPTION(DateUtilException, Exception);
class DateUtil
{
public:
	/*@action:用于增加月数
	 *@param：
	 *		yearmonth--入参，年月
	 *		addmonth--入参，增减的差值
	 *@return：增减后的月份
	 */
	static int AddMonth(int yearmonth, int addmonth);

	/*@action: 用于当前时间的字符串精确到微妙
	 *@param:
	 *      *strSrc--入参，带判断字符串
	 *@return： char*
	 */
	static char* GetSysdateUsec(char *info);

	/*@action: 根据时间格式串生成系统时间
	 *@param:
	 *      format-入参，
	 *      stime-初参；
	 *@retrun:
	 */
	static char* GetCurrentTime(int format, char* stime);

	/**
	 * 获取指定年月的天数
	 */
	static int GetDaysOfMonth(int y,int m);

	/**
	 * 获取月份间隔数，不含当月
	 */
	static int DiffMons(int begMon , int endMon);
private:
	DateUtil();
	DateUtil(const DateUtil &du);
	DateUtil& operator = (const DateUtil &du);
};


}



#endif /* INCLUDE_DATEUTIL_H_ */
