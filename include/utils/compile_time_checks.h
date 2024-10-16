#ifndef __DOMOTICS_UTILS_COMPILE_TIME_CHECKS_H__
#define __DOMOTICS_UTILS_COMPILE_TIME_CHECKS_H__

namespace Utils {
/**
 * \internal
 * Namespace containing all compile time checks. These are used to create better (and more advanced) error
 * messages using static_assert
 */
namespace CompileTimeChecks {

/**
 * \internal
 * Checks whether two types are the same. This is the is not equal variant
 */
template <class T, class U>
struct is_same
{
    enum
    {
        value = 0
    };
};

/**
 * \internal
 * Checks whether two types are the same. This is the is equal variant
 */
template <class T>
struct is_same<T, T>
{
    enum
    {
        value = 1
    };
};

template <bool B, class T = void>
struct enable_if
{
};

template <class T>
struct enable_if<true, T>
{
    typedef T type;
};
} // namespace CompileTimeChecks
} // namespace Utils

#endif