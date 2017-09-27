/*
 * JsonUtil.cpp
 *
 *  Created on: 2017年9月27日
 *      Author: cplusplus
 */

#include "JsonUtil.h"
#include <sys/types.h>
#include <locale.h>     /* struct lconv, setlocale, localeconv */
#include <stdlib.h>
#include <stdio.h>

namespace CommonUtils{


static int Gb18030String2Utf8(std::string &src , std::string &dest)
{
	char strOut[4096]={0};
	if(src == "")
		return 0;

    if(NULL==setlocale(LC_ALL,"zh_CN.gb18030"))
    {
        fprintf(stderr, "[%s,%d] Bad Parameter \n" , __FILE__ , __LINE__);
        return -1;
    }
  	//计算转换后的长度
    int unicodeLen=mbstowcs(NULL,src.c_str(),0);
    if(unicodeLen<=0)
    {
        fprintf(stderr, "[%s,%d] Can not Transfer \n" , __FILE__ , __LINE__);
        return -1;
    }
    wchar_t *unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);

	//转换为unicode
    mbstowcs(unicodeStr,src.c_str(),src.length());

    //将unicode编码转换为uft8编码
    if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))
    {
    	free(unicodeStr);
        fprintf(stderr, "[%s,%d] Bad Parameter\n" , __FILE__ , __LINE__);
        return -1;
    }
	//计算转换后的长度
    int gbLen=wcstombs(NULL,unicodeStr,0);
    if(gbLen<=0)
    {
    	free(unicodeStr);
    	fprintf(stderr, "[%s,%d] Can not Transfer \n" , __FILE__ , __LINE__);
        return -1;
    }

    wcstombs(strOut,unicodeStr,gbLen);
    free(unicodeStr);

	dest.append(strOut);

    return gbLen;
}

static int Utf8ToGb18030(std::string &src , std::string &dest)
{
	char strOut[4096]={0};
	if(src == "")
		return 0;

        //将unicode编码转换为uft8编码
    if(NULL== setlocale(LC_ALL,"zh_CN.utf8") )
    {
    	fprintf(stderr, "[%s,%d] Bad Parameter \n" , __FILE__ , __LINE__);
        return -1;
    }
  	//计算转换后的长度
    int unicodeLen=mbstowcs(NULL,src.c_str(),0);
    if(unicodeLen<=0)
    {
    	fprintf(stderr, "[%s,%d] Can not Transfer \n" , __FILE__ , __LINE__);
        return -1;
    }
    wchar_t *unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);

	//转换为unicode
    mbstowcs(unicodeStr,src.c_str(),src.length());

    //将unicode编码转换为gb18030编码
    if(NULL==setlocale(LC_ALL,"zh_CN.gb18030"))
    {
    	free(unicodeStr);
    	fprintf(stderr, "[%s,%d] Bad Parameter \n" , __FILE__ , __LINE__);
        return -1;
    }
	//计算转换后的长度
    int gbLen=wcstombs(NULL,unicodeStr,0);
    if(gbLen<=0)
    {
    	free(unicodeStr);
    	fprintf(stderr, "[%s,%d] Can not Transfer \n" , __FILE__ , __LINE__);
        return -1;
    }

    wcstombs(strOut,unicodeStr,gbLen);
    free(unicodeStr);

	dest.append(strOut);

    return gbLen;
}

std::string JsonUtil::JsonToString(cJSON *root)
{
	char *out = NULL;
	///20150805
	out = cJSON_PrintUnformatted(root);    ///非格式化输出
	if(NULL == out)
		return "";
	std::string strResult;
	strResult.append(out);
	free(out);

	return strResult;

}
std::string JsonUtil::JsonToUtf8String(cJSON *root)
{
	char *out = NULL;

	///////20150805
	out=cJSON_PrintUnformatted(root);   ///非格式化输出
	if(NULL == out)
		return "";

	std::string strResult;
	std::string strUtf8Result;

	strResult.append(out);
	free(out);

	if(-1 ==  Gb18030String2Utf8(strResult , strUtf8Result) )
		return "";

	return strUtf8Result;
}
void JsonUtil::JsonDelete(cJSON *root)
{
	if(NULL != root)
	{
		cJSON_Delete(root);
		root = NULL;
	}
}


}




