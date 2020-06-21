
#ifndef EX2_FRACTAL_H
#define EX2_FRACTAL_H
// ------------------------------ includes ------------------------------
#include <iostream>
#include "vector"
#include "string"

// -------------------------- const definitions -------------------------
#define FRACTAL_DRAWER "#"

/**
 * enum of Tree types.
 */
enum Tree
{
    sierpinskiCarpet = 1,
    sierpinskiTriangle = 2,
    vicsekFractal = 3
};

// ------------------------------- classes ------------------------------

/**
 * Abstract class of Fractal.
 */
class Fractal
{
private:
    /**
     * Recursive method to create the fractal.
     * @param dim - the dim of current view.
     * @param boardSize - The size of the col in the board.
     * @param row - the row index.
     * @param col - the col index.
     */
    void _recursiveDraw(int dim, int boardSize, int row, int col);

    int _colsBase;
    int _resCols;
    int _dim;
    std::vector<std::string> _resFractal;
protected:
    std::vector<std::string> _baseFractal;

    /**
     * C'tor of an abstract class. Initialize all the members that in the abstract class.
     * @param colsBase - The number of cols in the basic fractal.
     * @param dim - The dimintion of the fractal need to be drawn.
     */
    Fractal(int colsBase, int dim);

public:
    /**
     * Method that all the derived classes are use. it draw the fractal with the dim that was given.
     * It calls a recursive method to create the fractal.
     */
    void drawFractal();

    /**
     * Print the fractal in the after it was drawn in the right dim.
     */
    void print() const;

    /**
     * helper method to the recursive method. It decide when to go to the recursive func again.
     * It's stands for the pattern to be save.
     * @param i - index of row
     * @param j - index of col
     * @param size - The size of the dim in the iterative.
     * @return - boolian value. if its stands the pattern-true, otherwise false.
     */
    virtual bool ifIndexMatchFractalCond(int i, int j, int size) = 0;

    /**
     * Default D'tor for abstract class.
     */
    virtual ~Fractal() = default;
};

/**
 * Sierpinski Carpet Fractal type.
 */
class SierpinskiCarpet : public Fractal
{
public:
    /**
     * C'tor for fractal type class. initialize in the initialize list the Fractal class C'tor.
     * @param dim - The dim that the fractal holds and the could be draw and print.
     */
    explicit SierpinskiCarpet(int dim);

    bool ifIndexMatchFractalCond(int i, int j, int size) override;
};

/**
 * Sierpinski Triangle Fractal type.
 */
class SierpinskiTriangle : public Fractal
{
public:
    bool ifIndexMatchFractalCond(int i, int j, int size) override;

    /**
     * C'tor for fractal type class. initialize in the initialize list the Fractal class C'tor.
     * @param dim - The dim that the fractal holds and the could be draw and print.
     */
    explicit SierpinskiTriangle(int dim);
};

/**
 * Vicsek Fractal type.
 */
class VicsekFractal : public Fractal
{
public:
    bool ifIndexMatchFractalCond(int i, int j, int size) override;

    /**
     * C'tor for fractal type class. initialize in the initialize list the Fractal class C'tor.
     * @param dim - The dim that the fractal holds and the could be draw and print.
     */
    explicit VicsekFractal(int dim);
};

#endif //EX2_FRACTAL_H