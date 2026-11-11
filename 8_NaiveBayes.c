
#include <stdio.h>
#include <string.h>

#define N 14
#define FEATURES 4
#define CLASSES 2

const char *data[N][FEATURES] = {
    {"Sunny", "Hot", "High", "Weak"},
    {"Sunny", "Hot", "High", "Strong"},
    {"Overcast", "Hot", "High", "Weak"},
    {"Rain", "Mild", "High", "Weak"},
    {"Rain", "Cool", "Normal", "Weak"},
    {"Rain", "Cool", "Normal", "Strong"},
    {"Overcast", "Cool", "Normal", "Strong"},
    {"Sunny", "Mild", "High", "Weak"},
    {"Sunny", "Cool", "Normal", "Weak"},
    {"Rain", "Mild", "Normal", "Weak"},
    {"Sunny", "Mild", "Normal", "Strong"},
    {"Overcast", "Mild", "High", "Strong"},
    {"Overcast", "Hot", "Normal", "Weak"},
    {"Rain", "Mild", "High", "Strong"}
};

int target[N] = {
    0, 0, 1, 1, 1, 0, 1,
    0, 1, 1, 1, 1, 1, 0
};

const char *values[FEATURES][3] = {
    {"Sunny", "Overcast", "Rain"},
    {"Hot", "Mild", "Cool"},
    {"High", "Normal", ""},
    {"Weak", "Strong", ""}
};

int categories[FEATURES] = {3, 3, 2, 2};

int encode(int feature, const char *value)
{
    int i;

    for (i = 0; i < categories[feature]; i++)
    {
        if (strcmp(value, values[feature][i]) == 0)
            return i;
    }

    return -1;
}

int predict(int test)
{
    int count[CLASSES] = {0};
    int freq[CLASSES][FEATURES][3] = {{{0}}};

    int i, j, c, v;
    double score[CLASSES];

    for (i = 0; i < N; i++)
    {
        if (i == test)
            continue;

        c = target[i];
        count[c]++;

        for (j = 0; j < FEATURES; j++)
        {
            v = encode(j, data[i][j]);

            if (v >= 0)
                freq[c][j][v]++;
        }
    }

    for (c = 0; c < CLASSES; c++)
    {
        score[c] = (double)count[c] / (N - 1);

        for (j = 0; j < FEATURES; j++)
        {
            v = encode(j, data[test][j]);

            score[c] *=
                (double)(freq[c][j][v] + 1) /
                (count[c] + categories[j]);
        }
    }

    return score[1] > score[0] ? 1 : 0;
}

int main()
{
    int i, predicted;

    int tp = 0, tn = 0, fp = 0, fn = 0;

    double accuracy, precision, recall;

    printf("Weather Forecasting Using Naive Bayes\n\n");
    printf("Record Actual Predicted\n");

    for (i = 0; i < N; i++)
    {
        predicted = predict(i);

        printf("%d %-6s %-6s\n",
               i + 1,
               target[i] ? "Yes" : "No",
               predicted ? "Yes" : "No");

        if (target[i] == 1 && predicted == 1)
            tp++;
        else if (target[i] == 0 && predicted == 0)
            tn++;
        else if (target[i] == 0 && predicted == 1)
            fp++;
        else
            fn++;
    }

    accuracy = (double)(tp + tn) / N * 100.0;

    precision = (tp + fp) ?
                (double)tp / (tp + fp) * 100.0 : 0.0;

    recall = (tp + fn) ?
             (double)tp / (tp + fn) * 100.0 : 0.0;

    printf("\nAccuracy = %.2f%%\n", accuracy);
    printf("Precision = %.2f%%\n", precision);
    printf("Recall = %.2f%%\n", recall);

    return 0;
}
