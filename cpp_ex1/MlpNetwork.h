//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

/**
 * Organize the order of the layers to the structure of the net. Its allowed the input to the net
 * and the valid output.
 */
class MlpNetwork
{
public:

    /**
     * Accepts 2 arrays, size 4 each. one for weights and one for biases. constructs the network
     */
    MlpNetwork(Matrix *weights, Matrix *biases);

    /**
     * Applies the entire network on input returns digit struct.
     */
    Digit operator()(const Matrix& img);

private:
Matrix _w[MLP_SIZE], _bias[MLP_SIZE];
};

#endif // MLPNETWORK_H
