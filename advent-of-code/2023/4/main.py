import re


def get_same(line):
    nums = line.split(":")[1]
    win_nums_str, my_nums_str = nums.split("|")
    win_nums = re.findall(r"\d+", win_nums_str)
    my_nums = re.findall(r"\d+", my_nums_str)
    return set(win_nums).intersection(set(my_nums))


with open("input.txt", "r") as file:
    lines = file.readlines()

    points = 0
    for line in lines:
        same = get_same(line)
        points += 2 ** (len(same) - 1) if len(same) > 0 else 0
    print(points)

    sum = 0
    copies = [1 for _ in range(len(lines))]
    for i, line in enumerate(lines):
        same = get_same(line)
        sum += copies[i]
        for n in range(copies[i]):
            for x in range(i + 1, i + 1 + len(same)):
                copies[x] += 1
    print(sum)
