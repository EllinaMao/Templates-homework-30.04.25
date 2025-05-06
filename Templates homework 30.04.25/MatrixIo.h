#pragma once
#include <iostream>
#include "MatrixData.h"

using namespace std;

template <typename T>
class MatrixIO
{
private:
    static void ClearInputBuffer();

public:
    static void Input(Matrix<T>& matrix);
    static void Output(const Matrix<T>& matrix);

    // Исправленный friend-оператор
    friend ostream& operator<<(ostream& os, const Matrix<T>& m) {
        for (size_t i = 0; i < m.GetRows(); i++) {
            for (size_t j = 0; j < m.GetColumns(); j++) { // Fixed GetColums -> GetColumns
                os << m(i, j) << " "; // Using the element access operator
            }
            os << endl;
        }
        return os;
    }
};

template<typename T>
inline void MatrixIO<T>::ClearInputBuffer()
{
    if (cin.fail()) { // Check if input failed
        cin.clear(); // Reset the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
}

template<typename T>
inline void MatrixIO<T>::Input(Matrix<T>& matrix)
{
    size_t rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    matrix.SetRows(rows);
    matrix.SetCols(cols);

    cout << "Enter the elements of the matrix:" << endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            T value;
            cin >> value;
            matrix(i, j) = value; // Using the element access operator
        }
    }
}

template<typename T>
inline void MatrixIO<T>::Output(const Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        for (size_t j = 0; j < matrix.GetColumns(); ++j) { // Fixed GetCols -> GetColumns
            cout << matrix(i, j) << " ";
        }
        cout << endl;
    }
    cout <<"----------------------------------------" << endl;

}

