#pragma once
#include <iostream>
#include <random>
using namespace std;


template <typename T>
class Matrix {
private:
    size_t mRows;
    size_t mColumns;
    T** mData;

    void AllocateMemory();
    void FreeMemory();
    //..
public:
    Matrix();
    Matrix(size_t rows, size_t columns);
    Matrix(size_t rows, size_t columns, T min, T max);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    T operator()(size_t row, size_t column) const;
    T& operator()(size_t row, size_t column);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    size_t GetRows() const;
    size_t GetColumns() const;
    void SetRows(size_t rows);
    void SetCols(size_t columns);
    void FillWithRandomValues(T min, T max);

    friend Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        if (lhs.GetRows() != rhs.GetRows() || lhs.GetColumns() != rhs.GetColumns()) {
            return Matrix<T>(0, 0); // Возвращаем пустую матрицу с нулевыми размерами
        }

        Matrix<T> result(lhs.GetRows(), lhs.GetColumns());
        for (size_t i = 0; i < lhs.GetRows(); ++i) {
            for (size_t j = 0; j < lhs.GetColumns(); ++j) {
                result(i, j) = lhs(i, j) + rhs(i, j);
            }
        }
        return result;
    }

    friend Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        if (lhs.GetRows() != rhs.GetRows() || lhs.GetColumns() != rhs.GetColumns()) {
            return Matrix<T>(0, 0); // Возвращаем пустую матрицу
        }

        Matrix<T> result(lhs.GetRows(), lhs.GetColumns());
        for (size_t i = 0; i < lhs.GetRows(); ++i) {
            for (size_t j = 0; j < lhs.GetColumns(); ++j) {
                result(i, j) = lhs(i, j) - rhs(i, j);
            }
        }
        return result;
    }



    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        if (lhs.GetColumns() != rhs.GetRows()) {
            return Matrix<T>(0, 0); // Возвращаем пустую матрицу
        }

        Matrix<T> result(lhs.GetRows(), rhs.GetColumns());
        for (size_t i = 0; i < lhs.GetRows(); ++i) {
            for (size_t j = 0; j < rhs.GetColumns(); ++j) {
                result(i, j) = 0;
                for (size_t k = 0; k < lhs.GetColumns(); ++k) {
                    result(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
        return result;
    }

    friend Matrix operator/(const Matrix& lhs, const T& scalar) {
        if (scalar == 0) {
            return Matrix<T>(0, 0); // Возвращаем пустую матрицу
        }

        Matrix<T> result(lhs.GetRows(), lhs.GetColumns());
        for (size_t i = 0; i < lhs.GetRows(); ++i) {
            for (size_t j = 0; j < lhs.GetColumns(); ++j) {
                result(i, j) = lhs(i, j) / scalar;
            }
        }
        return result;
    }
};

template <typename T>
Matrix<T>::Matrix() : mRows(5), mColumns(5) {
    AllocateMemory();
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns)
    : mRows(rows), mColumns(columns) {
    AllocateMemory();
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T min, T max)
    : mRows(rows), mColumns(columns) {
    AllocateMemory();
    FillWithRandomValues(min, max);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : mRows(other.mRows), mColumns(other.mColumns) {
    AllocateMemory();
    for (size_t i = 0; i < mRows; ++i) {
        for (size_t j = 0; j < mColumns; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : mRows(other.mRows), mColumns(other.mColumns), mData(other.mData) {
    other.mRows = 0;
    other.mColumns = 0;
    other.mData = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
    FreeMemory();
}

template <typename T>
T Matrix<T>::operator()(size_t row, size_t column) const {
    if (row >= mRows || column >= mColumns) {
        return T();
    }
    return mData[row][column];
}

template <typename T>
T& Matrix<T>::operator()(size_t row, size_t column) {
    if (row >= mRows || column >= mColumns) {
        return mData[0][0];
    }
    return mData[row][column];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    FreeMemory();

    mRows = other.mRows;
    mColumns = other.mColumns;

    AllocateMemory();

    for (size_t i = 0; i < mRows; ++i) {
        for (size_t j = 0; j < mColumns; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }

    return *this; // Возвращаем ссылку на текущий объект
}


template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    FreeMemory();

    mRows = other.mRows;
    mColumns = other.mColumns;
    mData = other.mData;

    other.mRows = 0; // Исправлено: обнуляем поля у объекта other
    other.mColumns = 0;
    other.mData = nullptr;

    return *this; // Возвращаем ссылку на текущий объект
}



template <typename T>
size_t Matrix<T>::GetRows() const {
    return mRows;
}

template <typename T>
size_t Matrix<T>::GetColumns() const {
    return mColumns;
}

template <typename T>
void Matrix<T>::SetRows(size_t rows) {
    FreeMemory();
    mRows = rows;
    AllocateMemory();
}

template <typename T>
void Matrix<T>::SetCols(size_t columns) {
    FreeMemory();
    mColumns = columns;
    AllocateMemory();
}

template <typename T>
void Matrix<T>::FillWithRandomValues(T min, T max) {
    random_device rd;
    mt19937 gen(rd());

    if constexpr (is_integral<T>::value || is_same<T, char>::value) {
        uniform_int_distribution<int> dist(static_cast<int>(min), static_cast<int>(max));
        for (size_t i = 0; i < mRows; ++i) {
            for (size_t j = 0; j < mColumns; ++j) {
                mData[i][j] = static_cast<T>(dist(gen));
            }
        }
    }
    else if constexpr (is_floating_point<T>::value) {
        uniform_real_distribution<T> dist(min, max);
        for (size_t i = 0; i < mRows; ++i) {
            for (size_t j = 0; j < mColumns; ++j) {
                mData[i][j] = dist(gen);
            }
        }
    }
}

template <typename T>
void Matrix<T>::AllocateMemory() {
    mData = new T * [mRows];
    for (size_t i = 0; i < mRows; ++i) {
        mData[i] = new T[mColumns];
    }
}

template <typename T>
void Matrix<T>::FreeMemory() {
    if (mData) {
        for (size_t i = 0; i < mRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
        mData = nullptr;
    }
}
