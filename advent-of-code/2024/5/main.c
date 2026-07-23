#include <stdio.h>

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

#define MAX_LINE 128

int find(int n, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == n) {
            return i;
        }
    }

    return -1;
}

void put_at(int idx, int n, int *arr, int size) {
    for (int i = size; i > idx; i--) {
        arr[i] = arr[i - 1];
    }
    arr[idx] = n;
}

void print_int_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int rules[2048][2];
    int rules_n = 0;

    int list[256][64];
    int list_n[256];
    int lists_amount = 0;

    int a, b;
    char line[MAX_LINE];
    char hit_spot = 0;
    while (fgets(line, MAX_LINE, stdin)) {
        if (!hit_spot) {
            if (sscanf(line, "%d|%d", &a, &b) == 2) {
                rules[rules_n][0] = a;
                rules[rules_n][1] = b;
                rules_n++;
            } else {
                hit_spot = 1;
            }
        } else {
            int nc;
            char *iter = line;
            char useless;
            int idx = 0;
            while (*iter && sscanf(iter, "%d%c%n", &a, &useless, &nc)) {
                iter += nc;
                list[lists_amount][idx] = a;
                idx++;
            }
            list_n[lists_amount] = idx;
            lists_amount++;
        }
    }

    // for (int i = 0; i < lists_amount; i++) {
    //     for (int j = 0; j < list_n[i]; j++) {
    //         printf("%d ", list[i][j]);
    //     }

    //    printf("\n");
    //}

    int sum = 0;
    int *curr_list;
    int size, num;

    int *bad_list[256];
    int bad_list_n[256];
    int bad_list_amount = 0;

    for (int test_case = 0; test_case < lists_amount; test_case++) {
        char fucked = 0;
        curr_list = list[test_case];
        size = list_n[test_case];

        for (int i = 0; i < size; i++) {
            num = curr_list[i];

            int check_num;
            int *curr_rule;
            // check numbers before
            for (int bf = 0; bf < i; bf++) {
                check_num = curr_list[bf];

                for (int rule_idx = 0; rule_idx < rules_n; rule_idx++) {
                    curr_rule = rules[rule_idx];
                    if (curr_rule[0] == num && curr_rule[1] == check_num) {
                        fucked = 1;
                    }
                }
            }

            // check numbers after
            for (int af = i + 1; af < size; af++) {
                check_num = curr_list[af];

                for (int rule_idx = 0; rule_idx < rules_n; rule_idx++) {
                    curr_rule = rules[rule_idx];
                    if (curr_rule[1] == num && curr_rule[0] == check_num) {
                        fucked = 1;
                    }
                }
            }
        }

        if (!fucked) {
            int num_to_sum = curr_list[size / 2];
            printf("OK: %d\n", num_to_sum);
            sum += num_to_sum;
        } else {
            bad_list[bad_list_amount] = curr_list;
            bad_list_n[bad_list_amount] = size;
            bad_list_amount++;
        }
    }

    printf("Part1: %d\n", sum);

    sum = 0;
    for (int test_case = 0; test_case < bad_list_amount; test_case++) {
        curr_list = bad_list[test_case];
        size = bad_list_n[test_case];

        int fixed_list[64];
        fixed_list[0] = curr_list[0];
        int fixed_list_n = 1;

        for (int i = 1; i < size; i++) {
            int num = curr_list[i];

            int lo = 0;
            int hi = fixed_list_n;

            int *curr_rule;
            for (int rule_i = 0; rule_i < rules_n; rule_i++) {
                curr_rule = rules[rule_i];

                // if rule applise to current num update range
                if (curr_rule[0] == num || curr_rule[1] == num) {
                    if (curr_rule[0] == num) {
                        int idx = find(curr_rule[1], fixed_list, fixed_list_n);
                        if (idx != -1) {
                            hi = MIN(hi, idx);
                        }
                    }
                    if (curr_rule[1] == num) {
                        int idx = find(curr_rule[0], fixed_list, fixed_list_n);
                        if (idx != -1) {
                            lo = MAX(lo, idx + 1);
                        }
                    }

                    // if (test_case == 2) {
                    //     printf("==");
                    // }
                }
                // if (test_case == 2) {
                //     printf("num: %d, lo: %d hi: %d, rule: %d %d\n", num, lo,
                //     hi,
                //            curr_rule[0], curr_rule[1]);
                // }

                if (lo == hi) {
                    put_at(lo, num, fixed_list, fixed_list_n);
                    fixed_list_n++;
                    break;
                }
            }

            // if (test_case == 2) {
            //     print_int_array(fixed_list, fixed_list_n);
            // }
        }
        sum += fixed_list[fixed_list_n / 2];
    }

    printf("Part2: %d", sum);

    return 0;
}
