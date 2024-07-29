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

    bool BubbleSort();
    bool SelectionSort();
    bool MergeSort();
    bool Clear();

    size_t GetSizeInBytes() override;

    int operator[](int idx) const;
private:
    void Swap(int& a, int& b);
    void MergeSortRecursive(int* arr, int size);
    void Merge(int* arr, int* left, int leftSize, int* right, int rightSize);
private:
    bool Grow();
    bool Shrink();
private:
    int *data = nullptr;
};