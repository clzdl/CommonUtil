/*
 * CharsetUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */

#include "CharsetUtil.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

namespace CommonUtils
{


int CharsetUtil::Uft8ToGb18030(std::string &src , std::string &dest)
{
	char strOut[4096]={0};
	if(src == "")
		return 0;

    //首先先将utf8编码转换为unicode编码
    //设置转换为unicode前的码,当前为utf8编码
    if(NULL==setlocale(LC_ALL,"zh_CN.utf-8"))
    {
        printf("[%s,%d]Bad Parameter\n" , __FILE__, __LINE__);
        return -1;
    }
  	//计算转换后的长度
    int unicodeLen=mbstowcs(NULL,src.c_str(),0);
    if(unicodeLen<=0)
    {
        printf("[%s,%d]Can not Transfer!!!\n",__FILE__,__LINE__);
        return -1;
    }
    wchar_t *unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);
    mbstowcs(unicodeStr,src.c_str(),src.length());//将utf8转换为unicode

    //将unicode编码转换为GB18030编码
    //设置unicode转换后的码,当前为gb18030
    if(NULL==setlocale(LC_ALL,"zh_CN.gb18030"))
    {
    	free(unicodeStr);
        printf("[%s,%d]Bad Parameter\n" , __FILE__ ,__LINE__ );
        return -1;
    }
    int gbLen=wcstombs(NULL,unicodeStr,0);//计算转换后的长度
    if(gbLen<=0)
    {
    	free(unicodeStr);
        printf("[%s,%d]Can not Transfer!!!\n",__FILE__,__LINE__);
        return -1;
    }

    wcstombs(strOut,unicodeStr,gbLen);
    free(unicodeStr);
	dest.append(strOut);
    return gbLen;
}

int CharsetUtil::Gb18030ToUtf8(std::string &src , std::string &dest)
{
	char strOut[4096]={0};
	if(src == "")
		return 0;

    //首先先将gb18030编码转换为unicode编码

    //设置转换为unicode前的码,当前为gb18030编码
    if(NULL==setlocale(LC_ALL,"zh_CN.gb18030"))
    {
        printf("[%s,%d]Bad Parameter\n" , __FILE__ , __LINE__ );
        return -1;
    }
  	//计算转换后的长度
    int unicodeLen=mbstowcs(NULL,src.c_str(),0);
    if(unicodeLen<=0)
    {
        printf("[%s,%d]Can not Transfer!!!\n" , __FILE__ ,__LINE__);
        return -1;
    }
    wchar_t *unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);

	//将gb18030转换为unicode
    mbstowcs(unicodeStr,src.c_str(),src.length());

    //将unicode编码转换为uft8编码
    //设置unicode转换后的码,当前为uft8
    if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))
    {
    	free(unicodeStr);
        printf("[%s,%d]Bad Parameter\n",__FILE__ , __LINE__);
        return -1;
    }
	//计算转换后的长度
    int gbLen=wcstombs(NULL,unicodeStr,0);
    if(gbLen<=0)
    {
    	free(unicodeStr);
        printf("[%s,%d]Can not Transfer!!!\n", __FILE__ , __LINE__);
        return -1;
    }

    wcstombs(strOut,unicodeStr,gbLen);
    free(unicodeStr);
	dest.append(strOut);
    return gbLen;
}



unsigned char* CharsetUtil::Utf8StringSub(const unsigned char* src , unsigned char *dest , int len , int offset)
{
    const unsigned char *p = src;
    unsigned char *q = dest;
    unsigned int iSubLen = 0;
    unsigned int iOffset = 0;
    unsigned int uiStep = 0;


    while(*p)
    {
        if(*p >= 0xFC)///6字节
            uiStep = 6;
        else if(*p >= 0xF8) ///5字节
            uiStep = 5;
        else if(*p >= 0xF0 )///4字节
            uiStep = 4;
        else if(*p >= 0xE0 )///3字节
            uiStep = 3;
        else if(*p >= 0xC0)///2字节
            uiStep = 2;
        else if(*p < 0x80) ///1字节
            uiStep = 1;
        else
        {

            return NULL;
        }

        if(iSubLen + uiStep > len)
            return dest;

        if(iOffset >= offset)
        {
            memcpy(q , p , uiStep);
            q += uiStep;  ///目的字符串后移
            iSubLen += uiStep;   ///截取字符串长度
        }
        else
            ++iOffset;

        p += uiStep;  ///原始字符串后移

    }

    return dest;
}

}
