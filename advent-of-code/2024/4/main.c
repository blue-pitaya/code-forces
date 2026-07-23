#include <stdio.h>

#define A 140

char data[A][A];
const char *word = "XMAS";
const int word_size = 4;
int found_blocks = 0;
int found_words = 0;
int found_idx = 0;

void search_xmas(int x, int y) {
    if (word[found_idx] != data[x][y]) {
        found_idx = 0;
    }

    if (word[found_idx] == data[x][y]) {
        found_idx++;
    }

    if (found_idx == word_size) {
        found_words++;
        found_idx = 0;
    }
}

void search_line(int sx, int sy, int dx, int dy) {
    int x = sx;
    int y = sy;
    found_idx = 0;
    while (x >= 0 && x < A && y >= 0 && y < A) {
        search_xmas(x, y);
        x += dx;
        y += dy;
    }
}

void part1() {
    for (int i = 0; i < A; i++) {
        // right
        search_line(0, i, 1, 0);
        // left
        search_line(A - 1, i, -1, 0);
        // down
        search_line(i, 0, 0, 1);
        // up
        search_line(i, A - 1, 0, -1);

        // down-right
        search_line(i, 0, 1, 1);
        search_line(0, i + 1, 1, 1);

        // down-left
        search_line(i, 0, -1, 1);
        search_line(A - 1, i + 1, -1, 1);

        // up-right
        search_line(i, A - 1, 1, -1);
        search_line(0, A - 2 - i, 1, -1);

        // up-left
        search_line(i, A - 1, -1, -1);
        search_line(A - 1, A - 2 - i, -1, -1);
    }

    printf("%d\n", found_words);
}

void part2() {
    for (int x = 0; x < A - 2; x++) {
        for (int y = 0; y < A - 2; y++) {
            if (data[x + 1][y + 1] == 'A') {
                if (data[x][y] == 'M' && data[x + 2][y] == 'M' &&
                    data[x][y + 2] == 'S' && data[x + 2][y + 2] == 'S') {
                    found_blocks++;
                }
                if (data[x][y] == 'M' && data[x + 2][y] == 'S' &&
                    data[x][y + 2] == 'M' && data[x + 2][y + 2] == 'S') {
                    found_blocks++;
                }
                if (data[x][y] == 'S' && data[x + 2][y] == 'S' &&
                    data[x][y + 2] == 'M' && data[x + 2][y + 2] == 'M') {
                    found_blocks++;
                }
                if (data[x][y] == 'S' && data[x + 2][y] == 'M' &&
                    data[x][y + 2] == 'S' && data[x + 2][y + 2] == 'M') {
                    found_blocks++;
                }
            }
        }
    }

    printf("%d\n", found_blocks);
}

int main() {
    char ch;
    int x = 0, y = 0;
    while (scanf("%c", &ch) == 1) {
        if (ch != '\n') {
            data[x][y] = ch;
            x++;
        } else {
            y++;
            x = 0;
        }
    }

    //part1();
    part2();

    return 0;
}
