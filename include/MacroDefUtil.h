/*
 * MacroDefUtil.h
 *
 *  Created on: 2017年9月30日
 *      Author: cplusplus
 */

#ifndef INCLUDE_MACRODEFUTIL_H_
#define INCLUDE_MACRODEFUTIL_H_


namespace CommonUtils{

#ifdef _DEBUG
#define _TRACE_MSG(FMT, ...)      fprintf(stdout,"[%s,%d]" FMT "\n" ,__FILE__ ,__LINE__, ##__VA_ARGS__)
#else
#define _TRACE_MSG(FMT, ...)
#endif

}


#endif /* INCLUDE_MACRODEFUTIL_H_ */
