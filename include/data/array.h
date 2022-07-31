#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <inttypes.h>

template<typename T, size_t N>
class Array
{
    static_assert(N > 0, "Size N has to be bigger than 0");
public:
    Array() = default;
    ~Array() = default;
    Array(const Array &) = delete;
    Array(Array &&) = delete;
    Array & operator=(const Array &) = delete;
    Array & operator=(Array &&) = delete;

    T & operator[](size_t index)
    {
        if(index < 0 || index >= N)
            throw "Out of bounds";

        return data[index];
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return N;
    }
private:
    T data[N];
};

#endif // __ARRAY_H__
