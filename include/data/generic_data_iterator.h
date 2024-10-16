//
// Created by Tim on 26/10/2022.
//

#ifndef DOMOTICSBASE_GENERIC_DATA_ITERATOR_H
#define DOMOTICSBASE_GENERIC_DATA_ITERATOR_H

namespace Data

{
/**
 * Template class for a data operator. The iterator assumes the collection has the
 * [] operator overloaded to read data from the collection.
 */
template <typename T, typename Collection>
class CollectionIterator
{
public:
    CollectionIterator(Collection & collection, const size_t index) :
        m_collection(collection), m_index(index)
    {
    }

    bool operator!=(const CollectionIterator & other) const
    {
        return m_index != other.m_index;
    }

    const T & operator*() const
    {
        return m_collection[m_index];
    }

    const CollectionIterator & operator++()
    {
        ++m_index;
        return *this;
    }

private:
    size_t m_index;
    Collection & m_collection;
};

} // namespace Data

#endif // DOMOTICSBASE_GENERIC_DATA_ITERATOR_H
