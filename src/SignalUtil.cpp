/*
 * SignalUtil.cpp
 *
 *  Created on: 2017年10月1日
 *      Author: cplusplus
 */



#include "SignalUtil.h"
#include <signal.h>

namespace CommonUtils
{
void SignalUtil::CatchSignal(std::vector<int> &signals,void (*Func)(int) )
{
	struct sigaction sa;
	sa.sa_handler = Func;
	sa.sa_flags   = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	for(auto it = signals.begin(); it != signals.end(); ++it)
	{
		sigaction(*it,  &sa, 0);
	}
}
}
