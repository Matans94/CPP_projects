// ------------------------------ includes ------------------------------

#include <string>
#include <vector>
#include "Fractal.h"
#include <cmath>

// -------------------------- const definitions -------------------------

#define SIERPINSKI_CARPET_COLS 3
#define SIERPINSKI_TRIANGLE_COLS 2
#define VICSEK_COLS 3
#define FRACTAL_SPACE ' '
#define SIERPINSKI_CARPET_FIRST_ROW "###"
#define SIERPINSKI_CARPET_SEC_ROW "# #"
#define SIERPINSKI_CARPET_THIRD_ROW "###"
#define SIERPINSKI_TRIANGLE_FIRST_ROW "##"
#define SIERPINSKI_TRIANGLE_SEC_ROW "# "
#define VICSEK_FRACTAL_FIRST_ROW "# #"
#define VICSEK_FRACTAL_SEC_ROW " # "
#define VICSEK_FRACTAL_THIRD_ROW "# #"

// -------------------------- Implementations ---------------------------

/**
 * C'tor of an abstract class. Initialize all the members that in the abstract class.
 * @param colsBase - The number of cols in the basic fractal.
 * @param dim - The dimintion of the fractal need to be drawn.
 */
Fractal::Fractal(int colsBase, int dim)
        : _colsBase(colsBase), _dim(dim)
{
    _resCols = (int) pow(_colsBase, _dim);
    std::string baseOutputString(_resCols, FRACTAL_SPACE);
    _resFractal = std::vector<std::string>(_resCols, baseOutputString);
}

/**
 * Print the fractal in the after it was drawn in the right dim.
 */
void Fractal::print() const
{
    std::vector<std::string> printVector = (_resCols == _colsBase) ? _baseFractal : _resFractal;

    for (int i = 0; i < _resCols; i++)
    {
        std::cout << printVector[i] << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Recursive method to create the fractal.
 * @param dim - the dim of current view.
 * @param boardSize - The size of the col in the board.
 * @param row - the row index.
 * @param col - the col index.
 */
void Fractal::_recursiveDraw(int dim, int boardSize, int row, int col)
{
    if (dim == 1)
    {
        for (int index = 0; index < _colsBase; index++)
        {
            _resFractal[row + index].replace(col, _colsBase, _baseFractal[index]);
        }
    }
    else
    {
        for (int i = 0; i < boardSize; i += boardSize / _colsBase)
        {
            for (int j = 0; j < boardSize; j += boardSize / _colsBase)
            {
                if (ifIndexMatchFractalCond(i, j, boardSize / _colsBase))
                {
                    _recursiveDraw(dim - 1, boardSize / _colsBase, row + i, col + j);
                }
            }
        }
    }
}

/**
 * Method that all the derived classes are use. it draw the fractal with the dim that was given.
 * It calls a recursive method to create the fractal.
 */
void Fractal::drawFractal()
{
    if (_dim == 0)
    {
        std::cout << FRACTAL_DRAWER << std::endl;
    }
    else
    {
        _recursiveDraw(_dim, _resCols, 0, 0);
    }
}


SierpinskiCarpet::SierpinskiCarpet(const int dim)
        : Fractal(SIERPINSKI_CARPET_COLS, dim)
{
    _baseFractal = std::vector<std::string>(SIERPINSKI_CARPET_COLS);
    _baseFractal[0] = SIERPINSKI_CARPET_FIRST_ROW;
    _baseFractal[1] = SIERPINSKI_CARPET_SEC_ROW;
    _baseFractal[2] = SIERPINSKI_CARPET_THIRD_ROW;
}

/**
 * helper method to the recursive method. It decide when to go to the recursive func again.
 * It's stands for the pattern to be save.
 * @param i - index of row
 * @param j - index of col
 * @param size - The size of the dim in the iterative.
 * @return - boolian value. if its stands the pattern-true, otherwise false.
 */
bool SierpinskiCarpet::ifIndexMatchFractalCond(int i, int j, int size)
{
    return (i != j || i != size);
}


SierpinskiTriangle::SierpinskiTriangle(const int dim)
        : Fractal(SIERPINSKI_TRIANGLE_COLS, dim)
{
    _baseFractal = std::vector<std::string>(SIERPINSKI_TRIANGLE_COLS);
    _baseFractal[0] = SIERPINSKI_TRIANGLE_FIRST_ROW;
    _baseFractal[1] = SIERPINSKI_TRIANGLE_SEC_ROW;
}

/**
 * helper method to the recursive method. It decide when to go to the recursive func again.
 * It's stands for the pattern to be save.
 * @param i - index of row
 * @param j - index of col
 * @param size - The size of the dim in the iterative.
 * @return - boolian value. if its stands the pattern-true, otherwise false.
 */
bool SierpinskiTriangle::ifIndexMatchFractalCond(const int i, const int j, const int size)
{
    return (i != j || i != size || j != size);
}


VicsekFractal::VicsekFractal(const int dim)
        : Fractal(VICSEK_COLS, dim)
{
    _baseFractal = std::vector<std::string>(VICSEK_COLS);
    _baseFractal[0] = VICSEK_FRACTAL_FIRST_ROW;
    _baseFractal[1] = VICSEK_FRACTAL_SEC_ROW;
    _baseFractal[2] = VICSEK_FRACTAL_THIRD_ROW;
}

/**
 * helper method to the recursive method. It decide when to go to the recursive func again.
 * It's stands for the pattern to be save.
 * @param i - index of row
 * @param j - index of col
 * @param size - The size of the dim in the iterative.
 * @return - boolian value. if its stands the pattern-true, otherwise false.
 */
bool VicsekFractal::ifIndexMatchFractalCond(int i, int j, int size)
{
    return (i != size && j != size) || i == j;
}
