// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>


/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

/**
 * Class for Matrix and the vectors for running the program.
 */
class Matrix
{

    MatrixDims _matrixDim{};
public:


    //Constructors
    /**
     * C'tor of 1 X 1 Matrix. inits all elems to 0.
     */
    Matrix();
    /**
     * C'tor of Matrix rowXcols and init all elems in the array to 0.
     * @param rows - How many rows the matrix holds.
     * @param cols - How many cols the matrix holds.
     */

    Matrix(int rows, int cols);

    /**
     * C'tor of matrix from another Matrix m
     * @param m - The another matrix.
     */
    Matrix(Matrix const &m);

    /**
     * D'tor of the obj Matrix.
     */
    ~Matrix();

    //Method
    /**
     * @return - amount of rows as int in the matrix.
     */
    int getRows() const; //Ignore nodiscard

    /**
 * @return - amount of cols as int in the matrix.
 */
    int getCols() const;

    /**
     * Transforms a matrix into a coloumn vector Supports function calling concatenation
     * @return - matrix after transformation.
     */
    Matrix &vectorize();

    /**
     * Prints matrix elements, no return value. prints space after each element (incl. last
     * element in the row) prints newline after each row (incl. last row)
     */
    void plainPrint() const;

    //Operators
    /**
     * change the matrix as the arg matrix.
     * @return - the a matrix as b.
     */
    Matrix& operator=(const Matrix &m);

    /**
     * Matrix multiplication
     * @return - matrix after the multiplication.
     */
    Matrix operator*(const Matrix &m) const;

    /**
     * Multiplication with a vector from the right.
     * @param c - The vector - M (1 x n) matrix
     * @return - a vector after the multiplication.
     */
    Matrix operator*(float c) const;

    /**
     * Multiplication with a vector from the left.
     * @param c - The vector - M (1 x n) matrix
     * @param m - The matrix for multiplication .
     * @return - a vector after the multiplication.
     */
    friend Matrix operator*(float c, const Matrix &m);

    /**
     * adding two matrix.
     * @param rightEle - whats from the right in the adding.
     * @return - the result matrix.
     */
    Matrix operator+(const Matrix &rightEle) const;

    /**
     * Matrix addition accumulation
     * @return - the result matrix.
     */
    Matrix operator+=(const Matrix &rightElem);

    /**
     * For i,j indices, Matrix m, m(i,j) will return the i,j element in the matrix
     * without an option to change the val inside.
     * @param i, j indexes.
     * @return - The value in th index.
     */
    const float& operator()(int i, int j) const;

    /**
     * For i,j indices, Matrix m, m(i,j) will return the i,j element in the matrix
     * with an option to change the val inside.
     * @param i, j indexes.
     * @return - The value in th index.
     */
    float& operator()(int i, int j);

    /**
     * For i index, Matrix m. with an option to change the val inside.
     * @param i- index
     * @return- the i’th element
     */
    float& operator[](int i);

    /**
     * For i index, Matrix m. without an option to change the val inside.
     * @param i- index
     * @return- the i’th element
     */
    float& operator[](int i) const;

    /**
     * Fills matrix elements has to read input stream fully, otherwise, that’s an error
     * @param is - the istream option.
     * @param m - matrix to insert the elems.
     * return - the istream.
     */
    friend std::istream& operator>>(std::istream &is, Matrix& m);

    /**
     * Print * as explained in the exe. Print the number its calculate from.
     * @param os - the streaming type.
     * @param m - The matrix the include the info.
     * @return - The stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Matrix& m);


private:
    /**
     * The array of all elems that the matrix holds.
     */
    float *_matrixArray = nullptr;

    /**
     * Check if the index is valid- as it should be bigger equal to 0 and lower than the len of
     * the matrix Array.
     * @param num - index.
     * @param boundary - rows * cols of the Matrix,
     * @return - 0 if its fails, otherwise 1.
     */
    int _ifLegalIndex(int num, int boundary) const;
};

#endif //MATRIX_H
