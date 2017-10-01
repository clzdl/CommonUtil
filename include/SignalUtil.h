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

/**
 * 信号工具类
 */
class SignalUtil
{
public:
	/**
	 * 捕捉信号
	 */
	static void CatchSignal(std::vector<int> &signals,void (*Func)(int) );

	/**
	 * 向本进程发送信号
	 */
	static int SendSignal(int signal);

private:
	SignalUtil();
	SignalUtil(const SignalUtil &su);
	SignalUtil& operator = (const SignalUtil &su);

};
}




#endif /* INCLUDE_SIGNALUTIL_H_ */
