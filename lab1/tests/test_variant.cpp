#include <cstddef>
#include <gtest/gtest.h>
#include "../src/array_ops.h"

TEST(ArrayCreateTest, CreateThenDeleteNullsPointer) {
    int *arr = array_create(3);
    ASSERT_NE(arr, nullptr);
    arr[2] = 7;
    EXPECT_EQ(arr[2], 7);

    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayResizeTest, GrowAndShrinkKeepPrefix) {
    int *arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    arr = array_resize(arr, 3, 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    arr = array_resize(arr, 5, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    array_delete(arr);
}

TEST(ArrayInsertTest, InsertIntoEmptyAtEndAndInMiddle) {
    std::size_t size = 0;
    int *arr = nullptr;

    arr = array_insert(arr, size, 0, 1);
    arr = array_insert(arr, size, 1, 3);
    arr = array_insert(arr, size, 1, 2);

    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayInsertTest_Fail, RejectsOutOfRangePosition) {
    std::size_t size = 2;
    int *arr = array_create(size);

    EXPECT_EQ(array_insert(arr, size, 5, 1), nullptr);
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

TEST(ArrayRemoveTest_Fail, RejectsOutOfRangeAndEmptyArray) {
    std::size_t size = 2;
    int *arr = array_create(size);
    EXPECT_EQ(array_remove(arr, size, 5), nullptr);
    EXPECT_EQ(size, 2u);
    array_delete(arr);

    std::size_t empty_size = 0;
    EXPECT_EQ(array_remove(nullptr, empty_size, 0), nullptr);
    EXPECT_EQ(empty_size, 0u);
}

TEST(ArrayBinarySearchTest, FindsFirstAndLastElements) {
    const int arr[] = {1, 3, 5, 7, 9};
    std::size_t out_index = 0;

    ASSERT_TRUE(array_binary_search(arr, 5, 1, out_index));
    EXPECT_EQ(out_index, 0u);
    ASSERT_TRUE(array_binary_search(arr, 5, 9, out_index));
    EXPECT_EQ(out_index, 4u);
}

TEST(ArrayBinarySearchTest_Fail, MissingValueOrEmptyArrayReturnsFalse) {
    const int arr[] = {1, 3, 5, 7, 9};
    std::size_t out_index = 0;

    EXPECT_FALSE(array_binary_search(arr, 5, 4, out_index));
    EXPECT_FALSE(array_binary_search(arr, 5, 0, out_index));
    EXPECT_FALSE(array_binary_search(nullptr, 0, 1, out_index));
}

TEST(ArrayMergeSortTest, SortsArrayWithDuplicates) {
    int arr[] = {5, 3, 1, 3, 2};

    array_merge_sort(arr, 5);

    const int expected[] = {1, 2, 3, 3, 5};
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ArrayMedianTest, OddSizeReturnsMiddleAndKeepsSource) {
    const int arr[] = {5, 3, 1, 4, 2};

    EXPECT_EQ(array_median(arr, 5), 3);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[4], 2);
}

TEST(ArrayMedianTest, EvenSizeReturnsLeftOfTwoMiddle) {
    const int arr[] = {4, 1, 3, 2};

    EXPECT_EQ(array_median(arr, 4), 2);
}

TEST(ArrayMedianTest_Fail, EmptyArrayReturnsZero) {
    EXPECT_EQ(array_median(nullptr, 0), 0);
}
