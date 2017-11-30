/*
 * TplUtil.h
 *
 *  Created on: 2017年11月29日
 *      Author: cplusplus
 */

#ifndef INCLUDE_TPLUTIL_H_
#define INCLUDE_TPLUTIL_H_

#include <memory>

namespace CommonUtils{
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


}

#endif /* INCLUDE_TPLUTIL_H_ */
