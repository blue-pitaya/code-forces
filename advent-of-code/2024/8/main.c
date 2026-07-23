#include <stdbool.h>
#include <stdio.h>

// Point

typedef struct {
    int x, y;
} Point;

// NodePositions

enum {
    NodePositions_MAX_UNIQ_NODE_POSITIONS = 128,
};

typedef struct {
    Point positions[NodePositions_MAX_UNIQ_NODE_POSITIONS];
    int size;
} NodePositions;

void NodePositions_add(NodePositions *n, char id, int x, int y) {
    n->positions[n->size].x = x;
    n->positions[n->size].y = y;
    n->size++;
}

// Map

enum {
    Map_SIZE = 50,
    Map_MAX_NODE_DEFS = 255, // ASCII
};

typedef struct {
    char map[Map_SIZE][Map_SIZE];
    int antinodes[Map_SIZE][Map_SIZE];
    NodePositions nodes[Map_MAX_NODE_DEFS];
} Map;

void Map_load(Map *m) {
    for (int y = 0; y < Map_SIZE; y++) {
        for (int x = 0; x < Map_SIZE; x++) {
            scanf("%c", &m->map[x][y]);
        }
        scanf("\n");
    }
}

void Map_print(Map *m) {
    for (int y = 0; y < Map_SIZE; y++) {
        for (int x = 0; x < Map_SIZE; x++) {
            printf("%c", m->map[x][y]);
        }
        printf("\n");
    }
}

void Map_print_antinodes(Map *m) {
    for (int y = 0; y < Map_SIZE; y++) {
        for (int x = 0; x < Map_SIZE; x++) {
            if (m->antinodes[x][y] > 0) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

void Map_init_nodes(Map *m) {
    for (int y = 0; y < Map_SIZE; y++) {
        for (int x = 0; x < Map_SIZE; x++) {
            char id = m->map[x][y];
            if (id != '.') {
                NodePositions_add(&m->nodes[id], id, x, y);
            }
        }
    }
}

bool Map_is_on_map(Map *m, Point p) {
    if (p.x < 0 || p.y < 0 || p.x >= Map_SIZE || p.y >= Map_SIZE) {
        return false;
    }
    return true;
}

void Map_calculate_antinodes(Map *m) {
    for (int i = 0; i < 255; i++) {
        const int size = m->nodes[i].size;
        if (size == 0) {
            continue;
        }
        Point *positions = m->nodes[i].positions;
        for (int j = 0; j < size; j++) {
            for (int k = j + 1; k < size; k++) {
                Point p1 = positions[j];
                Point p2 = positions[k];

                Point dist1 = {.x = p1.x - p2.x, .y = p1.y - p2.y};
                Point antinode1 = {.x = p1.x + dist1.x, .y = p1.y + dist1.y};
                if (Map_is_on_map(m, antinode1)) {
                    m->antinodes[antinode1.x][antinode1.y]++;
                }

                Point dist2 = {.x = p2.x - p1.x, .y = p2.y - p1.y};
                Point antinode2 = {.x = p2.x + dist2.x, .y = p2.y + dist2.y};
                if (Map_is_on_map(m, antinode2)) {
                    m->antinodes[antinode2.x][antinode2.y]++;
                }
            }
        }
    }
}

void Map_calculate_antinodes2(Map *m) {
    for (int i = 0; i < 255; i++) {
        const int size = m->nodes[i].size;
        if (size == 0) {
            continue;
        }
        Point *positions = m->nodes[i].positions;
        for (int j = 0; j < size; j++) {
            for (int k = j + 1; k < size; k++) {
                Point p1 = positions[j];
                Point p2 = positions[k];

                Point dist1 = {.x = p1.x - p2.x, .y = p1.y - p2.y};
                int mul = 0;
                while (true) {
                    Point antinode = {
                        .x = p1.x + mul * dist1.x,
                        .y = p1.y + mul * dist1.y,
                    };
                    if (Map_is_on_map(m, antinode)) {
                        m->antinodes[antinode.x][antinode.y]++;
                    } else {
                        break;
                    }
                    mul++;
                }

                Point dist2 = {.x = p2.x - p1.x, .y = p2.y - p1.y};
                mul = 0;
                while (true) {
                    Point antinode = {
                        .x = p2.x + mul * dist2.x,
                        .y = p2.y + mul * dist2.y,
                    };
                    if (Map_is_on_map(m, antinode)) {
                        m->antinodes[antinode.x][antinode.y]++;
                    } else {
                        break;
                    }
                    mul++;
                }
            }
        }
    }
}

int Map_count_antinodes(Map *m) {
    int sum = 0;
    for (int y = 0; y < Map_SIZE; y++) {
        for (int x = 0; x < Map_SIZE; x++) {
            if (m->antinodes[x][y] > 0) {
                sum++;
            }
        }
    }

    return sum;
}

// Program

Map map = {
    .map = {{0}},
    .antinodes = {{0}},
    .nodes = {{
        .positions = {{0}},
        .size = 0,
    }},
};

int main(void) {
    // part1
    // Map_load(&map);
    // Map_init_nodes(&map);
    // Map_calculate_antinodes(&map);
    // int res = Map_count_antinodes(&map);

    // part2
    Map_load(&map);
    Map_init_nodes(&map);
    Map_calculate_antinodes2(&map);
    int res = Map_count_antinodes(&map);

    printf("%d\n", res);

    return 0;
}
