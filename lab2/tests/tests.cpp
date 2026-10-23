#include <sstream>
#include <utility>
#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(MatrixCreateTest, DefaultMatrixIsEmpty) {
    Matrix m;

    EXPECT_EQ(m.rows(), 0u);
    EXPECT_EQ(m.cols(), 0u);
}

TEST(MatrixCreateTest, ConstructorFillsValue) {
    Matrix m(2, 3, 1.5);

    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.cols(), 3u);
    EXPECT_DOUBLE_EQ(m.get(0, 0), 1.5);
    EXPECT_DOUBLE_EQ(m.get(1, 2), 1.5);
}

TEST(MatrixSetTest, SetThenGet) {
    Matrix m(2, 2, 0.0);

    EXPECT_TRUE(m.set(0, 1, 7.0));
    EXPECT_DOUBLE_EQ(m.get(0, 1), 7.0);
    EXPECT_DOUBLE_EQ(m.get(1, 0), 0.0);
}

TEST(MatrixSetTest_Fail, OutOfRangeIndex) {
    Matrix m(2, 2, 1.0);

    EXPECT_FALSE(m.set(2, 0, 5.0));
    EXPECT_FALSE(m.set(0, 2, 5.0));
    EXPECT_DOUBLE_EQ(m.get(2, 0), 0.0);
}

TEST(MatrixCopyTest, CopyConstructorMakesDeepCopy) {
    Matrix a(2, 2, 1.0);
    Matrix b(a);
    b.set(0, 0, 9.0);

    EXPECT_DOUBLE_EQ(a.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 9.0);
}

TEST(MatrixCopyTest, CopyAssignmentMakesDeepCopy) {
    Matrix a(2, 2, 1.0);
    Matrix b(3, 1, 5.0);
    b = a;
    a.set(1, 1, 4.0);

    EXPECT_EQ(b.rows(), 2u);
    EXPECT_EQ(b.cols(), 2u);
    EXPECT_DOUBLE_EQ(b.get(1, 1), 1.0);
}

TEST(MatrixCopyTest, SelfAssignment) {
    Matrix a(2, 2, 3.0);
    Matrix &ref = a;
    a = ref;

    EXPECT_EQ(a.rows(), 2u);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 3.0);
}

TEST(MatrixMoveTest, MoveConstructorEmptiesSource) {
    Matrix a(2, 2, 3.0);
    Matrix b(std::move(a));

    EXPECT_EQ(b.rows(), 2u);
    EXPECT_DOUBLE_EQ(b.get(1, 1), 3.0);
    EXPECT_EQ(a.rows(), 0u);
    EXPECT_EQ(a.cols(), 0u);
}

TEST(MatrixMoveTest, MoveAssignmentEmptiesSource) {
    Matrix a(2, 2, 2.0);
    Matrix b(1, 1, 5.0);
    b = std::move(a);

    EXPECT_EQ(b.rows(), 2u);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 2.0);
    EXPECT_EQ(a.rows(), 0u);
}

TEST(MatrixAddTest, AddSameSize) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    EXPECT_TRUE(a.add(b));
    EXPECT_DOUBLE_EQ(a.get(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 3.0);
}

TEST(MatrixAddTest_Fail, DifferentSize) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 3, 1.0);

    EXPECT_FALSE(a.add(b));
    EXPECT_DOUBLE_EQ(a.get(0, 0), 1.0);
}

TEST(MatrixMulTest, MulSquare) {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    EXPECT_TRUE(a.mul(b));
    EXPECT_DOUBLE_EQ(a.get(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 4.0);
}

TEST(MatrixMulTest, MulChangesSize) {
    Matrix a(2, 3, 1.0);
    Matrix b(3, 1, 2.0);

    EXPECT_TRUE(a.mul(b));
    EXPECT_EQ(a.rows(), 2u);
    EXPECT_EQ(a.cols(), 1u);
    EXPECT_DOUBLE_EQ(a.get(1, 0), 6.0);
}

TEST(MatrixMulTest_Fail, WrongSize) {
    Matrix a(2, 3, 1.0);
    Matrix b(2, 3, 1.0);

    EXPECT_FALSE(a.mul(b));
    EXPECT_EQ(a.rows(), 2u);
    EXPECT_EQ(a.cols(), 3u);
}

TEST(MatrixPrintTest, PrintsRows) {
    Matrix m(2, 2, 0.0);
    m.set(0, 0, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);
    std::ostringstream out;

    m.print(out);
    EXPECT_EQ(out.str(), "1 2 \n3 4 \n");
}

TEST(MatrixSumTest, SumOfAllElements) {
    Matrix m(2, 2, 0.0);
    m.set(0, 0, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);

    EXPECT_DOUBLE_EQ(m.sum(), 10.0);
}

TEST(MatrixSumTest, SingleElement) {
    Matrix m(1, 1, -2.5);

    EXPECT_DOUBLE_EQ(m.sum(), -2.5);
}

TEST(MatrixSumTest, EmptyMatrixIsZero) {
    Matrix m;
    Matrix n(0, 3, 1.0);

    EXPECT_DOUBLE_EQ(m.sum(), 0.0);
    EXPECT_DOUBLE_EQ(n.sum(), 0.0);
}

TEST(MatrixSumTest, MovedFromMatrixIsZero) {
    Matrix a(2, 2, 1.0);
    Matrix b(std::move(a));

    EXPECT_DOUBLE_EQ(b.sum(), 4.0);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}
