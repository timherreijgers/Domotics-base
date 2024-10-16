#ifndef __DOMOTICS_UTILS_STRING_LITERAL_H__
#define __DOMOTICS_UTILS_STRING_LITERAL_H__

/**
 * \file string_literal.h
 *
 * File containing a simple wrapper for a string_literal
 */

/**
 * \brief Small wrapper around string literals to enable saving references to them in class members
 *
 * The goal of this wrapper is to be able to save a reference to a string literal within a class. The wrapper itself
 * doesn't enforce that the saved string is actually a literal and mostly serves as a reminder for the developer
 * that this parameters should be string literal.
 */
class string_literal
{
public:
    /**
     * Constructor that sets the string literal
     *
     * @param string The string literal
     */
    explicit string_literal(const char* string)
        : m_string(string)
    {
    }

    /**
     *
     * Function that gets the string literal back from the wrapper.
     *
     * @return The contained string literal
     */
    [[nodiscard]] auto string() const noexcept -> const char*
    {
        return m_string;
    }

    /**
     * Conversion operator to allow casting back to a raw string pointer
     */
    [[nodiscard]] explicit constexpr operator const char*() const noexcept
    {
        return m_string;
    }
private:
    const char* m_string;
};

#endif // __DOMOTICS_UTILS_STRING_LITERAL_H__