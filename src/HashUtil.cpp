/*
 * PubFunUtil.cpp
 *
 *  Created on: 2017年9月25日
 *      Author: cplusplus
 */

#include <HashUtil.h>
#include <sys/types.h>

namespace CommonUtils
{

unsigned  int  HashUtil::ELFHash(const char   * str)
{
    /*************************变量定义***************************/
    unsigned  int  hash  =   0 ;
    unsigned  int  x     =   0 ;
    /************************************************************/

    /***********************哈希字符串***************************/
    while  ( * str)
    {
        hash  =  (hash  <<   4 )  +  ( * str ++ );
        if  ((x  =  hash  &   0xF0000000L )  !=   0 )
        {
            hash  ^=  (x  >>   24 );
            hash  &=   ~ x;
        }
    }
    /************************************************************/
    return  (hash  &   0x7FFFFFFF );/*返回的哈希值*/
}


}

