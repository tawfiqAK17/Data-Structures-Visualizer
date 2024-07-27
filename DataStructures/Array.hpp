#pragma once

#include <cstddef>
#include "DataStructure.hpp"

class Array : public DataStructure {
public:
    Array() = default;
    ~Array() override;
    void Add(int val);
    void Remove(int val);
    void RemoveAt(int idx);
    void Find(int val);
    void Clear();

    size_t GetSizeInBytes() override;

    int operator[](int idx) const;
private:
    bool Grow();
    bool Shrink();
private:
    int *data = nullptr;
};