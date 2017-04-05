#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//
// Created by lirfu on 05.04.17..
//

int main() {
    int i, size, wght;


    // Statictics
    int min, max;
    double avg;

    srand(time(NULL));

    printf("Please enter the number of items to generate: ");
    scanf("%d", &size);
    printf("Please enter the maximum item weight: ");
    scanf("%d", &size);
    printf("Please enter the maximum item profit: ");
    scanf("%d", &size);

    wght = rand();

    avg = wght;
    min = max = wght;

    for (i = 1; i < size; i++) {
        wght = rand();
        avg += wght;

        if (wght < min) min = wght;
        if (wght > max) max = wght;
    }

    avg /= size;

    printf("Statictics:\n");
    printf("\tmin: %d", min);
    printf("\tmax: %d", max);
    printf("\tavg: %.2f", avg);

    return 0;
}

