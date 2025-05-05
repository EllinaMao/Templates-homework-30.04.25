#pragma once
#include <iostream>
#include "MatrixData.h"

template <typename T>
class MatrixAnalysis {
public:
    static T Min(const Matrix<T>& matrix);
    static T Max(const Matrix<T>& matrix);
};

template <typename T>
T MatrixAnalysis<T>::Min(const Matrix<T>& matrix) {
    T minValue = matrix(0, 0); // Предполагаем, что Matrix имеет оператор () для доступа к элементам
    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        for (size_t j = 0; j < matrix.GetColumns(); ++j) {
            if (matrix(i, j) < minValue) {
                minValue = matrix(i, j);
            }
        }
    }
    return minValue;
}

template <typename T>
T MatrixAnalysis<T>::Max(const Matrix<T>& matrix) {
    T maxValue = matrix(0, 0);
    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        for (size_t j = 0; j < matrix.GetColumns(); ++j) {
            if (matrix(i, j) > maxValue) {
                maxValue = matrix(i, j);
            }
        }
    }
    return maxValue;
}
