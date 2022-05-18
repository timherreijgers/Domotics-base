#ifndef __DOMOTICS_UTILS_COMPILE_TIME_CHECKS_H__
#define __DOMOTICS_UTILS_COMPILE_TIME_CHECKS_H__

namespace CompileTimeChecks
{
    template<class T, class U>
    struct is_same {
        enum { value = 0 };
    };

    template<class T>
    struct is_same<T, T> {
        enum { value = 1 };
    };
}

#endif