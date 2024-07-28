#include <cstdlib>
#include <ctime>
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
        Add(rand() % 1000);
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
