#pragma once
#include <cstddef>

// Базовые операции семейства A
int* array_create(std::size_t size);                                         // new int[size], +1 слот под '\0' не нужен
void array_delete(int*& arr);                                                // delete[] и обнулить указатель
int* array_resize(int* arr, std::size_t size, std::size_t new_size);         // новая память + копия
int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value);  // вставка
int* array_remove(int* arr, std::size_t& size, std::size_t pos);             // удаление
void array_print(const int* arr, std::size_t size);
bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index);

// Вариант 6: сортировка слиянием (рекурсия) + медиана
void array_merge_sort(int* arr, std::size_t size);         // сигнатура на твоё усмотрение
int array_median(const int* arr, std::size_t size);        // элемент size/2 отсортированного массива
