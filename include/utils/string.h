#ifndef __DOMOTICS_UTILS_STRING_H__
#define __DOMOTICS_UTILS_STRING_H__

#include "compile_time_checks.h"

namespace Utils
{
	template<typename Arg>
	void appendStrings(char * buffer, Arg arg)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value, "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
	}

	template<typename Arg, typename... Args>
	void appendStrings(char * buffer, Arg arg, Args... args)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value,  "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
		appendStrings(buffer, args...);
	}
}
#endif
