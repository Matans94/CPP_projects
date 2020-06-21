//
// Created by matans on 23/12/2019.
//

#ifndef EX1_DENSE_H
#define EX1_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * represent a layer for sets and activate the action functions on the layer in the new.
 */
class Dense
{
public:
    /**
     * Inits a new layer with given parameters.
     * @param w - weights matrix.
     * @param bias - Bias Vector.
     * @param actType - The type of action to activate.
     */
    Dense(const Matrix& w, const Matrix& bias, const ActivationType actType);

    /**
     * Returns the weights of this layer
     */
    Matrix getWeights() const ;

    /**
     * Returns the bias of this layer
     */
    Matrix getBias() const;

    /**
     * Returns the activation function of this layer
     */
    ActivationType getActivation() ;

    /**
     *  Applies the layer on input and returns output matrix Layers operate .
     */
    Matrix operator()(const Matrix& input) const;

private:

    /**
     * The matrixes of the weight and the bias.
     */
    Matrix _w, _bias;

    /**
     * The kind of action to operate.
     */
    Activation _actType;
};


#endif //EX1_DENSE_H
