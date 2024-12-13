#include <fstream>
#include <iostream>
#include <map>
#include <set>

using namespace std;

const int X = 140;
const int Y = 140;
const pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int EvaluatePlot(int x, int y, char a, char plot[X][Y]){
    queue<pair<int, int>> queue;
    set<pair<int, int>> resolvedPos;
    map<int, set<pair<int, int>>> sidesX;
    map<int, set<pair<int, int>>> sidesY;
    queue.emplace(x, y);
    while (!queue.empty()) {
        auto pos = queue.front();
        queue.pop();
        if (resolvedPos.contains(pos)) {
            continue;
        }
        resolvedPos.insert(pos);
        for (auto dir : dirs) {
            pair<int, int> newPos = {pos.first + dir.first, pos.second + dir.second};
            if (newPos.first >= 0 && newPos.first < X && newPos.second >= 0 && newPos.second < Y) {
                if (resolvedPos.contains(newPos)) {
                    continue;
                }
                if (plot[newPos.first][newPos.second] == a) {
                    queue.emplace(newPos);
                    continue;
                }
            }
            if (dir.first != 0) {
                int modX = dir.first == -1 ? -1 : 0;
                sidesX[pos.first + modX].insert({pos.second, dir.first});
            } else {
                int modY = dir.second == -1 ? -1 : 0;
                sidesY[pos.second + modY].insert({pos.first, dir.second});
            }
        }
    }
    for (auto pos : resolvedPos) {
        plot[pos.first][pos.second] = '.';
    }
    int perimeter = 0;
    for (auto line : sidesX) {
        pair<int, int> prevSide = {-3, 0};
        for (auto side : line.second) {
            if (prevSide.first + 1 != side.first) {
                perimeter++;
            } else if (prevSide.second != side.second) {
                perimeter++;
            }
            prevSide = side;
        }
    }
    for (auto line : sidesY) {
        pair<int, int> prevSide = {-3, 0};
        for (auto side : line.second) {
            if (prevSide.first + 1 != side.first) {
                perimeter++;
            } else if (prevSide.second != side.second) {
                perimeter++;
            }
            prevSide = side;
        }
    }
    int sum = perimeter * resolvedPos.size();
    cout << "Type: " << a << " - " << sum << " = " << resolvedPos.size() << " * " << perimeter << "\n";
    return sum;
}

int main() {
    ifstream in("Input.txt");

    char map[X][Y];

    int y = 0;
    string lineTmp;
    while (getline(in, lineTmp)) {
        int x = 0;
        for (char a : lineTmp) {
            map[x][y] = a;
            x++;
        }
        y++;
    }

    int sum;
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            char a = map[x][y];
            if (a == '.') {
                continue;
            }
            int plot = EvaluatePlot(x, y, a, map);
            sum += plot;
        }
    }
    cout << sum;
}
