#include <cstdlib>
#include <iostream>
#include "Array.hpp"

Array::~Array() {
    Clear();
}

bool Array::Add(int val) {
    Grow();
    data[size++] = val;
    return true;
}

bool Array::AddRandom(int number) {
    for (int i = 0; i < number; i++) {
        Add(rand() % 20);
    }
    return true;
}

bool Array::Remove(int val) {
    for (int i = 0; i < size; i++) {
        if (data[i] == val) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            if (Shrink())
                size--;
            else
                size = 0;
            return true;
        }
    }
    return false;
}

bool Array::RemoveAt(int idx) {
    if (idx >= size || idx < 0)
        return false;
    for (int i = 0; i < size; i++) {
        if (i == idx) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            if (Shrink())
                size--;
            else
                size = 0;
            return true;
        }
    }
    return true;
}

bool Array::Find(int val) {
    for (int i = 0; i < size; i++)
        if (data[i] == val)
            return true;
    return false;
}

bool Array::BubbleSort() {
    if (size == 0)
        return true;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (data[j] < data[i])
                Swap(data[i], data[j]);
        }
    }
    return true;
}

bool Array::SelectionSort() {
    if (size == 0)
        return true;
    for (size_t i = 0; i < size - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < size; j++) {
            if (data[j] < data[i])
                minIdx = j;
        }
        Swap(data[i], data[minIdx]);
    }
    return true;
}

bool Array::MergeSort() {
    if (!data)
        return true;
    MergeSortRecursive(data, size);
    return true;
}

void Array::MergeSortRecursive(int *arr, int size) {
    if (size <= 1)
        return;
    int *left = new int[size / 2];
    int *right = new int[size - size / 2];

    for (int i = 0; i < size / 2; i++) {
        left[i] = arr[i];
    }
    for (int i = size / 2; i < size; i++) {
        right[i - size / 2] = arr[i];
    }
    MergeSortRecursive(left, size / 2);
    MergeSortRecursive(right, size - size / 2);
    Merge(arr, left, size / 2, right, size - size / 2);
    delete[] left;
    delete[] right;
}

void Array::Merge(int* arr, int *left, int leftSize, int *right, int rightSize) {
    int rIdx = 0, lIdx = 0, arrIdx = 0;
    while (lIdx < leftSize && rIdx < rightSize) {
        if (left[lIdx] <= right[rIdx]) {
            arr[arrIdx++] = left[lIdx++];
        } else {
            arr[arrIdx++] = right[rIdx++];
        }
    }
    while (lIdx < leftSize) {
        arr[arrIdx++] = left[lIdx++];
    }
    while (rIdx < rightSize) {
        arr[arrIdx++] = right[rIdx++];
    }

}

bool Array::Clear() {
    delete[] data;
    data = nullptr;
    size = 0;
    return true;
}

bool Array::Grow() {
    if (size == 0) {
        data = new int;
        return true;
    }
    int *temp = data;
    data = new int[size + 1];
    for (int i = 0; i < size; i++) {
        data[i] = temp[i];
    }
    delete[] temp;
    return true;
}

bool Array::Shrink() {
    if (size == 0)
        return false;
    if (size == 1) {
        data = nullptr;
        return false;
    }
    int *temp = data;
    data = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        data[i] = temp[i];
    }
    delete[] temp;
    return true;
}

size_t Array::GetSizeInBytes() {
    return size * sizeof(int);
}

int Array::operator[](int idx) const {
    if (data)
        return data[idx];
    return -1;
}

void Array::Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
