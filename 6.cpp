#include <fstream>
#include <iostream>
#include <set>
using namespace std;

int Size = 15;
int X = Size;
int Y = Size;

void Rotate(pair<int, int> &guardsDir) {
    if (guardsDir.first != 0) {
        guardsDir.second = guardsDir.first;
        guardsDir.first = 0;
    } else {
        guardsDir.first = -guardsDir.second;
        guardsDir.second = 0;
    }
}

int main() {
    int map[X][Y];
    ifstream in("Input.txt");
    string lineTmp;
    pair<int, int> guardsPos;
    int y = 0;
    while (getline(in, lineTmp)) {
        int x = 0;
        for (char a : lineTmp) {
            if (a == '#') {
                map[x][y] = 1;
            }
            else if(a == '^') {
                guardsPos.first = x;
                guardsPos.second = y;
                map[x][y] = -1;
            } else {
                map[x][y] = 0;
            }
            x++;
        }
        y++;
    }

    pair<int, int> guardsDir;
    guardsDir.first = 0;
    guardsDir.second = -1;

    int loops = 0;

    while (true) {
        int newX = guardsPos.first + guardsDir.first;
        int newY = guardsPos.second + guardsDir.second;
        if (newX >= X || newX < 0 || newY >= Y || newY < 0) {
            break;
        }
        if (map[newX][newY] != 1) {
            if (map[newX][newY] == 0) {
                auto tmpPos = guardsPos;
                auto tmpDir = guardsDir;

                set<pair<pair<int, int>, pair<int, int>>> visited;
                visited.insert(make_pair(tmpPos, tmpDir));

                map[newX][newY] = 1;

                while (true) {
                    int newXTmp = tmpPos.first + tmpDir.first;
                    int newYTmp = tmpPos.second + tmpDir.second;
                    if (newXTmp >= X || newXTmp < 0 || newYTmp >= Y || newYTmp < 0) {
                        break;
                    }
                    if (map[newXTmp][newYTmp] != 1) {
                        tmpPos.first = newXTmp;
                        tmpPos.second = newYTmp;
                    } else {
                        Rotate(tmpDir);
                    }

                    auto state = std::make_pair(tmpPos, tmpDir);
                    if (visited.contains(state)) {
                        loops++;
                        break;
                    }
                    visited.insert(state);
                }
            }
            map[newX][newY] = -1;
            guardsPos.first = newX;
            guardsPos.second = newY;
            continue;
        }
        Rotate(guardsDir);
    }

    cout << loops;
}
