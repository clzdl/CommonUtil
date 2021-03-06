/*
 * FileUtil.h
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#ifndef INCLUDE_FILEUTIL_H_
#define INCLUDE_FILEUTIL_H_

#include <string>

namespace CommonUtils
{

class FileUtil
{
public:


	/*@action:用于文件已被锁定，用于实现程序单实例
	 *@param：
	 *		inFileName--入参，文件路径
	 *@return：0-success；-1-fail
	 */
	static short CheckUniqueCopy( const char *inFileName );

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
	static long GetFileSize(const char* strFileName);

	/*@action:用于获取文件大小（字节数）
	 *@param：
	 *		strFileName--入参，文件路径
	 *@return：-1-fail；>=0 文件大小
	 */
	static long GetFileSize(std::string strFileName);

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

	/*@action:用于判断目录是否存在
	 *@param：
	 *		strPath--入参，目录路径
	 *@return：增减后的月份
	 */
	static bool IsDirectoryExist(const char *strPath);

	/*@action:用于创建目录，必须确保父目录存在
	 *@param：
	 *		path--入参，目录路径
	 *@return：0-success；-1-fail
	 */
	static int Mkdir(const char *path);

	/*@action:用于移动文件
	 *@param：
	 *		strSrc--入参，源文件路径
	 *		strDest--入参，目的路径
	 *@return：0-success；-1-fail
	 */
	static int MoveFile(const char *strSrc ,const char *strDest);

	/*
	 *Function : 文件或目录是否存在
	 *Input    : pathname 文件
	 *Output   : 无
	 *Return   : true 是，false 否
	 *Desc     : pathname支持简单通配
	 */
	static bool IsExistFileByRe(const char *pathname );

	/*
	 *Function : 文件剪切、重命名
	 *Input    : src 源文件，dest 目的文件
	 *Output   : 无
	 *Return   : SUCCESS 成功，FAIL 失败
	 */
	static int MultiRename(const char *src, const char *dest );
private:
	FileUtil();
	FileUtil(const FileUtil &fu);
	FileUtil& operator = (const FileUtil &fu);
};


}



#endif /* INCLUDE_FILEUTIL_H_ */
