#include <stdbool.h>
#include <stdio.h>

#define LLU unsigned long long

#ifndef MAP_W
#define MAP_W 52
#endif

#ifndef MAP_H
#define MAP_H 52
#endif

enum {
    MAX_QUEUE_SIZE = MAP_W * MAP_H,
};

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point queue[MAP_H * MAP_W];
    int start;
    int end;
} Queue;

int map[MAP_W][MAP_H];

void load() {
    char curr;
    int x = 0, y = 0;
    while (scanf("%c", &curr) != EOF) {
        if (curr == '\n') {
            y++;
            x = 0;
        }
        if (curr >= '0' && curr <= '9') {
            map[x][y] = curr - '0';
            x++;
        }
    }
}

void print() {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            printf("%d", map[x][y]);
        }
        printf("\n");
    }
}

void queue_clear(Queue *q) {
    q->start = 0;
    q->end = 0;
}

void queue_push(Queue *q, Point p) {
    q->queue[q->end].x = p.x;
    q->queue[q->end].y = p.y;
    q->end++;
}

int queue_pull(Queue *q, Point *res) {
    if (q->start >= q->end) {
        return -1;
    }

    res->x = q->queue[q->start].x;
    res->y = q->queue[q->start].y;
    q->start++;

    return 0;
}

int run(Queue *q) {
    int bfs[MAP_W][MAP_H];
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            bfs[x][y] = -1;
        }
    }

    Point p;
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        if (queue_pull(q, &p) == -1) {
            break;
        };
        int num = map[p.x][p.y];
        bfs[p.x][p.y] = num;
        if (num >= 9) {
            printf("Found: (%d,%d)\n", p.x, p.y);
            continue;
        }

        int x = p.x - 1;
        int y = p.y;
        if (x >= 0 && map[x][y] == (num + 1) && bfs[x][y] == -1) {
            Point p = {.x = x, .y = y};
            queue_push(q, p);
        }
        x = p.x + 1;
        y = p.y;
        if (x < MAP_W && map[x][y] == (num + 1) && bfs[x][y] == -1) {
            Point p = {.x = x, .y = y};
            queue_push(q, p);
        }
        x = p.x;
        y = p.y - 1;
        if (y >= 0 && map[x][y] == (num + 1) && bfs[x][y] == -1) {
            Point p = {.x = x, .y = y};
            queue_push(q, p);
        }

        x = p.x;
        y = p.y + 1;
        if (y < MAP_H && map[x][y] == (num + 1) && bfs[x][y] == -1) {
            Point p = {.x = x, .y = y};
            queue_push(q, p);
        }
    }

    int sum = 0;
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (bfs[x][y] == 9) {
                sum++;
            }
        }
    }

    printf("===\n");
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (bfs[x][y] >= 0) {
                printf("%d", bfs[x][y]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("===\n");

    return sum;
}

Queue queue;

void part1() {
    int sum = 0;
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (map[x][y] == 0) {
                queue_clear(&queue);
                Point p = {.x = x, .y = y};
                queue_push(&queue, p);
                int curr = run(&queue);
                printf("%d\n", curr);
                sum += curr;
            }
        }
    }

    printf("%d\n", sum);
}

int main(void) {
    load();
    // print();
    part1();

    return 0;
}
