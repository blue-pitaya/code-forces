#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 255
#define MAX_NUMS 50
#define LL long long

LL powll(LL a, LL n) {
    LL res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
    }
    return res;
}

LL part1(LL expected, int nums[], int nums_size) {
    LL permutations_size = powll(2, nums_size - 1);
    printf("Looking for: %lld\n", expected);
    for (LL i = 0; i < permutations_size; i++) {
        int current_number_idx = 0;
        LL current_permutation = i;

        LL current_res = nums[current_number_idx];
        printf("Checking: %d", nums[current_number_idx]);
        current_number_idx++;
        while (current_number_idx < nums_size) {
            if (current_permutation & 1) {
                current_res += nums[current_number_idx];
                printf(" + %d", nums[current_number_idx]);
            } else {
                current_res *= nums[current_number_idx];
                printf(" * %d", nums[current_number_idx]);
            }
            current_number_idx++;
            current_permutation >>= 1;
        }
        printf(" = %lld", current_res);

        if (current_res == expected) {
            printf(", FOUND!\n");
            return expected;
        } else {
            printf("\n");
        }
    }

    return 0;
}

LL part2(LL expected, const int nums[], int nums_size) {
    LL permutations_size = powll(3, nums_size - 1);

    printf("Looking for: %lld\n", expected);

    for (LL i = 0; i < permutations_size; i++) {
        int current_number_idx = 0;
        LL current_permutation = i;

        LL current_res = nums[current_number_idx];
        // printf("Checking: %d", nums[current_number_idx]);
        current_number_idx++;

        while (current_number_idx < nums_size) {
            int operand = current_permutation % 3;

            char num1[20] = {0};
            char num2[20] = {0};
            switch (operand) {
            case 0:
                current_res += nums[current_number_idx];
                // printf(" + %d", nums[current_number_idx]);
                break;
            case 1:
                current_res *= nums[current_number_idx];
                // printf(" * %d", nums[current_number_idx]);
                break;
            case 2:
                sprintf(num1, "%lld", current_res);
                sprintf(num2, "%d", nums[current_number_idx]);
                strcat(num1, num2);
                current_res = atoll(num1);

                // printf(" || %d (%lld)", nums[current_number_idx],
                // current_res);
                break;
            }

            current_number_idx++;
            current_permutation /= 3;
        }
        // printf(" = %lld", current_res);

        if (current_res == expected) {
            // printf("FOUND!\n");
            return expected;
        } else {
            // printf("\n");
        }
    }

    return 0;
}

int main() {
    char line[MAX_LINE];

    LL res;
    int nums[MAX_NUMS];
    int nums_size = 0;

    LL sum = 0;

    while (fgets(line, MAX_LINE, stdin)) {
        nums_size = 0;

        int offset = 0;
        int curr_offset = 0;
        sscanf(line, "%lld:%n", &res, &curr_offset);
        offset += curr_offset;

        while (offset < MAX_LINE &&
               sscanf(line + offset, "%d%n", &nums[nums_size], &curr_offset) ==
                   1) {
            nums_size++;
            offset += curr_offset;
        }

        // sum += part1(res, nums, nums_size);
        sum += part2(res, nums, nums_size);
    }

    printf("Sum: %lld\n", sum);

    return 0;
}
