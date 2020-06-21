//
// Created by matans on 23/12/2019.
//

#include "Matrix.h"

#define ERR_MSG "Wrong input ! "
#define DEFAULT_NUM 1
#define NEW_LINE '\n'
#define DOUBLE_SPACE "  "
#define DOUBLE_ASTERISK "**"
#define SPACE " "
#define SUCCESS 1
#define FAILURE 0



/**
 * Constructs Matrix rows X cols initis all elements to 0.
 * @param rows - Number of rows from user.
 * @param cols - Number of cols from user.
 */
Matrix::Matrix(const int rows, const int cols) :
        _matrixDim{rows, cols}
{
    if (rows > 0 && cols > 0)
    {
        _matrixArray = new float[rows * cols]();
    }
    else
    {
        std::cerr << ERR_MSG << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Construct 1X1 Matrix inits the single elements to 0.
 * @return - New obj Matrix initialize as explained.
 */
Matrix::Matrix() :
        Matrix(DEFAULT_NUM, DEFAULT_NUM)
{
}

Matrix &Matrix::operator=(const Matrix &m)
{
    if (this != &m)
    {
        delete[] _matrixArray;
        _matrixDim.rows = m._matrixDim.rows;
        _matrixDim.cols = m._matrixDim.cols;
        _matrixArray = new float[_matrixDim.rows * _matrixDim.cols];
        for (int i = 0; i < _matrixDim.rows * _matrixDim.cols; i++)
        {
            _matrixArray[i] = m._matrixArray[i];
        }
    }
    return *this;
}

/**
 * Constructs matrix from another Matrix m.
 */
Matrix::Matrix(const Matrix &m)
{
    _matrixDim.rows = m._matrixDim.rows;
    _matrixDim.cols = m._matrixDim.cols;
    _matrixArray = new float[m.getRows() * m.getCols()];
    for (int i = 0; i < _matrixDim.rows * _matrixDim.cols; i++)
    {
        _matrixArray[i] = m._matrixArray[i];
    }
}



/**
 * Destructor.
 */
Matrix::~Matrix()
{
    delete[] _matrixArray;
}

int Matrix::getRows() const
{
    return _matrixDim.rows;
}

int Matrix::getCols() const
{
    return _matrixDim.cols;
}

/**
 * Transforms a matrix into a coloumn vector Supports function calling concatenation
 * @param m - The matrix to transform
 * @return - New matrix -> vector.
 */
Matrix& Matrix::vectorize()
{
    _matrixDim.rows = getCols() * getRows();
    _matrixDim.cols = 1;
    return *this;
}

/**
 * Prints matrix elements. Space after each elements, and new line
 * every new row.
 */
void Matrix::plainPrint() const
{
    for (int i = 0; i < _matrixDim.rows; i++)
    {
        for (int j = 0; j < _matrixDim.cols; j++)
        {
            std::cout << (*this)(i, j) << SPACE;
        }
        std::cout << NEW_LINE;
    }
}

/**
 * Matrix multiplication.
 * @param rightEle
 * @return
 */
Matrix Matrix::operator+(Matrix const &rightEle) const
{
    if (_matrixDim.rows == rightEle._matrixDim.rows && _matrixDim.cols == rightEle._matrixDim.cols)
    {
        Matrix res(_matrixDim.rows, _matrixDim.cols);
        for (int i = 0; i < (_matrixDim.rows*_matrixDim.cols); i++)
        {
            res[i] = (*this)[i] + rightEle[i];
        }
        return res;
    }
    std::cerr << ERR_MSG << std::endl;
    exit(EXIT_FAILURE);
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (_matrixDim.cols == m._matrixDim.rows)
    {
        Matrix res(_matrixDim.rows, m._matrixDim.cols);
        for (int i = 0; i < _matrixDim.rows; i++)
        {
            for (int j = 0; j < m._matrixDim.cols; j++)
            {
                res(i, j) = 0;
                for (int k = 0; k < m._matrixDim.rows; k++)
                {
                    res(i, j) += (*this)(i, k) * m(k, j);
                }
            }
        }
        return res;
    }
    std::cerr << ERR_MSG << std::endl;
    exit(EXIT_FAILURE);
}

Matrix Matrix::operator*(const float c) const
{
    Matrix res(*this);
    for (int i = 0; i < _matrixDim.rows * _matrixDim.cols; i++)
    {
        res[i] = res[i] * c;
    }
    return res;
}

Matrix operator*(float c, const Matrix& m)
{
    return m * c;
}

Matrix Matrix::operator+=(const Matrix &rightElem)
{
    *this  = *this + rightElem;
    return *this;
}

const float &Matrix::operator()(const int i, const int j) const
{
    if (_ifLegalIndex(i, this->getRows()) && _ifLegalIndex(j, this->getCols()))
    {
        return _matrixArray[i * _matrixDim.cols + j];
    }
    exit(EXIT_FAILURE);
}

float &Matrix::operator()(const int i, const int j)
{
    if (_ifLegalIndex(i, this->getRows()) && _ifLegalIndex(j, this->getCols()))
    {
        return _matrixArray[i * _matrixDim.cols + j];
    }
    exit(EXIT_FAILURE);
}

float &Matrix::operator[](int i)
{
    if (!_ifLegalIndex(i, this->getCols() * this->getRows()))
    {
        exit(EXIT_FAILURE);
    }
    return _matrixArray[i];
}

float &Matrix::operator[](int i) const
{
    if (!_ifLegalIndex(i, this->getCols() * this->getRows()))
    {
        exit(EXIT_FAILURE);
    }
    return _matrixArray[i];
}

std::istream& operator>>(std::istream &is, Matrix& m)
{
    int i = 0;
    while (i < m.getCols()*m.getRows() && is.read(reinterpret_cast<char*>(&m[i]), sizeof(float)))
    {
        i++;
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Matrix& m)
{
    for (int i = 0; i < m._matrixDim.rows; i++)
    {
        for (int j = 0; j < m._matrixDim.cols; j++)
        {
            if (m(i, j) <= 0.1f)
            {
                std::cout << DOUBLE_SPACE;
            }
            else
            {
                std::cout << DOUBLE_ASTERISK;
            }
        }
        std::cout << NEW_LINE;
    }
    return os;
}

int Matrix::_ifLegalIndex(const int num, const int boundary) const
{
    if (num >= 0 && num < boundary)
    {
        return SUCCESS;
    }
    return FAILURE;
}
