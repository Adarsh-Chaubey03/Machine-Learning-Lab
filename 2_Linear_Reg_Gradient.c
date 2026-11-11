
#include <stdio.h>

int main()
{
    int n, epochs;
    float x[100], y[100], weight[100];
    float w = 0, b = 0, lr;
    float dw, db, wmse;

    printf("Weighted Linear Regression\n");

    printf("Enter number of data points: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter X, Y and Weight: ");
        scanf("%f %f %f", &x[i], &y[i], &weight[i]);
    }

    printf("Enter Learning Rate: ");
    scanf("%f", &lr);

    printf("Enter Number of Epochs: ");
    scanf("%d", &epochs);

    for (int epoch = 1; epoch <= epochs; epoch++)
    {
        dw = 0;
        db = 0;
        wmse = 0;

        for (int i = 0; i < n; i++)
        {
            float prediction = w * x[i] + b;
            float error = prediction - y[i];

            dw += weight[i] * error * x[i];
            db += weight[i] * error;
            wmse += weight[i] * error * error;
        }

        dw = (2.0 / n) * dw;
        db = (2.0 / n) * db;
        wmse = wmse / n;

        w = w - lr * dw;
        b = b - lr * db;

        printf("Epoch %d WMSE = %.6f\n", epoch, wmse);
    }

    printf("\nFinal Weight = %.4f\n", w);
    printf("Final Bias = %.4f\n", b);

    printf("Regression Equation: Y = %.4fX + %.4f\n", w, b);

    printf("\nX\tActual Y\tWeight\tPredicted Y\n");

    wmse = 0;

    for (int i = 0; i < n; i++)
    {
        float prediction = w * x[i] + b;
        float error = prediction - y[i];

        wmse += weight[i] * error * error;

        printf("%.2f\t%.2f\t\t%.2f\t%.2f\n",
               x[i], y[i], weight[i], prediction);
    }

    wmse = wmse / n;

    printf("\nFinal WMSE = %.6f\n", wmse);

    return 0;
}