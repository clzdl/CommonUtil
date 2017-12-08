/*
 * DateUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#include "DateUtil.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <stdlib.h>
#include "string.h"
#include <sys/time.h>


namespace CommonUtils
{


int DateUtil::AddMonth(int yearmonth, int addmonth)
{
	int a = 0;
	if (addmonth >= 0)
	{
		a =  (yearmonth/100 + (yearmonth%100 + addmonth)/12)*100 + (yearmonth%100+addmonth)%12;
	}
	else
		a = (yearmonth/100+((yearmonth%100+addmonth-12)/12))*100+(yearmonth%100+addmonth%12+12)%12;
	if (a%100==0)
	{
		return addmonth>=0?(a/100-1)*100+12:a+12;
	}
	else
		return a;
}


char* DateUtil::GetSysdateUsec(char *info)
{
    struct timeval tv;
    struct timezone tz;
    struct tm cur_time;
    gettimeofday (&tv, &tz);
    localtime_r (&(tv.tv_sec), &cur_time);
    sprintf (info, "%04d%02d%02d%02d%02d%02d%06ld", cur_time.tm_year+1900, cur_time.tm_mon + 1, cur_time.tm_mday, cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec, tv.tv_usec);
    info[20] = '\0';

    return info;
}


char* DateUtil::GetCurrentTime(int format, char* stime)
{
    struct tm ptm;
    time_t now;
    char formatstring[30];
    char datetimestring[50];
    struct timeval start;

    memset(datetimestring, 0, sizeof(datetimestring));

    time(&now);
    localtime_r(&now , &ptm);
    gettimeofday(&start,NULL);
    if(format == 0) /*YYYYMMDD*/
        strcpy(formatstring, "%d%02d%02d");
    else if(format == 1) /*YYYY/MM/DD*/
        strcpy(formatstring, "%d/%02d/%02d");
    else if(format == 2) /*YYYY->MM->DD*/
        strcpy(formatstring, "%d->%02d->%02d");
    else if(format == 3) /*HH:MM:SS*/
        strcpy(formatstring, "%02d:%02d:%02d:%ld");
    else if(format == 4) /*HHMMSS*/
        strcpy(formatstring, "%02d%02d%02d");
    else if(format == 13) /*YYYY/MM/DD HH:MM:SS*/
        strcpy(formatstring, "%d%02d%02d%02d%02d%02d");
    else
        strcpy(formatstring, "%d%02d%02d");

    if (format <= 2)
        sprintf(datetimestring, formatstring, 1900 + ptm.tm_year, ptm.tm_mon + 1,     ptm.tm_mday);
    else if (format == 3)
        sprintf(datetimestring, formatstring, ptm.tm_hour,     ptm.tm_min, ptm.tm_sec,start.tv_usec);
    else if (format <= 4)
        sprintf(datetimestring, formatstring, ptm.tm_hour,     ptm.tm_min, ptm.tm_sec);
    else
        sprintf(datetimestring, formatstring, 1900 + ptm.tm_year, ptm.tm_mon + 1,     ptm.tm_mday, ptm.tm_hour, ptm.tm_min, ptm.tm_sec);

    strcpy(stime, datetimestring);

    return stime;
}

//获取指定月份的天数
int DateUtil::GetDaysOfMonth(int y,int m)
{
    int day[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if (2 == m)
        return ((0 == y%4 && 0 != y%100 )||(0==y%400)) ? 29 : 28;
    else
        return day[m-1];
}

int DateUtil::DiffMons(int begMon , int endMon)
{
	if(begMon < 197001 || begMon >  999999 || endMon< 197001 || endMon > 999999)
		THROW(DateUtilException , "DiffMons parameter error,must　yyyymmdd");

	if(begMon > endMon)
		std::swap(begMon,endMon);

	if(begMon/100 == endMon/100)
		return endMon-begMon;
	else
		return (endMon/100-begMon/100)*12 +(12-begMon%100) + endMon%100;
}

}


