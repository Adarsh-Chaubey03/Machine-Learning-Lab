#include <stdio.h>

int main() {

    float x[4][3] = {
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };

    int target[4] = {1, 1, 1, 0};

    float w[3] = {0.3, 0.0, 0.0};

    float learning_rate = 0.1;
    float threshold = 0.5;

    int epoch, i;

    float sum, error, output;

    for (epoch = 0; epoch < 8; epoch++) {

        printf("Number of count is %d\n", epoch);

        for (i = 0; i < 4; i++) {

            sum = x[i][0] * w[0] +
                  x[i][1] * w[1] +
                  x[i][2] * w[2];

            if (sum >= threshold)
                output = 1;
            else
                output = 0;

            error = target[i] - output;

            printf("Sum is %.6f\n", sum);
            printf("Error is %.0f\n", error);

            w[0] = w[0] + learning_rate * error * x[i][0];
            w[1] = w[1] + learning_rate * error * x[i][1];
            w[2] = w[2] + learning_rate * error * x[i][2];

            printf("Weight 0 = %.6f Weight 1 = %.6f Weight 2 = %.6f\n",
                   w[0], w[1], w[2]);
        }
    }

    printf("\nFinal Testing:\n");

    for (i = 0; i < 4; i++) {

        sum = x[i][0] * w[0] +
              x[i][1] * w[1] +
              x[i][2] * w[2];

        if (sum >= threshold)
            output = 1;
        else
            output = 0;

        printf("Sum is %.6f\n", sum);

        printf("The output for test data %d is: %.0f\n",
               i, output);
    }

    return 0;
}