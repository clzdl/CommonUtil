/*
 * Md5Util.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#include "Md5Util.h"
#include "openssl/md5.h"
#include <fstream>
#include "string.h"

namespace CommonUtils
{


int Md5Util::Md5FileSummary(std::string strFileName , std::string &outMd5Sum)
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
		snprintf(strHex ,sizeof(strHex), "%02x" , md5[i]);
		outMd5Sum.append(strHex);
	}
	return 0;
}


int Md5Util::Md5StringSummary(std::string strData , std::string &outMd5Sum)
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
        snprintf(strHex ,sizeof(strHex), "%02x" , md5[i]);
        outMd5Sum.append(strHex);
    }
    return 0;
}

}

