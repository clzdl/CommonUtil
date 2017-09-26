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
	bool IsDirectoryExist(const char *strPath);

	/*@action:用于创建目录，必须确保父目录存在
	 *@param：
	 *		path--入参，目录路径
	 *@return：0-success；-1-fail
	 */
	int Mkdir(const char *path);

	/*@action:用于移动文件
	 *@param：
	 *		strSrc--入参，源文件路径
	 *		strDest--入参，目的路径
	 *@return：0-success；-1-fail
	 */
	int MoveFile(const char *strSrc ,const char *strDest);
};


}



#endif /* INCLUDE_FILEUTIL_H_ */
