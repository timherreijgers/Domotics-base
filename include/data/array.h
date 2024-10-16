#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>

#include "generic_data_iterator.h"

namespace Data {

/**
 *
 * \brief Wrapper around c-style arrays
 *
 * This class provides an easy way to handle compile size known arrays. The size of the array must be bigger than zero,
 * and is specified using the N templates argument. The array is only able to store one datatype, just like c-style arrays, which
 * is specified by the T templates argument.
 *
 * The goal of this class is to add more functionality to a standard C-style array. At this point in time this class is purely a
 * wrapper around a C-style array, which tries to stay true to the C-style array interface. Planned features are, but are not limited
 * to: Support range based for loops, fill function, find functions, etc. Besides these features, it also provides move- and copy
 * protection, and will support better move- and copy semantics in the future. Currently, this array can't be moved or copied.
 *
 * @tparam T The type of the array
 * @tparam N The number of elements
 */
template <typename T, size_t N>
class Array
{
    static_assert(N > 0, "Size N has to be bigger than 0");

public:
    /**
     * Definition of modifiable iterator
     */
    using array_iterator = CollectionIterator<T, Array<T, N>>;

    /**
     * Definition of unmodifiable iterator
     */
    using const_array_iterator = CollectionIterator<T, const Array<T, N>>;

    Array() = default;
    ~Array() = default;
    Array(const Array &) = delete;
    Array(Array &&) = delete;
    Array & operator=(const Array &) = delete;
    Array & operator=(Array &&) = delete;

    /**
     * Accesses an element in the array. The index is not checked to be within bounds. This operator can
     * be used to either read or write to an element.
     *
     * @param index Index to access
     * @return Data in element.
     */
    [[nodiscard]] T & operator[](size_t index)
    {
        return at(index);
    }

    /**
     * Accesses an element in the array. The index is not checked to be within bounds. This operator can
     * be used to either read or write to an element.
     *
     * @param index Index to access
     * @return Data in element.
     */
    [[nodiscard]] const T & operator[](size_t index) const
    {
        return at(index);
    }

    /**
     * Gets a pointer pointing to the first element of the array.
     *
     * @return A pointer pointing to the first element
     */
    [[nodiscard]] T * data()
    {
        return m_data;
    }

    /**
     * Gets a pointer pointing to the first element of the array.
     *
     * @return A pointer pointing to the first element
     */
    [[nodiscard]] const T * data() const
    {
        return m_data;
    }

    /**
     * Accesses an element in the array. The index is not checked to be within bounds. This function can
     * be used to either read or write to an element.
     *
     * @param index Index to access
     * @return Data in element.
     */
    [[nodiscard]] T & at(size_t index)
    {
        return m_data[index];
    }

    /**
     * Accesses an element in the array. The index is not checked to be within bounds. This function can
     * be used to either read or write to an element.
     *
     * @param index Index to access
     * @return Data in element.
     */
    [[nodiscard]] const T & at(size_t index) const
    {
        return m_data[index];
    }

    /**
     * Gets the size of the array.
     *
     * @return The array size
     */
    [[nodiscard]] inline size_t size() const noexcept
    {
        return N;
    }

    /**
     * Returns an iterator to the begin of the array
     *
     * @return The iterator
     */
    array_iterator begin()
    {
        return array_iterator(*this, 0);
    }

    /**
     * Returns an iterator to the end of the array
     *
     * @return The iterator
     */
    array_iterator end()
    {
        return array_iterator(*this, N);
    }

    /**
     * Returns an iterator to the begin of the array
     *
     * @return The iterator
     */
    const_array_iterator begin() const
    {
        return const_array_iterator(*this, 0);
    }

    /**
     * Returns an iterator to the end of the array
     *
     * @return The iterator
     */
    const_array_iterator end() const
    {
        return const_array_iterator(*this, N);
    }

private:
    T m_data[N];
};

} // namespace Data

#endif // __ARRAY_H__
