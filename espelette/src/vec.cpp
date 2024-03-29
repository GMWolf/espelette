//
// Created by felix on 06/10/2021.
//

#include "vec.h"
#include <cstdlib>
#include <cstring>
#include <cassert>

RawVec::RawVec(size_t elementSize) noexcept : elementSize(elementSize)
{}

RawVec::RawVec(const RawVec & v) noexcept : elementSize(v.elementSize)
{
    resize(v.size());
    memcpy(memory, v.memory, elementSize * v.elementCount);
}


RawVec::RawVec(RawVec && v) noexcept : elementSize(v.elementSize)
{
    memory = v.memory;
    capacity = v.capacity;
    elementCount = v.elementCount;
    v.memory = nullptr;
    v.capacity = 0;
    v.elementCount = 0;
}

RawVec& RawVec::operator=(const RawVec& v) noexcept
{
    assert(v.elementSize == elementSize);
    resize(v.size());
    memcpy(memory, v.memory, elementSize * v.elementCount);
    return *this;
}

RawVec &RawVec::operator=(RawVec && v) noexcept
{
    assert(v.elementSize == elementSize);
    memory = v.memory;
    capacity = v.capacity;
    elementCount = v.elementCount;
    v.memory = nullptr;
    v.elementCount = 0;
    v.capacity = 0;
    return *this;
}


RawVec::~RawVec()
{
    free(memory);
}

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
    if (newSize > capacity)
    {
        memory = static_cast<char*>(realloc(memory, newSize * elementSize));
        capacity = newSize;
    }
}

void RawVec::grow()
{
    size_t newCapacity = capacity < 8 ? 8 : capacity * 2;
    reserve(newCapacity);
}

void RawVec::resize(size_t newSize)
{
    reserve(newSize);
    elementCount = newSize;
}

void *RawVec::allocBack(size_t n) {
    if (elementCount + n > capacity)
    {
        grow();
    }

    void* ret = get(elementCount);
    elementCount += n;
    return ret;
}

void RawVec::clear() {
    elementCount = 0;
}

void *RawVec::getBack() {
    return get(elementCount - 1);
}

