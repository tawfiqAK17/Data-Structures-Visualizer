#pragma once

#include <cstddef>
#include "DataStructure.hpp"

class Array : public DataStructure {
public:
    Array() = default;
    ~Array() override;
    bool Add(int val);
    bool AddRandom(int number);
    bool Remove(int val);
    bool RemoveAt(int idx);
    bool Find(int val);
    bool Clear();

    size_t GetSizeInBytes() override;

    int operator[](int idx) const;
private:
    bool Grow();
    bool Shrink();
private:
    int *data = nullptr;
};