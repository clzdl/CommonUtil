/*
 * CharsetUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_CHARSETUTIL_H_
#define INCLUDE_CHARSETUTIL_H_

#include <string>


namespace CommonUtils
{

class CharsetUtil
{
public:
	/*@action:用于Utf8字符串转换为GB18030字符集下的字符串
	 *@param：
	 *		src--入参，待转换字符串
	 *		dest--出参，转换后的字符串
	 *@return：0-success；-1-fail
	 */
	int Uft8ToGb18030(std::string &src , std::string &dest);

	/*@action:用于GB18030字符串转换为utf8字符集下的字符串
	 *@param：
	 *		src--入参，待转换字符串
	 *		dest--出参，转换后的字符串
	 *@return：0-success；-1-fail
	 */
	int Gb18030ToUtf8(std::string &src , std::string &dest);

	/*@action: 用于截取utf8字符串，防止中英文截取出现乱码(函数不检验源字符串是否为utf8,需要调用者保证原字符串准确性)
	 *@param:
	 *      src--入参，原字节流
	 *      dest--出参，截取后的字节流
	 *      len--入参，按字节数的长度
	 *      offset--入参，字符的偏移数
	 *@return: NULL/substring
	 */
	unsigned char* Utf8StringSub(const unsigned char* src , unsigned char *dest , int len , int offset =0);
};


}


#endif /* INCLUDE_CHARSETUTIL_H_ */
