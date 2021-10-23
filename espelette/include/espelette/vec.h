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
    const size_t elementSize {};
    size_t elementCount {};
    size_t capacity {};
    char* memory {};
public:
    explicit RawVec(size_t elementSize) noexcept;
    ~RawVec() noexcept;

    RawVec(const RawVec&) noexcept;
    RawVec(RawVec&&) noexcept;

    RawVec& operator=(const RawVec&) noexcept;
    RawVec& operator=(RawVec&&) noexcept;

    void* get(size_t index);
    [[nodiscard]] const void* get(size_t index) const;
    void* getBack();

    void* data();
    [[nodiscard]] const void* data() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t byte_size() const;

    void reserve(size_t newSize);
    void resize(size_t newSize);
    void clear();


    void* allocBack(size_t n = 1);

private:
    void grow();
};

// Wrapper around raw vec. Only for POD types. use std::vector otherwise
template<class T>
class Vec : public RawVec
{
public:
    Vec() noexcept: RawVec(sizeof(T)){}
    Vec(Vec&&) noexcept = default;
    Vec(const Vec&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    Vec& operator=(const Vec&) noexcept = default;

    T* begin() { return static_cast<T*>(get(0)); }
    T* end() { return static_cast<T*>(get(size())); }

    void push_back(const T& t) { *static_cast<T*>(allocBack()) = t; }
    T* alloc_back(size_t n) { return static_cast<T*>(RawVec::allocBack(n)); };

    T& operator[](size_t index){ return *static_cast<T*>(get(index)); };

    T& back(){ return *static_cast<T*>(getBack()); }
};
#endif //ESPELETTE_VEC_H
