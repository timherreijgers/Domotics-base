#ifndef __DOMOTICS_UTILS_STRING_H__
#define __DOMOTICS_UTILS_STRING_H__

#include <inttypes.h>

#include "compile_time_checks.h"

/**
 * Namespace containing all utility functions/classes
 */
namespace Utils
{
	template<typename Arg>
	void appendStringsUnsafe(char * buffer, Arg arg)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value, "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
	}

	/** 
	 * Appends multiple C-style string into the provided buffer. The user is responsible for making sure the buffer is cleared before appending. 
	 * This variant of the function will not check whether the string will fit into the buffer, for this see ::appendStrings(char *, size_t, Arg, Args...)
	 * 
	 * \param buffer The buffer to write into
	 * \param args The strings to append
	 */
	template<typename Arg, typename... Args>
	void appendStringsUnsafe(char * buffer, Arg arg, Args... args)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value,  "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
		appendStringsUnsafe(buffer, args...);
	}

	template<typename Arg>
	bool appendStrings(char * buffer, size_t size, Arg arg)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value, "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
		return true;
	}

	/**
	 * Appends multiple C-style string into the provided buffer. The user is responsible for making sure the buffer is cleared before appending. 
	 * This variant will return whether the appending has finished succesfully. This variant is slower then the usafe variant
	 * as it will check the length of the string before appending for every string. If speed is more important then reliabilty, use ::appendStringsUnsafe(char *, Arg, Args...) 
	 * (WIP)
	 * 
	 * \param buffer The buffer to write into
	 * \param size The size of the buffer
	 * \param args The strings to append
	 * 
	 * \returns Whether the appending was succesfull
	 */
	template<typename Arg, typename... Args>
	bool appendStrings(char * buffer, size_t size, Arg arg, Args... args)
	{
		static_assert(CompileTimeChecks::is_same<Arg, const char *>::value,  "The input for appendStrToBuffer can only be a string literal");
		strcat(buffer, (const char *) arg);
		return appendStringsUnsafe(buffer, args...);
	}
}
#endif
