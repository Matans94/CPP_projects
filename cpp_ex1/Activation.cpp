//
// Created by matans on 23/12/2019.
//

#include <cstdlib>
#include <cmath>
#include "Activation.h"
#define ERR_MSG "Wrong input ! "


/**
 * Accepts activation type (Relu/Softmax) and defines this instance's activation accordingly.
 * @param actType - The type of activation.
 */
Activation::Activation(ActivationType actType):
_actType(actType)
{}

ActivationType Activation::getActivationType()
{
    return _actType;
}

//The matrix is vector - (n,1)
Matrix Activation::operator()(const Matrix &m) const
{
    if (_actType == Relu)
    {
        return _relu(m);
    }
    else if (_actType == Softmax)
    {
        return _softmax(m);
    }
    else
    {
        std::cerr << ERR_MSG << std::endl;
        exit(EXIT_FAILURE);
    }
}

Matrix Activation::_relu(const Matrix &matrix) const
{
    for (int i = 0; i < matrix.getRows(); i++)
    {
        if (matrix[i] < 0)
        {
            matrix[i] = 0;
        }
    }
    return matrix;
}

Matrix Activation::_softmax(const Matrix &matrix) const
{
    Matrix res(matrix);
    float expSummation = 0;
    for (int i = 0; i < res.getRows(); i++)
    {
        res[i] = std::exp(res[i]);
        expSummation += res[i];
    }
    return (res*(1 / expSummation));
}







