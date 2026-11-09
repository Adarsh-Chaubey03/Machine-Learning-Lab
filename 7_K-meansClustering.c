
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 16
#define SIZE 256

int main()
{
    int image[3][3];
    int centroid[K];
    int newCentroid[K];
    int count[K];

    int i, j, k, value, cluster;
    int changed;

    // Initialize centroids
    for (k = 0; k < K; k++)
        centroid[k] = k * 16 + 2;

    // Read 3x3 grayscale image
    printf("Enter 3x3 grayscale image values (0-255):\n");

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &image[i][j]);

    // Display initial centroids
    printf("\nInitial centroids:\n");

    for (k = 0; k < K; k++)
        printf("%d ", centroid[k]);

    printf("\n");

    // K-Means training
    do
    {
        changed = 0;

        // Reset cluster counts and sums
        for (k = 0; k < K; k++)
        {
            count[k] = 0;
            newCentroid[k] = 0;
        }

        // Assign all grayscale values to nearest centroid
        for (value = 0; value < SIZE; value++)
        {
            cluster = 0;

            for (k = 1; k < K; k++)
            {
                if (abs(value - centroid[k]) <
                    abs(value - centroid[cluster]))
                {
                    cluster = k;
                }
            }

            newCentroid[cluster] += value;
            count[cluster]++;
        }

        // Calculate and update centroids
        for (k = 0; k < K; k++)
        {
            if (count[k] > 0)
                newCentroid[k] /= count[k];
            else
                newCentroid[k] = centroid[k];

            if (newCentroid[k] != centroid[k])
                changed = 1;

            centroid[k] = newCentroid[k];
        }

    } while (changed);

    // Display final centroids
    printf("\nFinal centroids:\n");

    for (k = 0; k < K; k++)
        printf("%d ", centroid[k]);

    printf("\n\nQuantized color (cluster indices 0-15):\n");

    // Quantize the image
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cluster = 0;

            for (k = 1; k < K; k++)
            {
                if (abs(image[i][j] - centroid[k]) <
                    abs(image[i][j] - centroid[cluster]))
                {
                    cluster = k;
                }
            }

            printf("%d ", cluster);
        }

        printf("\n");
    }

    return 0;
}
