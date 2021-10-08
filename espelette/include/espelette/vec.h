//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_VEC_H
#define ESPELETTE_VEC_H

#include <cstddef>

// A small vector for POD types. If your Elements have constructors / destructors use std::vector
class RawVec
{
protected:
    size_t elementSize {};
    size_t elementCount {};
    size_t capacity {};
    char* memory {};
public:
    explicit RawVec(size_t elementSize) : elementSize(elementSize)
    {}

    void* get(size_t index);
    [[nodiscard]] const void* get(size_t index) const;

    void* data();
    [[nodiscard]] const void* data() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t byte_size() const;

    void reserve(size_t newSize);
    void resize(size_t newSize);
    void clear();

    void* allocBack();

private:
    void grow();
};

// Wrapper around raw vec. Only for POD types. use std::vector otherwise
template<class T>
class Vec : public RawVec
{
public:
    Vec() : RawVec(sizeof(T))
    {}
    void push_back(const T& t)
    {
        *static_cast<T*>(allocBack()) = t;
    }
};

#endif //ESPELETTE_VEC_H
