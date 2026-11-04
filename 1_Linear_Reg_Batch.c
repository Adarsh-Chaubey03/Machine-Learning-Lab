
#include <stdio.h>

int main()
{
    int n, epochs, i, j;
    float x[100], y[100];
    float w = 0.0, b = 0.0, lr;
    float dw, db, prediction, error, mse = 0.0;

    printf("Linear Regression using Gradient Descent\n");
    printf("----------------------------------------\n");

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter X and Y values:\n");

    for (i = 0; i < n; i++)
    {
        printf("Data %d (X Y): ", i + 1);
        scanf("%f %f", &x[i], &y[i]);
    }

    printf("Enter Learning Rate: ");
    scanf("%f", &lr);

    printf("Enter Number of Epochs: ");
    scanf("%d", &epochs);

    for (i = 1; i <= epochs; i++)
    {
        dw = 0.0;
        db = 0.0;
        mse = 0.0;

        for (j = 0; j < n; j++)
        {
            prediction = w * x[j] + b;
            error = prediction - y[j];

            dw += error * x[j];
            db += error;
            mse += error * error;
        }

        dw = (2.0 / n) * dw;
        db = (2.0 / n) * db;
        mse = mse / n;

        w = w - lr * dw;
        b = b - lr * db;

        printf("Epoch %d MSE = %.6f\n", i, mse);
    }

    mse = 0.0;

    printf("----------------------------------------\n");
    printf("Training Completed Successfully\n");
    printf("----------------------------------------\n");

    printf("Final Weight (Slope) = %.4f\n", w);
    printf("Final Bias (Intercept) = %.4f\n", b);

    printf("Regression Equation:\n");
    printf("Y = %.4fX + %.4f\n", w, b);

    printf("---------------------------------------------\n");
    printf("X\tActual Y\tPredicted Y\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        prediction = w * x[i] + b;
        printf("%.2f\t%.2f\t\t%.2f\n", x[i], y[i], prediction);

        error = prediction - y[i];
        mse += error * error;
    }

    mse = mse / n;

    printf("---------------------------------------------\n");
    printf("Final Mean Squared Error (MSE) = %.6f\n", mse);

    return 0;
}
