/*
 * PubFunUtil.cpp
 *
 *  Created on: 2017年9月25日
 *      Author: cplusplus
 */

#include "PubFunUtil.h"
#include <unistd.h>
#include "openssl/md5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <stdlib.h>
#include "string.h"
#include "StringUtil.h"

namespace CommonUtils
{

int PubFunUtil::Md5FileSummary(std::string strFileName , std::string &outMd5Sum)
{

	char strBuff[4096+1];
	MD5_CTX c;
    unsigned char md5[17]={0};
	char strHex[2+1];

	std::ifstream inFile(strFileName.c_str());
	if(!inFile.is_open())
		return -1;


	MD5_Init(&c);

	while(!inFile.eof())
	{
		memset(strBuff , 0 ,sizeof(strBuff));
		inFile.read(strBuff, 4096);

		MD5_Update(&c, strBuff, strlen(strBuff));
	}

	MD5_Final(md5,&c);

	for(int i = 0; i < 16; i++)
	{
		memset(strHex , 0 ,sizeof(strHex));
		sprintf(strHex , "%02.2x" , md5[i]);
		outMd5Sum.append(strHex);
	}
	return 0;
}


int PubFunUtil::Md5StringSummary(std::string strData , std::string &outMd5Sum)
{
    MD5_CTX c;
    char strHex[2+1];
    unsigned char md5[17]={0};


    MD5_Init(&c);
    MD5_Update(&c, strData.c_str(), strData.length());
    MD5_Final(md5,&c);

    for(int i = 0; i < 16; i++)
    {
        memset(strHex , 0 ,sizeof(strHex));
        sprintf(strHex , "%02.2x" , md5[i]);
        outMd5Sum.append(strHex);
    }
    return 0;
}

std::string PubFunUtil::Number2String(long lValue)
{
    return StringUtil::toString<long>(lValue);
}

std::string PubFunUtil::Float2String(double dValue)
{
    return StringUtil::toString<double>(dValue);
}

bool PubFunUtil::IsFileExist(const std::string &strFile)
{
	if(0== access(strFile.c_str() , F_OK) )
		return true;
	else
		return false;
}

long PubFunUtil::getFileSize(const char* strFileName)
{
	struct stat fstat;

	if(access(strFileName,F_OK) != 0)
		return -1;

	if(stat(strFileName,&fstat) < 0)
		return -1;

	return (long)fstat.st_size;
}

long PubFunUtil::getFileSize(std::string strFileName)
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

}

