#pragma once

#include <cstddef>
#include "DataStructure.hpp"

class Array : public DataStructure {
public:
    Array() = default;
    ~Array() override;
    void Add(int val);
    void remove(int val);
    void Clear();

    int operator[](int idx) const;
private:
    bool Grow();
    bool Shrink();
private:
    int *data = nullptr;
};