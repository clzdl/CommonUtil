#ifndef _PUBLIC_FUN_UTIL_H_
#define _PUBLIC_FUN_UTIL_H_
#include <string>

namespace CommonUtils
{

class PubFunUtil
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

	/*@action:用于判断文件是否存在
	 *@param：
	 *		strFile--入参，文件路径
	 *@return：true/false
	 */
	static bool IsFileExist(const std::string &strFile);

	/*@action:用于获取文件大小（字节数）
	 *@param：
	 *		strFileName--入参，文件路径
	 *@return：-1-fail；>=0 文件大小
	 */
	static long getFileSize(const char* strFileName);

	/*@action:用于获取文件大小（字节数）
	 *@param：
	 *		strFileName--入参，文件路径
	 *@return：-1-fail；>=0 文件大小
	 */
	static long getFileSize(std::string strFileName);

	/*@action:用于获取文件最近的修改时间
	 *@param：
	 *		strFileName--入参，文件路径
	 *@return：-1-fail； else success
	 */
	static time_t GetFileLastModificationTime(std::string strFileName);

	/*@action:用于获取文件最近的修改时间
	 *@param：
	 *		strFileName--入参，文件路径
	 *@return：-1-fail； else success
	 */
	static time_t GetFileLastModificationTime(const char* strFileName);
};
}

#endif
