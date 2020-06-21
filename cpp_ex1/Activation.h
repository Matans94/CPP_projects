//Activation.h
#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * The class that sets the activation functions.
 */
class Activation
{
public:
    ActivationType _actType;

    /**
     * Accepts activation type (Relu/Softmax) and defines this instace’s activation accordingly
     * @param actType - The type of action.
     */
    explicit Activation(ActivationType actType);

    /**
     * @return- this activation’s type(Relu/Softmax)
     */
    ActivationType getActivationType();

    /**
     * Applies activation function on input.
     * @param m - the matrix to activate the function.
     * @return - The matrix after the activation func.
     */
    Matrix operator()(const Matrix &m) const;
private:

    /**
     * check every val in the matrix array . if the the val is smaller than zero it change it to
     * 0 otherwise it stills the same.
     * @param matrix - The matrix for activations,
     * @return - The matrix after this activation func.
     */
    Matrix _relu(const Matrix &matrix) const;

    /**
     * takes the vector and do a summation of every val with an exp. after that it multipucate
     * it with the vector.
     * @param  - The vector for activations,
     * @return - The matrix after this activation func.
     */
    Matrix _softmax(const Matrix &matrix) const;
};
#endif //ACTIVATION_H
