/*
 * SignalUtil.h
 *
 *  Created on: 2017年10月1日
 *      Author: cplusplus
 */

#ifndef INCLUDE_SIGNALUTIL_H_
#define INCLUDE_SIGNALUTIL_H_

#include <vector>
namespace CommonUtils
{
class SignalUtil
{
public:
	/**
	 * 捕捉信号
	 */
	void CatchSignal(std::vector<int> signals,void (*Func)(int) );

private:
	SignalUtil();
	SignalUtil(const SignalUtil &su);
	SignalUtil& operator = (const SignalUtil &su);

};
}




#endif /* INCLUDE_SIGNALUTIL_H_ */
