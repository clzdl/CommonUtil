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
#include <fcntl.h>
#include <errno.h>
#include "string.h"

namespace CommonUtils
{


short FileUtil::CheckUniqueCopy( const char *inFileName )
{
    int pid_file_fd;
    int flag;
    char line[1048];

    struct flock lock;

    /* open the PID file, create if nonexistent */
    pid_file_fd = open(inFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(pid_file_fd == -1)
    {
        return -1;
    }

    lock.l_type   = F_WRLCK;
    lock.l_start  = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len    = 0;
    flag = fcntl(pid_file_fd, F_SETLK, &lock);
    if(flag < 0)
    {
       if(errno == EACCES || errno == EAGAIN)
       {
          close(pid_file_fd);
          return -1;
       }
       else
       {
          close(pid_file_fd);
          return -1;
       }
    }

    ftruncate(pid_file_fd, 0);
    sprintf(line, "%ld\n", (long)getpid());
    write(pid_file_fd, line, strlen(line));

    return 0;
}

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

