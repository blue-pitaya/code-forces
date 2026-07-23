#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char bool;

bool is_safe(int *nums, int size, int idx_to_ignr) {
    int num, last_num, diff, last_diff;
    int nums_checked = 0;

    for (int i = 0; i < size; i++) {
        if (i == idx_to_ignr) {
            continue;
        }

        num = nums[i];
        diff = num - last_num;

        if (nums_checked == 0) {
        } else if (nums_checked == 1) {
            if (!(abs(diff) >= 1 && abs(diff) <= 3)) {
                return FALSE;
            }
        } else {
            if (!(abs(diff) >= 1 && abs(diff) <= 3 &&
                  ((last_diff > 0 && diff > 0) ||
                   (last_diff < 0 && diff < 0)))) {
                return FALSE;
            }
        }

        last_diff = diff;
        last_num = num;
        nums_checked++;
    }

    return TRUE;
}

void part1() {
    int safe_combinations = 0;
    int nums[16];
    int nums_len = 0;

    int a;
    char ch;
    while (scanf("%d%c", &a, &ch) == 2) {
        nums[nums_len] = a;
        nums_len++;

        if (ch != ' ') {
            if (is_safe(nums, nums_len, -1)) {
                safe_combinations++;
            }

            nums_len = 0;
        }
    }

    printf("%d\n", safe_combinations);
}

void part2() {
    int safe_combinations = 0;
    int nums[16];
    int nums_len = 0;
    bool safe_found = FALSE;

    int a;
    char ch;
    while (scanf("%d%c", &a, &ch) == 2) {
        nums[nums_len] = a;
        nums_len++;

        if (ch != ' ') {
            safe_found = FALSE;
            for (int idx_to_ignr = -1; idx_to_ignr < nums_len; idx_to_ignr++) {
                if (is_safe(nums, nums_len, idx_to_ignr)) {
                    safe_found = TRUE;
                }
            }

            if (safe_found) {
                safe_combinations++;
            }

            nums_len = 0;
        }
    }

    printf("%d\n", safe_combinations);
}

int main() {
    // part1();
    part2();

    return 0;
}
