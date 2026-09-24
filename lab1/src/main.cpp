#include <iostream>
#include <limits>
#include "array_ops.hpp"

static void print_menu() {
    std::cout
            << "\n--- Лабораторная 1, вариант 6 ---\n"
            << "1. Создать массив\n"
            << "2. Показать элемент по индексу\n"
            << "3. Вставить элемент\n"
            << "4. Удалить элемент\n"
            << "5. Изменить размер\n"
            << "6. Вывести массив\n"
            << "7. Отсортировать и найти медиану\n"
            << "0. Выход\n"
            << "Команда: ";
}

static bool read_int(int &value) {
    std::cin >> value;
    if (std::cin.eof()) {
        return false;
    }
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно ввести целое число\n";
        return false;
    }
    return true;
}

static bool read_size(std::size_t &value) {
    long long raw = 0;
    std::cin >> raw;
    if (std::cin.eof()) {
        return false;
    }
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно ввести целое число\n";
        return false;
    }
    if (raw < 0) {
        std::cout << "Число не может быть отрицательным\n";
        return false;
    }
    value = static_cast<std::size_t>(raw);
    return true;
}

static void array_fill_zero(int *arr, std::size_t from, std::size_t to) {
    for (std::size_t i = from; i < to; ++i) {
        arr[i] = 0;
    }
}

int main() {
    int *array = nullptr;
    std::size_t size = 0;
    bool ok = true;

    while (ok) {
        print_menu();
        int command = 0;
        if (!read_int(command)) {
            if (!std::cin) {
                ok = false;
            }
            continue;
        }

        switch (command) {
            case 1: {
                std::cout << "Введите размер массива: ";
                std::size_t new_size = 0;
                if (!read_size(new_size)) {
                    break;
                }
                int *new_array = array_create(new_size);
                array_fill_zero(new_array, 0, new_size);
                array_delete(array);
                array = new_array;
                size = new_size;
                std::cout << "Создан массив из " << size << " нулей\n";
                break;
            }
            case 2: {
                std::cout << "Введите индекс элемента: ";
                std::size_t pos = 0;
                if (!read_size(pos)) {
                    break;
                }
                if (array == nullptr || pos >= size) {
                    std::cout << "Некорректный индекс\n";
                    break;
                }
                std::cout << "arr[" << pos << "] = " << array[pos] << "\n";
                break;
            }
            case 3: {
                std::cout << "Введите индекс и значение: ";
                std::size_t pos = 0;
                if (!read_size(pos)) {
                    break;
                }
                int value = 0;
                if (!read_int(value)) {
                    break;
                }
                int *new_array = array_insert(array, size, pos, value);
                if (new_array == nullptr) {
                    std::cout << "Некорректный индекс\n";
                    break;
                }
                array = new_array;
                break;
            }
            case 4: {
                std::cout << "Введите индекс элемента для удаления: ";
                std::size_t pos = 0;
                if (!read_size(pos)) {
                    break;
                }
                int *new_array = array_remove(array, size, pos);
                if (new_array == nullptr) {
                    std::cout << "Некорректный индекс\n";
                    break;
                }
                array = new_array;
                break;
            }
            case 5: {
                std::cout << "Введите новый размер массива: ";
                std::size_t new_size = 0;
                if (!read_size(new_size)) {
                    break;
                }
                int *new_array = array_resize(array, size, new_size);
                if (new_array == nullptr) {
                    std::cout << "Не удалось изменить размер\n";
                    break;
                }
                array_fill_zero(new_array, size, new_size);
                array = new_array;
                size = new_size;
                break;
            }
            case 6: {
                if (array == nullptr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }
                array_print(array, size);
                break;
            }
            case 7: {
                if (array == nullptr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }
                int median = array_median(array, size);
                array_print(array, size);
                std::cout << "Медиана: " << median << "\n";
                break;
            }
            case 0: {
                ok = false;
                break;
            }
            default: {
                std::cout << "Нет такой команды\n";
                break;
            }
        }
    }

    array_delete(array);
    return 0;
}
