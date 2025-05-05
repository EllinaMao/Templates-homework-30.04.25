// Templates homework 30.04.25.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MatrixData.h"
#include "MatrixIo.h"
#include "IMatrixAnalisis.h"

using namespace std;
/*
+Создайте шаблонный класс матрица.
+необходимо реализовать динамическое выделение памяти, очистку памяти,
+заполнение матрицы с клавиатуры,
+заполнение случайными значениями,
+отображение матрицы,
арифметические операции с помощью перегруженных операторов(+, -, *, / ), 
+поиск максимального и минимального элемента.*/
int main()
{
    // Working with an int matrix
    cout << "Working with an int matrix:" << endl;
    int rows = 10;
    int columns = 10;

    int min = 30;
    int max = 110;
    Matrix<int> intMat(rows, columns, min, max); 

    int intMinValue = MatrixAnalysis<int>::Min(intMat);
    int intMaxValue = MatrixAnalysis<int>::Max(intMat);

	MatrixIO<int>::Output(intMat);
    cout << "Minimum value: " << intMinValue << ", Maximum value: " << intMaxValue << endl;

    // Working with a char matrix
    cout << "\nWorking with a char matrix:" << endl;
    Matrix<char> charMat(rows, columns);
    cout << "Enter the elements of the char matrix:" << endl;
    MatrixIO<char>::Input(charMat);
    cout << "Char matrix:" << endl;
    MatrixIO<char>::Output(charMat);
    ////

//
//    Matrix<int> mat1(3, 3, 1, 10);
//Matrix<int> mat2(3, 3, 1, 10);
//
//Matrix<int> sum = mat1 + mat2; // Сложение
//Matrix<int> diff = mat1 - mat2; // Вычитание
//Matrix<int> product = mat1 * mat2; // Умножение
//Matrix<int> scaled = mat1 / 2; // Деление на скаляр

    return 0;
}

