#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUTS 3
#define HIDDEN 4
#define OUTPUTS 1
#define SAMPLES 8
#define EPOCHS 10000

double input[SAMPLES][INPUTS];
double target[SAMPLES];
double w1[INPUTS][HIDDEN];
double b1[HIDDEN];
double w2[HIDDEN];
double b2;

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double y)
{
    return y * (1.0 - y);
}

void initialize()
{
    int i, j;

    for (i = 0; i < INPUTS; i++)
        for (j = 0; j < HIDDEN; j++)
            w1[i][j] = ((double)rand() / RAND_MAX) - 0.5;

    for (i = 0; i < HIDDEN; i++)
    {
        b1[i] = ((double)rand() / RAND_MAX) - 0.5;
        w2[i] = ((double)rand() / RAND_MAX) - 0.5;
    }

    b2 = ((double)rand() / RAND_MAX) - 0.5;
}

double forward(double x[], double hidden[])
{
    int i, j;
    double sum, output;

    for (j = 0; j < HIDDEN; j++)
    {
        sum = b1[j];

        for (i = 0; i < INPUTS; i++)
            sum += x[i] * w1[i][j];

        hidden[j] = sigmoid(sum);
    }

    output = b2;

    for (j = 0; j < HIDDEN; j++)
        output += hidden[j] * w2[j];

    return sigmoid(output);
}

int main()
{
    int i, j, k, epoch;
    int ones;

    double hidden[HIDDEN];
    double output, error, delta_out;
    double delta_hidden[HIDDEN];

    double learning_rate = 0.5;
    double total_error;

    srand(1);

    for (i = 0; i < SAMPLES; i++)
    {
        ones = 0;

        for (j = 0; j < INPUTS; j++)
        {
            input[i][j] = (i >> (INPUTS - 1 - j)) & 1;
            ones += (int)input[i][j];
        }

        target[i] = ones % 2;
    }

    initialize();

    for (epoch = 0; epoch < EPOCHS; epoch++)
    {
        total_error = 0.0;

        for (i = 0; i < SAMPLES; i++)
        {
            output = forward(input[i], hidden);

            error = target[i] - output;

            total_error += 0.5 * error * error;

            delta_out = error * sigmoid_derivative(output);

            for (j = 0; j < HIDDEN; j++)
            {
                delta_hidden[j] =
                    delta_out * w2[j] *
                    sigmoid_derivative(hidden[j]);
            }

            for (j = 0; j < HIDDEN; j++)
                w2[j] += learning_rate *
                         delta_out * hidden[j];

            b2 += learning_rate * delta_out;

            for (j = 0; j < HIDDEN; j++)
            {
                for (k = 0; k < INPUTS; k++)
                    w1[k][j] += learning_rate *
                                delta_hidden[j] * input[i][k];

                b1[j] += learning_rate * delta_hidden[j];
            }
        }

        if (epoch % 1000 == 0)
            printf("Epoch %d, Error=%.6f\n",
                   epoch, total_error);
    }

    printf("\nTesting trained MLP on parity problem:\n\n");

    for (i = 0; i < SAMPLES; i++)
    {
        output = forward(input[i], hidden);

        printf("Input: %.0f%.0f%.0f -> Output: %.4f "
               "(Target=%.0f)\n",
               input[i][0], input[i][1], input[i][2],
               output, target[i]);
    }

    return 0;
}