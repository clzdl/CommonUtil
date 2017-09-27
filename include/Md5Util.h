/*
 * Md5Util.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_MD5UTIL_H_
#define INCLUDE_MD5UTIL_H_

#include <string>

namespace CommonUtils
{

class Md5Util
{
public:
	/*@action:用于生成文件md5摘要信息
	 *@param：
	 *		strFileName--入参，文件路径
	 *		outMd5Sum--出参，生成的md5摘要信息
	 *@return：0-success；-1-fail
	 */
	static int Md5FileSummary(std::string strFileName , std::string &outMd5Sum);


	/*@action:用于字符串的md5摘要信息
	 *@param：
	 *      strData--入参，文件路径
	 *      outMd5Sum--出参，生成的md5摘要信息
	 *@return：0-success；-1-fail
	 */
	static int Md5StringSummary(std::string strData , std::string &outMd5Sum);

private:
	Md5Util();
	Md5Util(const Md5Util& mu);
	Md5Util& operator = (const Md5Util& mu);
};


}



#endif /* INCLUDE_MD5UTIL_H_ */
