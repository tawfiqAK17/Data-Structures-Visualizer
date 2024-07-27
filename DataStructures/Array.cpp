#include "Array.hpp"

Array::~Array() {
    Clear();
}

void Array::Add(int val) {
    if (Grow())
        data[size++] = val;
}

void Array::Remove(int val) {
    if (size == 1 && data[0] == val) {
        if (Shrink())
            size--;
        else
            size = 0;
        return;
    }
    for (int i = 0; i < size; i++) {
        if (data[i] == val) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            if (Shrink())
                size--;
            else
                size = 0;
            return;
        }
    }
}

void Array::Clear() {
    delete[] data;
    data = nullptr;
    size = 0;
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
