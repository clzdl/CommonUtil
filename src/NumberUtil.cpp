/*
 * NumberUtil.cpp
 *
 *  Created on: 2017年9月26日
 *      Author: cplusplus
 */


#include "NumberUtil.h"
#include <unistd.h>
#include <sys/types.h>
#include "StringUtil.h"

namespace CommonUtils
{

std::string NumberUtil::Number2String(long lValue)
{
    return StringUtil::toString<long>(lValue);
}

std::string NumberUtil::Float2String(double dValue)
{
    return StringUtil::toString<double>(dValue);
}


bool NumberUtil::IsDigitString(std::string strSrc)
{
    for(std::string::iterator it = strSrc.begin() ; it != strSrc.end(); ++it)
        if(0 == isdigit(*it))
            return false;

    return true;
}



}

