#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char bool;

bool enabled = TRUE;
int state = 0, num1_size = 0, num2_size = 0;
char num1[16];
char num2[16];
int a, b, sum = 0;
int curr_search_idx = 0;

int scan_state = 0; // if in progress of scanning for "mul" or "don't"

void clear_state() {
    state = 0;
    num1_size = 0;
    num2_size = 0;
    curr_search_idx = 0;
    scan_state = 0;
}

void scan_for_mul(char ch) {
    switch (state) {
    case 0:
        if (ch == 'm') {
            state++;
        } else {
            clear_state();
        }
        break;
    case 1:
        if (ch == 'u') {
            state++;
        } else {
            clear_state();
        }
        break;
    case 2:
        if (ch == 'l') {
            state++;
        } else {
            clear_state();
        }
        break;
    case 3:
        if (ch == '(') {
            state++;
        } else {
            clear_state();
        }
        break;
    case 4:
        if (ch >= '0' && ch <= '9') {
            num1[num1_size] = ch;
            num1_size++;
        } else if (ch == ',') {
            state++;
        } else {
            clear_state();
        }
        break;
    case 5:
        if (ch >= '0' && ch <= '9') {
            num2[num2_size] = ch;
            num2_size++;
        } else if (ch == ')') {
            num1[num1_size] = 0;
            num2[num2_size] = 0;
            a = atoi(num1);
            b = atoi(num2);
            sum += a * b;
            clear_state();
        } else {
            clear_state();
        }
        break;
    }
}

void scan_for_do(char ch) {
    const char *str = "do()";
    if (ch == str[curr_search_idx]) {
        curr_search_idx++;
    } else {
        clear_state();
    }

    if (curr_search_idx >= 4) {
        enabled = TRUE;
        clear_state();
    }
}

void scan_for_dont(char ch) {
    const char *str = "don't()";
    if (ch == str[curr_search_idx]) {
        curr_search_idx++;
    } else {
        clear_state();
    }

    if (curr_search_idx >= 7) {
        enabled = FALSE;
        clear_state();
    }
}

void part1() {
    char ch;
    while (scanf("%c", &ch) == 1) {
        scan_for_mul(ch);
    }

    printf("%d\n", sum);
}

void part2() {
    char ch;

    while (scanf("%c", &ch) == 1) {
        if (enabled) {
            // no "mul" or "don't" scanning
            if (scan_state == 0) {
                if (ch == 'm') {
                    scan_state = 1;
                }
                if (ch == 'd') {
                    scan_state = 2;
                }
            }

            if (scan_state == 1) {
                scan_for_mul(ch);
            }
            if (scan_state == 2) {
                scan_for_dont(ch);
            }
        } else {
            scan_for_do(ch);
        }
    }

    printf("%d\n", sum);
}

int main() {
    //part1();
    part2();

    return 0;
}
