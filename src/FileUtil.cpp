/*
 * FileUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#include "FileUtil.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

namespace CommonUtils
{

bool FileUtil::IsFileExist(const std::string &strFile)
{
	if(0== access(strFile.c_str() , F_OK) )
		return true;
	else
		return false;
}

long FileUtil::GetFileSize(const char* strFileName)
{
	struct stat fstat;

	if(access(strFileName,F_OK) != 0)
		return -1;

	if(stat(strFileName,&fstat) < 0)
		return -1;

	return (long)fstat.st_size;
}

long FileUtil::GetFileSize(std::string strFileName)
{
	struct stat fstat;

	if(access(strFileName.c_str(),F_OK) != 0){

		return(-1);
	}

	if(stat(strFileName.c_str(),&fstat) < 0){
		return(-1);
	}
	return((long)fstat.st_size);
}


int FileUtil::MoveFile(const char *strSrc ,const char *strDest)
{
	if( GetFileSize( strSrc ) >0 )
		return rename( strSrc , strDest);
	else
		return remove( strSrc );
}


bool FileUtil::IsDirectoryExist(const char * strPath)
{
	struct stat sb;
	if(0 == stat(strPath , &sb) )
	{
		switch(sb.st_mode & S_IFMT )
		{
			case S_IFDIR:
				return true;
			default:
				return false;
		}
	}

	return false;

}


int FileUtil::Mkdir(const char *path)
{
	return mkdir(path, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
}


time_t FileUtil::GetFileLastModificationTime(std::string strFileName)
{
	struct stat fstat;

	if(access(strFileName.c_str(),F_OK) != 0)
		return -1;

	if(stat(strFileName.c_str(),&fstat) < 0)
		return -1;

	return((long)fstat.st_mtime);
}

time_t FileUtil::GetFileLastModificationTime(const char* strFileName)
{
	struct stat fstat;

	if(access(strFileName,F_OK) != 0)
		return -1;

	if(stat(strFileName,&fstat) < 0)
		return -1;

	return((long)fstat.st_mtime);
}

}

