#include "array_ops.h"
#include <algorithm>
#include <iostream>

int *array_create(std::size_t size) {
    return new int[size];
}

void array_delete(int *&arr) {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
}

int *array_resize(int *arr, std::size_t size, std::size_t new_size) {
    if (arr == nullptr && size != 0) {
        return nullptr;
    }
    int *new_arr = new int[new_size];
    std::size_t copy_count = std::min(size, new_size);
    for (std::size_t i = 0; i < copy_count; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    return new_arr;
}

int *array_insert(int *arr, std::size_t &size, std::size_t pos, int value) {
    if (pos > size) {
        return nullptr;
    }
    int *new_arr = array_resize(arr, size, size + 1);
    for (std::size_t i = size; i > pos; --i) {
        new_arr[i] = new_arr[i - 1];
    }
    new_arr[pos] = value;

    size += 1;
    return new_arr;
}

int *array_remove(int *arr, std::size_t &size, std::size_t pos) {
    if (arr == nullptr || size == 0) {
        return nullptr;
    }
    if (pos >= size) {
        return nullptr;
    }
    for (std::size_t i = pos; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    int *new_arr = array_resize(arr, size, size - 1);
    size -= 1;
    return new_arr;
}

void array_print(const int *arr, std::size_t size) {
    if (arr == nullptr || size == 0) {
        return;
    }
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

bool array_binary_search(const int *arr, std::size_t size, int target, std::size_t &out_index) {
    if (arr == nullptr || size == 0) {
        return false;
    }
    std::size_t low = 0;
    std::size_t high = size - 1;
    while (low <= high) {
        std::size_t mid = low + (high - low) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        } else if (arr[mid] > target) {
            if (mid == 0) return false;
            high = mid - 1;
        } else {
            out_index = mid;
            return true;
        }
    }
    return false;
}

void array_merge_sort(int *arr, std::size_t size) {
    if (arr == nullptr || size <= 1) {
        return;
    }

    std::size_t mid = size / 2;
    array_merge_sort(arr, mid);
    array_merge_sort(arr + mid, size - mid);

    int *temp = new int[size];
    std::size_t i = 0;
    std::size_t j = mid;
    std::size_t k = 0;

    while (i < mid && j < size) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            ++i;
        } else {
            temp[k] = arr[j];
            ++j;
        }
        ++k;
    }
    while (i < mid) {
        temp[k] = arr[i];
        ++i;
        ++k;
    }
    while (j < size) {
        temp[k] = arr[j];
        ++j;
        ++k;
    }

    for (std::size_t m = 0; m < size; ++m) {
        arr[m] = temp[m];
    }
    delete[] temp;
}

int array_median(int *arr, std::size_t size) {
    if (arr == nullptr || size == 0) {
        return 0;
    }
    array_merge_sort(arr, size);
    return arr[size / 2];
}
