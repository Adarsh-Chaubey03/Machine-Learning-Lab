#include <stdio.h>

int main()
{
    int actual[] = {1, 1, 1, 1, 0, 0, 0, 0};
    int predicted[] = {1, 1, 1, 0, 1, 0, 0, 0};

    int n = sizeof(actual) / sizeof(actual[0]);

    int TP = 0, TN = 0, FP = 0, FN = 0;
    int i;
    float accuracy;

    for (i = 0; i < n; i++)
    {
        if (actual[i] == 1 && predicted[i] == 1)
            TP++;

        else if (actual[i] == 0 && predicted[i] == 0)
            TN++;

        else if (actual[i] == 0 && predicted[i] == 1)
            FP++;

        else if (actual[i] == 1 && predicted[i] == 0)
            FN++;
    }

    printf("Confusion Matrix\n\n");
    printf("        Predicted\n");
    printf("       Positive Negative\n");

    printf("Actual Positive %d      %d\n", TP, FN);
    printf("Actual Negative %d       %d\n", FP, TN);

    accuracy = (float)(TP + TN) / n * 100;

    printf("\nTP = %d\n", TP);
    printf("TN = %d\n", TN);
    printf("FP = %d\n", FP);
    printf("FN = %d\n", FN);

    printf("Accuracy = %.2f%%\n", accuracy);

    return 0;
}
