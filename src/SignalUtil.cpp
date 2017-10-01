/*
 * SignalUtil.cpp
 *
 *  Created on: 2017年10月1日
 *      Author: cplusplus
 */



#include "SignalUtil.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

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

int SignalUtil::SendSignal(int signal)
{
	pid_t pid = getpid();
	return kill(pid , signal);
}

}
