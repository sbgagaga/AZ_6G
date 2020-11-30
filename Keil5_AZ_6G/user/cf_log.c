#include <string.h>
#include "cf_log.h"

#define ON  (1)
#define OFF (0)

#define CF_ERROR_SWITCH  ON
#define CF_DEBUG_SWITCH  ON

#if (CF_ERROR_SWITCH || CF_DEBUG_SWITCH)
	static char sz[1024] = { 0 };
#endif

void cf_loge(const char *fmt, ...)
{
	#if CF_ERROR_SWITCH
		va_list ap;
		memset(sz, 0, 1024);
		/* 组合使用可变参数以及vsprintf，实现printf */
		va_start(ap, fmt);
		vsprintf(sz, fmt, ap); 
		printf(sz);
		va_end(ap);
	#endif
}

void cf_logd(const char *fmt, ...)
{
	#if CF_DEBUG_SWITCH
		va_list ap;
		memset(sz, 0, 1024);
		/* 组合使用可变参数以及vsprintf，实现printf */
		va_start(ap, fmt);
		vsprintf(sz, fmt, ap); 
		printf(sz);
		va_end(ap);
	#endif	
}
