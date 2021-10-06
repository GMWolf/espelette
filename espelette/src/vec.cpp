//
// Created by felix on 06/10/2021.
//


#include "vec.h"
#include <cstdlib>

void *RawVec::get(size_t index)
{
    return memory + elementSize * index;
}

const void *RawVec::get(size_t index) const
{
    return memory + elementSize * index;
}

void *RawVec::data()
{
    return memory;
}

size_t RawVec::size() const
{
    return elementCount;
}

size_t RawVec::byte_size() const
{
    return elementCount * elementSize;
}

const void *RawVec::data() const
{
    return memory;
}

void RawVec::reserve(size_t newSize)
{
    if (newSize > elementCount)
    {
        memory = static_cast<char*>(realloc(memory, newSize * elementSize));
    }
}

void RawVec::grow()
{
    size_t newCapacity = capacity == 0 ? 8 : capacity * 2;
    reserve(newCapacity);
}

void RawVec::resize(size_t newSize)
{
    reserve(newSize);
    elementCount = newSize;
}

void *RawVec::allocBack() {
    if (elementCount == capacity)
    {
        grow();
    }

    elementCount++;
    return get(elementCount - 1);
}

void RawVec::clear() {
    elementCount = 0;
}
