//
// Created by matans on 23/12/2019.
//

#include "Dense.h"

/**
 * Inits a new layer with given parameters.
 * @param w - weights matrix.
 * @param bias - Bias Vector.
 * @param actType - The type of action to activate.
 */
Dense::Dense(const Matrix& w, const Matrix& bias, const ActivationType actType):
_w(w), _bias(bias), _actType(actType)
{}

Matrix Dense::getWeights() const
{
    return _w;
}

Matrix Dense::getBias() const
{
    return _bias;
}

ActivationType Dense::getActivation()
{
    return _actType.getActivationType();
}

Matrix Dense::operator()(const Matrix& input) const
{
    Matrix res;
    res = (_w*input) + _bias;
    return _actType(res);
}



