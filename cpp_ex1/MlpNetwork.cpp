//
// Created by matans on 23/12/2019.
//

#include "MlpNetwork.h"
#include "Matrix.h"
#include "Dense.h"
#include "Activation.h"

#define ERR_MSG "Wrong input ! "


#define OUTPUT_VECTOR_LEN 10

/**
 * Accepts 2 arrays, size 4 each. one for weights and one for biases. constructs the network
 */
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases)
{
    for (int i = 0; i < MLP_SIZE; i++)
    {
        if (weightsDims[i].cols == weights[i].getCols() &&
            weightsDims[i].rows == weights[i].getRows() &&
            biasDims[i].rows == biases[i].getRows() && biasDims[i].cols == biases[i].getCols())
        {
            _w[i] = weights[i];
            _bias[i] = biases[i];
        }
        else
        {
            std::cerr << ERR_MSG << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

Digit MlpNetwork::operator()(const Matrix &img)
{
    if (//img.getCols() == imgDims.cols && img.getRows() == imgDims.rows)
            img.getRows() * img.getCols() == imgDims.cols * imgDims.rows)
    {
        Matrix firstLayer = Dense(_w[0], _bias[0], Relu)(img);
        Matrix secLayer = Dense(_w[1], _bias[1], Relu)(firstLayer);
        Matrix thirdLayer = Dense(_w[2], _bias[2], Relu)(secLayer);
        Matrix forthLayer = Dense(_w[3], _bias[3], Softmax)(thirdLayer);

        float maxVal = 0;
        unsigned int maxIndex = 0;
        for (int i = 0; i < OUTPUT_VECTOR_LEN; i++)
        {
            if (maxVal < forthLayer[i])
            {
                maxVal = forthLayer[i];
                maxIndex = i;
            }
        }
        return Digit{maxIndex, maxVal};
    }
    else
    {
        std::cerr << ERR_MSG << std::endl;
        exit(EXIT_FAILURE);
    }
}

