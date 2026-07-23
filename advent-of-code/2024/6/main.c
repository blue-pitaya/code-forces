#include <stdio.h>

#define MAX_LINE 200
#define SIDE 130

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

char maze[SIDE][SIDE];
int guard_x = 0;
int guard_y = 0;
int direction = TOP;

int is_obstacke_at(int x, int y) {
    if (x < 0 || x >= SIDE || y < 0 || y >= SIDE) {
        return 0;
    }

    return maze[x][y] == '#';
}

void move() {
    if (direction == TOP) {
        guard_y--;
    }
    if (direction == BOTTOM) {
        guard_y++;
    }
    if (direction == LEFT) {
        guard_x--;
    }
    if (direction == RIGHT) {
        guard_x++;
    }
}

void check_for_obstacle() {
    if (direction == TOP) {
        if (is_obstacke_at(guard_x, guard_y - 1)) {
            direction++;
        }
    } else if (direction == BOTTOM) {
        if (is_obstacke_at(guard_x, guard_y + 1)) {
            direction++;
        }
    } else if (direction == LEFT) {
        if (is_obstacke_at(guard_x - 1, guard_y)) {
            direction++;
        }
    } else if (direction == RIGHT) {
        if (is_obstacke_at(guard_x + 1, guard_y)) {
            direction++;
        }
    }

    direction = direction % 4;
}

int main() {
    char line[MAX_LINE];

    int row = 0;
    while (fgets(line, MAX_LINE, stdin)) {
        int i = 0;
        char *iter = line;
        while (*iter && *iter != '\n') {
            if (*iter != '.' && *iter != '#') {
                guard_x = i;
                guard_y = row;
            }

            maze[i][row] = *iter;
            iter++;
            i++;
        }
        row++;
    }

    int step = 0;
    while (guard_x >= 0 && guard_x < SIDE && guard_y >= 0 && guard_y < SIDE) {
        maze[guard_x][guard_y] = 'X';
        check_for_obstacle();
        move();

        step++;
    }

    for (int y = 0; y < SIDE; y++) {
        for (int x = 0; x < SIDE; x++) {
            printf("%c", maze[x][y]);
        }
        printf("\n");
    }

    int sum = 0;
    for (int y = 0; y < SIDE; y++) {
        for (int x = 0; x < SIDE; x++) {
            if (maze[x][y] == 'X') {
                sum++;
            }
        }
    }

    printf("Part1: %d\n", sum);


}
