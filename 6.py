import sys
from collections import defaultdict

X = 10
Y = 10

def rotate(guards_dir):
    if guards_dir[0] != 0:
        guards_dir[1] = guards_dir[0]
        guards_dir[0] = 0
    else:
        guards_dir[0] = -guards_dir[1]
        guards_dir[1] = 0

def main():
    grid = [[False for _ in range(Y)] for _ in range(X)]

    with open("Input.txt", "r") as f:
        lines = f.readlines()

    guards_pos = None
    y = 0
    for line in lines:
        x = 0
        for char in line.strip():
            if char == '#':
                grid[x][y] = True
            elif char == '^':
                guards_pos = [x, y]
            else:
                grid[x][y] = False
            x += 1
        y += 1

    guards_dir = [0, -1]
    loops = 0

    while True:
        new_x = guards_pos[0] + guards_dir[0]
        new_y = guards_pos[1] + guards_dir[1]

        if new_x >= X or new_x < 0 or new_y >= Y or new_y < 0:
            break

        if not grid[new_x][new_y]:
            guards_pos[0] = new_x
            guards_pos[1] = new_y
        else:
            tmp_pos = guards_pos[:]
            tmp_dir = guards_dir[:]

            visited = set()
            visited.add((tuple(tmp_pos), tuple(tmp_dir)))

            while True:
                rotate(tmp_dir)
                new_x_tmp = tmp_pos[0] + tmp_dir[0]
                new_y_tmp = tmp_pos[1] + tmp_dir[1]

                if new_x_tmp >= X or new_x_tmp < 0 or new_y_tmp >= Y or new_y_tmp < 0:
                    break

                if not grid[new_x_tmp][new_y_tmp]:
                    tmp_pos[0] = new_x_tmp
                    tmp_pos[1] = new_y_tmp
                else:
                    rotate(tmp_dir)

                state = (tuple(tmp_pos), tuple(tmp_dir))
                if state in visited:
                    loops += 1
                    break

                visited.add(state)

            rotate(guards_dir)
            continue

        rotate(guards_dir)

    print(loops)

if __name__ == "__main__":
    main()