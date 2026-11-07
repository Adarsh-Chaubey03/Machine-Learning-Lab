#include <stdio.h>
#include <string.h>

int main() {

    char spam_words[5][20] = {
        "free", "win", "money", "offer", "cash"
    };

    char ham_words[5][20] = {
        "meeting", "project", "hello", "tomorrow", "friend"
    };

    int spam_counts[5] = {3, 2, 2, 2, 1};
    int ham_counts[5] = {2, 3, 2, 1, 1};

    int total_spam = 10;
    int total_ham = 9;

    char input[100];
    char word[20];

    int i, j, k = 0;

    float p_spam = 0.5;
    float p_ham = 0.5;

    printf("Enter a message to classify: ");
    fgets(input, sizeof(input), stdin);

    for (i = 0; i <= strlen(input); i++) {

        if (input[i] == ' ' ||
            input[i] == '\0' ||
            input[i] == '\n') {

            word[k] = '\0';

            if (k > 0) {

                int found_spam = 0;
                int found_ham = 0;

                for (j = 0; j < 5; j++) {

                    if (strcmp(word, spam_words[j]) == 0) {

                        p_spam *= (float)(spam_counts[j] + 1)
                                  / (total_spam + 5);

                        found_spam = 1;
                    }
                }

                if (!found_spam) {
                    p_spam *= 1.0 / (total_spam + 5);
                }

                for (j = 0; j < 5; j++) {

                    if (strcmp(word, ham_words[j]) == 0) {

                        p_ham *= (float)(ham_counts[j] + 1)
                                 / (total_ham + 5);

                        found_ham = 1;
                    }
                }

                if (!found_ham) {
                    p_ham *= 1.0 / (total_ham + 5);
                }
            }

            k = 0;

        } else {

            word[k++] = input[i];
        }
    }

    printf("\nProbability of Spam: %f\n", p_spam);

    printf("Probability of Non-Spam: %f\n", p_ham);

    if (p_spam > p_ham) {

        printf("\nResult: The message is SPAM.\n");

    } else {

        printf("\nResult: The message is NON-SPAM.\n");
    }

    return 0;
}