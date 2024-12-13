#include <fstream>
#include <iostream>
#include <set>
using namespace std;

int X = 40;
int Y = 40;

int main(){
    ifstream in("Input.txt");

    int map[X][Y];
    string lineTmp;
    int y = 0;
    while (getline(in, lineTmp)) {
        int x = 0;
        for (char a : lineTmp) {
            map[x][y] = a - '0';
            x++;
        }
        y++;
    }

    int sum = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (map[x][y] == 0) {
                queue<pair<int, int>> posToCheck;
                posToCheck.emplace(x, y);
                while (!posToCheck.empty()) {
                    auto pos = posToCheck.front();
                    posToCheck.pop();
                    int value = map[pos.first][pos.second];
                    value++;
                    auto checkedPos = make_pair(pos.first + 1, pos.second);
                    if (checkedPos.first < 0 || checkedPos.first >= X || checkedPos.second < 0 || checkedPos.second >= Y) {

                    }
                    else if (map[checkedPos.first][checkedPos.second] == value) {
                        if (value == 9) {
                            sum++;
                        } else {
                            posToCheck.push(checkedPos);
                        }
                    }
                    checkedPos = make_pair(pos.first - 1, pos.second);
                    if (checkedPos.first < 0 || checkedPos.first >= X || checkedPos.second < 0 || checkedPos.second >= Y) {

                    }
                    else if (map[checkedPos.first][checkedPos.second] == value) {
                        if (value == 9) {
                            sum++;
                        } else {
                            posToCheck.push(checkedPos);
                        }
                    }
                    checkedPos = make_pair(pos.first, pos.second + 1);
                    if (checkedPos.first < 0 || checkedPos.first >= X || checkedPos.second < 0 || checkedPos.second >= Y) {

                    }
                    else if (map[checkedPos.first][checkedPos.second] == value) {
                        if (value == 9) {
                            sum++;
                        } else {
                            posToCheck.push(checkedPos);
                        }
                    }
                    checkedPos = make_pair(pos.first, pos.second - 1);
                    if (checkedPos.first < 0 || checkedPos.first >= X || checkedPos.second < 0 || checkedPos.second >= Y) {

                    }
                    else if (map[checkedPos.first][checkedPos.second] == value) {
                        if (value == 9) {
                            sum++;
                        } else {
                            posToCheck.push(checkedPos);
                        }
                    }
                }
            }
        }
    }
    cout << sum;
}
