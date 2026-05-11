#include <stdio.h>

#define MAX_W 1000
#define MAX_H 1000

int w, h, size;
char map[MAX_W * MAX_H];
int start, finish;

int steps[MAX_W * MAX_H];
int queue[MAX_W * MAX_H];
char path[MAX_W * MAX_H];

void load_map() {
    scanf("%d%d", &h, &w);
    size = w * h;
    for (int i = 0; i < size; i++) {
        steps[i] = -1;
        scanf(" %c", &map[i]);
        if (map[i] == 'A') {
            start = i;
            steps[i] = 0;
        } else if (map[i] == 'B') {
            finish = i;
        }
    }
}

int get_position(int x, int y) {
    if (!(x >= 0 && x < w)) {
        return -1;
    }
    if (!(y >= 0 && y < h)) {
        return -1;
    }

    return y * w + x;
}

int solve_steps() {
    int current_position, next_pos;
    int res = -1;
    int q_start = 0;
    int q_end = 0;
    queue[q_end++] = start;
    while (q_start != q_end) {
        current_position = queue[q_start++];
        if (current_position == finish) {
            return steps[current_position];
        }

        int x = current_position % w;
        int y = current_position / w;
        int next_positions[] = {
            get_position(x, y - 1),
            get_position(x, y + 1),
            get_position(x - 1, y),
            get_position(x + 1, y),
        };
        for (int i = 0; i < 4; i++) {
            next_pos = next_positions[i];
            if (next_pos == -1) {
                continue;
            }
            if (steps[next_pos] == -1 && map[next_pos] != '#') {
                steps[next_pos] = steps[current_position] + 1;
                queue[q_end++] = next_pos;
            }
        }
    }

    return -1;
}

void solve_path(int found_steps) {
    char directions[] = {'D', 'U', 'R', 'L'};
    int current_position = finish;
    int next_pos;
    int idx = found_steps;
    while (current_position != start) {
        int x = current_position % w;
        int y = current_position / w;
        int next_positions[] = {
            get_position(x, y - 1),
            get_position(x, y + 1),
            get_position(x - 1, y),
            get_position(x + 1, y),
        };
        for (int i = 0; i < 4; i++) {
            next_pos = next_positions[i];
            if (next_pos == -1) {
                continue;
            }

            if (steps[next_pos] != -1 &&
                steps[next_pos] < steps[current_position]) {
                current_position = next_pos;
                path[--idx] = directions[i];
                break;
            }
        }
    }
}

int main() {
    load_map();
    int found = solve_steps();
    if (found == -1) {
        printf("NO\n");

        return 0;
    }

    printf("YES\n%d\n", found);
    solve_path(found);
    for (int i = 0; i < found; i++) {
        printf("%c", path[i]);
    }
    printf("\n");

    return 0;
}
