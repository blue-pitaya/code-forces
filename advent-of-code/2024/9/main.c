#include <stdbool.h>
#include <stdio.h>

#define LLU unsigned long long

enum {
    INPUT_SIZE = 20000,
    MAX_EXPAND_SPACE_OF_SINGLE_BLOCK = 10,
    MAX_DISK_SIZE = INPUT_SIZE * MAX_EXPAND_SPACE_OF_SINGLE_BLOCK,
    GAP = -1,
};

typedef struct {
    int start;
    int size;
} File;

File files[INPUT_SIZE];
int files_amount = 0;
int disk[MAX_DISK_SIZE] = {GAP};
int disk_size = 0;

void input_disk() {
    unsigned char input_digit;
    int input_num;

    bool is_filling_file = true;
    int disk_idx = 0;
    while (scanf("%c", &input_digit) != EOF) {
        if (input_digit < 48 || input_digit > 57) {
            continue;
        }
        input_num = input_digit - '0';

        if (is_filling_file) {
            files[files_amount].start = disk_idx;
            files[files_amount].size = input_num;
            for (int i = 0; i < input_num; i++) {
                disk[disk_idx] = files_amount;
                disk_idx++;
            }
            files_amount++;
        } else {
            for (int i = 0; i < input_num; i++) {
                disk[disk_idx] = GAP;
                disk_idx++;
            }
        }

        is_filling_file = !is_filling_file;
    }

    disk_size = disk_idx;
}

void part1() {
    int file_grab_idx = disk_size - 1;
    int placing_idx = 0;
    while (placing_idx <= file_grab_idx) {
        if (disk[file_grab_idx] == GAP) {
            file_grab_idx--;
            continue;
        }

        int block_file_id = disk[file_grab_idx];
        while (disk[placing_idx] != GAP) {
            placing_idx++;
        }
        if (!(placing_idx <= file_grab_idx)) {
            break;
        }
        disk[file_grab_idx] = GAP;
        disk[placing_idx] = block_file_id;
        file_grab_idx--;
    }
}

void part2() {
    for (int file_id = files_amount - 1; file_id >= 0; file_id--) {
        int gap_start = 0;
        int gap_size = 0;
        bool found = false;
        for (int i = 0; i < files[file_id].start; i++) {
            if (disk[i] == GAP) {
                gap_size++;
            } else {
                if (gap_size >= files[file_id].size) {
                    for (int j = 0; j < files[file_id].size; j++) {
                        disk[gap_start + j] = file_id;
                        disk[files[file_id].start + j] = GAP;
                    }
                    found = true;
                    break;
                } else {
                    gap_start = i + 1;
                    gap_size = 0;
                }
            }
        }
        if (!found && (gap_size >= files[file_id].size)) {
            for (int j = 0; j < files[file_id].size; j++) {
                disk[gap_start + j] = file_id;
                disk[files[file_id].start + j] = GAP;
            }
        }
    }
}

LLU checksum() {
    LLU res = 0;
    for (int i = 0; i <= disk_size; i++) {
        if (disk[i] != GAP) {
            int file_id = disk[i];
            res += (LLU)i * (LLU)file_id;
        }
    }
    return res;
}

int main(void) {
    input_disk();
    // part1();
    part2();
    printf("%llu\n", checksum());

    return 0;
}
