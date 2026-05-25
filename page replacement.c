#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int frame[10], i, j, k = 0, flag, faults = 0;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");

    for(i = 0; i < n; i++) {
        flag = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            frame[k] = pages[i];
            k = (k + 1) % frames;
            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++) {
                if(frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("FIFO Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int frames) {
    int frame[10], time[10];
    int i, j, pos, faults = 0, counter = 0, flag;

    for(i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");

    for(i = 0; i < n; i++) {
        flag = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            pos = 0;

            for(j = 1; j < frames; j++) {
                if(time[j] < time[pos])
                    pos = j;
            }

            counter++;
            frame[pos] = pages[i];
            time[pos] = counter;
            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++) {
                if(frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("LRU Page Faults: %d\n", faults);
}

int predict(int pages[], int frame[], int n, int index, int frames) {
    int i, j, farthest = index, pos = -1;

    for(i = 0; i < frames; i++) {
        for(j = index; j < n; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if(j == n)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int n, int frames) {
    int frame[10];
    int i, j, faults = 0, filled = 0, flag;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for(i = 0; i < n; i++) {
        flag = 0;

        for(j = 0; j < filled; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            if(filled < frames) {
                frame[filled++] = pages[i];
            } else {
                int pos = predict(pages, frame, n, i + 1, frames);
                frame[pos] = pages[i];
            }

            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++) {
                if(frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int frames, n, i;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
