#include <fstream>
#include <iostream>
using namespace std;

const int Size = 141;
const int X = Size;
const int Y = Size;
const pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    ifstream in("Input.txt");

    int map[X][Y];
    pair<int, int> startPos;
    pair<int, int> endPos;

    int y = 0;
    string lineTmp;
    while (y < Y) {
        getline(in, lineTmp);
        int x = 0;
        for (char a : lineTmp) {
            if (a == 'S') {
                startPos.first = x;
                startPos.second = y;
            }
            if (a == 'E') {
                endPos.first = x;
                endPos.second = y;
            }
            map[x][y] = a == '#' ? -1 : 0;
            x++;
        }
        y++;
    }

    auto currentPos = startPos;
    int baseTime = 0;
    vector<pair<int, int>> path;

    while (true) {
        map[currentPos.first][currentPos.second] = baseTime;
        path.push_back(currentPos);
        if (currentPos == endPos) {
            break;
        }
        for (auto dir : dirs) {
            pair<int, int> newPos = {currentPos.first + dir.first, currentPos.second + dir.second};
            if (newPos.first < 0 || newPos.first >= Size || newPos.second < 0 || newPos.second >= Size) {
                continue;
            }
            if (newPos == startPos) {
                continue;
            }
            if (map[newPos.first][newPos.second] == 0) {
                baseTime ++;
                currentPos = newPos;
                break;
            }
        }
    }

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            cout << setw(2) << map[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int MinTimeSave = 100;
    int cheatLenght = 20;

    int cheatsNr = 0;

    for (auto node : path) {
        auto nodeCost = map[node.first][node.second];
        for (int x = -cheatLenght; x <= cheatLenght; x++) {
            for (int y = -(cheatLenght - abs(x)); y <= cheatLenght - abs(x); y++) {
                pair<int, int> newPos = {node.first + x, node.second + y};
                if (newPos.first < 0 || newPos.first >= Size || newPos.second < 0 || newPos.second >= Size) {
                    continue;
                }
                if (map[newPos.first][newPos.second] == -1) {
                    continue;
                }
                int timeSave = map[newPos.first][newPos.second] - nodeCost - (abs(x) + abs(y));
                if (timeSave >= MinTimeSave) {
                    cout << "Cheating from " << node.first << "," << node.second << " to " << newPos.first << "," << newPos.second << " saves " << timeSave << " time steps" << endl;
                    cheatsNr ++;
                }
            }
        }
    }

    cout << cheatsNr << endl;
}