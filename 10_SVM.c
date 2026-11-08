#include <stdio.h>

#define N 4
#define FEATURES 2
#define EPOCHS 100
#define LR 0.1

typedef struct
{
    double x[FEATURES];
    int label;
} DataPoint;

double dotProduct(double w[], double x[])
{
    int i;
    double sum = 0.0;

    for (i = 0; i < FEATURES; i++)
        sum += w[i] * x[i];

    return sum;
}

int predict(double w[], double b, double x[])
{
    return (dotProduct(w, x) + b >= 0) ? 1 : -1;
}

int main()
{
    DataPoint data[N] = {
        {{2.0, 3.0}, 1},
        {{3.0, 3.0}, 1},
        {{1.0, 1.0}, -1},
        {{2.0, 1.0}, -1}
    };

    double test[][FEATURES] = {
        {1.5, 2.0},
        {3.0, 2.0}
    };

    double w[FEATURES] = {0.0, 0.0};
    double b = 0.0;

    int i, j, epoch;

    for (epoch = 0; epoch < EPOCHS; epoch++)
    {
        for (i = 0; i < N; i++)
        {
            int prediction = predict(w, b, data[i].x);

            if (prediction != data[i].label)
            {
                for (j = 0; j < FEATURES; j++)
                    w[j] += LR * data[i].label *
                            data[i].x[j];

                b += LR * data[i].label;
            }
        }
    }

    printf("Trained SVM weights:\n");

    printf("w1 = %f, w2 = %f, b = %f\n",
           w[0], w[1], b);

    printf("\nPredictions on training data:\n");

    for (i = 0; i < N; i++)
    {
        printf("(%.6f, %.6f) -> %d\n",
               data[i].x[0], data[i].x[1],
               predict(w, b, data[i].x));
    }

    printf("\nPredictions on new points:\n");

    for (i = 0; i < 2; i++)
    {
        printf("(%.6f, %.6f) -> %d\n",
               test[i][0], test[i][1],
               predict(w, b, test[i]));
    }

    return 0;
}
