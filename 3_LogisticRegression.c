
#include <stdio.h>
#include <math.h>

#define N 10
#define FEATURES 3

double X[N][FEATURES] = {
    {6.00, 77, 12},
    {5.92, 65, 11},
    {5.58, 64, 10},
    {5.92, 80, 12},

    {5.00, 49, 8},
    {5.50, 54, 9},
    {5.42, 60, 9},
    {5.75, 59, 10},
    {5.00, 55, 9},
    {5.50, 58, 9}
};

int Y[N] = {1, 1, 1, 1,0, 0, 0, 0, 0, 0};

double sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}

double calculateCost(double weights[], double bias)
{
    double cost = 0.0;

    for (int i = 0; i < N; i++)
    {
        double z = bias;

        for (int j = 0; j < FEATURES; j++)
        {
            z += weights[j] * X[i][j];
        }

        double prediction = sigmoid(z);

        if (prediction < 1e-15)
            prediction = 1e-15;

        if (prediction > 1 - 1e-15)
            prediction = 1 - 1e-15;

        cost += -(Y[i] * log(prediction) + (1 - Y[i]) * log(1 - prediction));
    }

    return cost / N;
}

int main()
{
    double weights[FEATURES] = {0.0, 0.0, 0.0};
    double bias = 0.0;

    double learningRate = 0.0001;

    int maxIterations = 100000;
    double tolerance = 1e-8;

    printf("============================================\n");
    printf("   LOGISTIC REGRESSION TRAINING\n");
    printf("============================================\n");

    printf("Learning Rate: %.6f\n", learningRate);

    double previousCost = 0.0;

    for (int iteration = 0; iteration < maxIterations; iteration++)
    {
        double dw[FEATURES] = {0.0, 0.0, 0.0};
        double db = 0.0;

        for (int i = 0; i < N; i++)
        {
            double z = bias;

            for (int j = 0; j < FEATURES; j++)
            {
                z += weights[j] * X[i][j];
            }

            double prediction = sigmoid(z);

            double error = prediction - Y[i];

            for (int j = 0; j < FEATURES; j++)
            {
                dw[j] += error * X[i][j];
            }

            db += error;
        }

        for (int j = 0; j < FEATURES; j++)
        {
            dw[j] /= N;
        }

        db /= N;

        for (int j = 0; j < FEATURES; j++)
        {
            weights[j] -= learningRate * dw[j];
        }

        bias -= learningRate * db;

        double cost = calculateCost(weights, bias);

        if (iteration > 0 && fabs(previousCost - cost) < tolerance)
        {
            break;
        }

        previousCost = cost;
    }

    printf("Training Complete.\n");

    printf("Optimal Weights:\n");
    printf("Bias = %.6f\n", bias);
    printf("Height = %.6f\n", weights[0]);
    printf("Weight = %.6f\n", weights[1]);
    printf("Foot Size = %.6f\n", weights[2]);

    double height, weight, footSize;

    printf("\nEnter details for prediction:\n");

    printf("Enter Height (feet): ");
    scanf("%lf", &height);

    printf("Enter Weight (kg): ");
    scanf("%lf", &weight);

    printf("Enter Foot Size: ");
    scanf("%lf", &footSize);

    double z = bias + weights[0] * height + weights[1] * weight + weights[2] * footSize;

    double probability = sigmoid(z);

    printf("\nProbability of Male: %.6f\n", probability);

    if (probability >= 0.5)
    {
        printf("Predicted Gender: Male\n");
    }
    else
    {
        printf("Predicted Gender: Female\n");
    }

    return 0;
}
