#include <cstddef>
#include <gtest/gtest.h>
#include "array_ops.h"

TEST(ArrayCreateTest, CreateAndFillArray) {
    std::size_t size = 5;
    int *arr = array_create(size);
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], i);
    }
    array_delete(arr);
}

TEST(ArrayDeleteTest, NullsPointerAfterDelete) {
    int *arr = array_create(3);
    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayResizeTest, GrowKeepsOldValues) {
    std::size_t size = 3;
    int *arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr = array_resize(arr, size, 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayResizeTest, ShrinkKeepsPrefix) {
    std::size_t size = 5;
    int *arr = array_create(size);
    int values[] = {0, 1, 2, 3, 4};
    for (std::size_t i = 0; i < size; ++i) arr[i] = values[i];
    arr = array_resize(arr, size, 2);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    array_delete(arr);
}

TEST(ArrayInsertTest, InsertInMiddle) {
    std::size_t size = 3;
    int *arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr = array_insert(arr, size, 1, 99);
    ASSERT_EQ(size, 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 3);
    array_delete(arr);
}

TEST(ArrayInsertTest, InsertAtEndIsAllowed) {
    std::size_t size = 2;
    int *arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr = array_insert(arr, size, 2, 3);
    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayInsertTest, InsertIntoEmptyArray) {
    std::size_t size = 0;
    int *arr = nullptr;
    arr = array_insert(arr, size, 0, 42);
    ASSERT_EQ(size, 1u);
    EXPECT_EQ(arr[0], 42);
    array_delete(arr);
}

TEST(ArrayInsertTest, RejectsOutOfRangePosition) {
    std::size_t size = 2;
    int *arr = array_create(size);
    int *result = array_insert(arr, size, 5, 1);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(size, 2u);
    array_delete(arr);
}

TEST(ArrayRemoveTest, RemoveFromMiddle) {
    std::size_t size = 4;
    int *arr = array_create(size);
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    arr = array_remove(arr, size, 1);
    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayRemoveTest, RejectsOutOfRangePosition) {
    std::size_t size = 2;
    int *arr = array_create(size);
    int *result = array_remove(arr, size, 5);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(size, 2u);
    array_delete(arr);
}

TEST(ArrayRemoveTest, RemoveFromEmptyArrayIsSafe) {
    std::size_t size = 0;
    int *arr = nullptr;
    int *result = array_remove(arr, size, 0);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(size, 0u);
}

TEST(ArrayBinarySearchTest, FindsExistingValue) {
    int arr[] = {1, 3, 5, 7, 9};
    std::size_t out_index = 0;
    bool found = array_binary_search(arr, 5, 9, out_index);
    EXPECT_TRUE(found);
    EXPECT_EQ(out_index, 4u);
}

TEST(ArrayBinarySearchTest, FindsFirstElement) {
    int arr[] = {2, 4, 6, 8};
    std::size_t out_index = 0;
    bool found = array_binary_search(arr, 4, 2, out_index);
    EXPECT_TRUE(found);
    EXPECT_EQ(out_index, 0u);
}

TEST(ArrayBinarySearchTest, ReturnsFalseWhenMissing) {
    int arr[] = {1, 3, 5, 7, 9};
    std::size_t out_index = 0;
    bool found = array_binary_search(arr, 5, 4, out_index);
    EXPECT_FALSE(found);
}

TEST(ArrayBinarySearchTest, EmptyArrayIsSafe) {
    std::size_t out_index = 0;
    bool found = array_binary_search(nullptr, 0, 1, out_index);
    EXPECT_FALSE(found);
}

TEST(ArrayMergeSortTest, SortsUnorderedArray) {
    std::size_t size = 5;
    int *arr = array_create(size);
    int values[] = {5, 3, 1, 4, 2};
    for (std::size_t i = 0; i < size; ++i) arr[i] = values[i];
    array_merge_sort(arr, size);
    int expected[] = {1, 2, 3, 4, 5};
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
    array_delete(arr);
}

TEST(ArrayMergeSortTest, SingleElementAndEmptyAreNoOps) {
    std::size_t size = 1;
    int *arr = array_create(size);
    arr[0] = 42;
    array_merge_sort(arr, size);
    EXPECT_EQ(arr[0], 42);
    array_delete(arr);

    array_merge_sort(nullptr, 0);
}

TEST(ArrayMedianTest, OddSizeArray) {
    std::size_t size = 5;
    int *arr = array_create(size);
    int values[] = {5, 3, 1, 4, 2};
    for (std::size_t i = 0; i < size; ++i) arr[i] = values[i];
    EXPECT_EQ(array_median(arr, size), 3);
    array_delete(arr);
}

TEST(ArrayMedianTest, EvenSizeArrayTakesLeftOfTwoMiddle) {
    std::size_t size = 4;
    int *arr = array_create(size);
    int values[] = {4, 1, 3, 2};
    for (std::size_t i = 0; i < size; ++i) arr[i] = values[i];
    EXPECT_EQ(array_median(arr, size), 3);
    array_delete(arr);
}

TEST(ArrayMedianTest, EmptyArrayIsSafe) {
    EXPECT_EQ(array_median(nullptr, 0), 0);
}
