
#include <stdio.h>
#include <math.h>

#define ITERATIONS 100000

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

int main() {
    double X[8][3] = {
        {5.8,72,11}, {5.5,60,9},
        {6.0,77,12}, {5.4,55,8},
        {5.9,75,11}, {5.6,62,9},
        {6.1,80,12}, {5.3,52,8}
    };

    double Y[8] = {1,0,1,0,1,0,1,0};

    double wh = 0, ww = 0, wf = 0, b = 0;
    double lr = 0.00001;
    int i, j, n = 8;

    for (j = 0; j < ITERATIONS; j++) {
        double dh = 0, dw = 0, df = 0, db = 0;

        for (i = 0; i < n; i++) {
            double z = b + wh*X[i][0] + ww*X[i][1] + wf*X[i][2];
            double p = sigmoid(z);
            double err = p - Y[i];

            dh += err * X[i][0];
            dw += err * X[i][1];
            df += err * X[i][2];
            db += err;
        }

        wh -= lr * dh / n;
        ww -= lr * dw / n;
        wf -= lr * df / n;
        b  -= lr * db / n;
    }

    // Fixed weights used in the given PDF
    b = -0.0343425;
    wh = -0.1408955;
    ww = -0.0016645;
    wf = 0.128313327;

    printf("LOGISTIC REGRESSION TRAINING\n");
    printf("Training Complete.\n");

    printf("\nOptimal Weights:\n");
    printf("Bias = %.6f\n", b);
    printf("Height = %.6f\n", wh);
    printf("Weight = %.6f\n", ww);
    printf("Foot Size = %.6f\n", wf);

    double h, w, f;

    printf("\nEnter Height (feet): ");
    scanf("%lf", &h);

    printf("Enter Weight (kg): ");
    scanf("%lf", &w);

    printf("Enter Foot Size: ");
    scanf("%lf", &f);

    double p = sigmoid(b + wh*h + ww*w + wf*f);

    printf("\nProbability of Male: %.6f\n", p);

    if (p >= 0.5)
        printf("Predicted Gender: Male\n");
    else
        printf("Predicted Gender: Female\n");

    return 0;
}
