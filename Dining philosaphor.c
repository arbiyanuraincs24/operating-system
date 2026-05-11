#include <stdio.h>

int main() {
    int n, hungry, choice;
    int pos[10], i, j;


    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);


    printf("How many are hungry: ");
    scanf("%d", &hungry);


    for (i = 0; i < hungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    do {

        printf("\n===== DINING PHILOSOPHERS MENU =====\n");
        printf("1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        if (choice == 1) {

            printf("\nAllow one philosopher to eat at any time\n\n");

            for (i = 0; i < hungry; i++) {


                for (j = 0; j < hungry; j++) {
                    if (j != i) {
                        printf("P %d is waiting\n", pos[j]);
                    }
                }


                printf("P %d is granted to eat\n", pos[i]);


                printf("P %d has finished eating\n\n", pos[i]);
            }
        }

        else if (choice == 2) {

            printf("\nAllow two philosophers to eat at same time\n\n");

            for (i = 0; i < hungry; i += 2) {


                printf("P %d is granted to eat\n", pos[i]);


                if (i + 1 < hungry) {

                    if ((pos[i] % n) + 1 == pos[i + 1] ||
                        (pos[i + 1] % n) + 1 == pos[i]) {

                        printf("P %d is waiting (conflict with P %d)\n",
                               pos[i + 1], pos[i]);
                    }
                    else {
                        printf("P %d is granted to eat\n", pos[i + 1]);
                    }
                }


                printf("P %d has finished eating\n", pos[i]);

                if (i + 1 < hungry) {

                    if (!(((pos[i] % n) + 1 == pos[i + 1]) ||
                          ((pos[i + 1] % n) + 1 == pos[i]))) {

                        printf("P %d has finished eating\n", pos[i + 1]);
                    }
                }

                printf("\n");
            }
        }


        else if (choice != 3) {
            printf("Invalid choice!\n");
        }

    } while (choice != 3);

    printf("\nProgram terminated.\n");

    return 0;
}
