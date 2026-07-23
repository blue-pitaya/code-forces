#include <stdio.h>
#include <stdlib.h>
#define NUMS 1024

typedef unsigned int uint;

int compare_int(const void *a, const void *b) {
    const int *x = (const int *)a;
    const int *y = (const int *)b;

    if (*x < *y)
        return -1;
    if (*x > *y)
        return 1;
    return 0;
}

void part1() {
    int left[NUMS], right[NUMS];
    int nums_n;

    while (scanf("%d %d", &left[nums_n], &right[nums_n]) == 2) {
        nums_n++;
    }

    qsort(left, nums_n, sizeof(int), compare_int);
    qsort(right, nums_n, sizeof(int), compare_int);

    uint total = 0;
    for (uint i = 0; i < nums_n; i++) {
        total += abs(left[i] - right[i]);
    }

    printf("%d\n", total);
}

// could be made by hash map but im too lazy to implemet it xd
void part2() {
    int left[NUMS], right[NUMS];
    int nums_n;

    while (scanf("%d %d", &left[nums_n], &right[nums_n]) == 2) {
        nums_n++;
    }

    uint total = 0;
    uint amount = 0;
    for (uint i = 0; i < nums_n; i++) {
        amount = 0;
        for (uint j = 0; j < nums_n; j++) {
            if (left[i] == right[j]) {
                amount++;
            }
        }

        total += left[i] * amount;
    }

    printf("%d\n", total);
}

int main() {
    // part1();
    part2();

    return 0;
}
