#pragma once

#include <cstddef>

class DataStructure {
public:
    DataStructure() = default;
    virtual ~DataStructure();
    virtual size_t GetSizeInBytes() = 0;
    [[nodiscard]] size_t GetSize() const;

protected:
    size_t size = 0;
};
