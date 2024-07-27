#pragma once

class DataStructure {
public:
    DataStructure() = default;
    virtual ~DataStructure();
    [[nodiscard]] unsigned int GetSize() const;

protected:
    unsigned int size = 0;
};
