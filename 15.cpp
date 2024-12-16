#include <fstream>
#include <iostream>
#include <set>

using namespace std;

const int Size = 50;
const int X = Size * 2;
const int Y = Size;

pair<int, int> TranslateCommand(char command) {
    switch (command) {
        case '^':
            return {0, -1};
        case '>':
            return {1, 0};
        case '<':
            return {-1, 0};
        case 'v':
            return {0, 1};
        default:
            cerr << "Error: Invalid command '" << command << "'" << endl;
            return {0, 0};
    }
}

void ResolveCommand(char command, char map[X][Y], pair<int, int> &robotPos) {
    auto vectorCommand = TranslateCommand(command);
    set currentPoses = {robotPos};
    stack<pair<int, int>> processedPos;
    processedPos.push(robotPos);
    bool canMove = true;
    while (canMove) {
        if (currentPoses.empty()) {
            break;
        }
        auto tmpPoses = currentPoses;
        for (auto currentPos : tmpPoses) {
            pair<int, int> targetPos = {currentPos.first + vectorCommand.first, currentPos.second + vectorCommand.second};
            auto targetObject = map[targetPos.first][targetPos.second];
            cout << "Checking target position: (" << targetPos.first << ", " << targetPos.second << ") with object '" << targetObject << "'" << endl;
            currentPoses.erase(currentPos);
            if (targetObject == '.') {
                break;
            }
            if (targetObject == '#') {
                canMove = false;
                break;
            }
            processedPos.push(targetPos);
            currentPoses.insert(targetPos);
            if (vectorCommand.second != 0) {
                if (targetObject == '[') {
                    pair<int, int> otherPart = {targetPos.first + 1, targetPos.second};
                    currentPoses.insert(otherPart);
                    processedPos.push(otherPart);
                } else {
                    pair<int, int> otherPart = {targetPos.first - 1, targetPos.second};
                    currentPoses.insert(otherPart);
                    processedPos.push(otherPart);
                }
            }
        }
    }
    if (!canMove) {
        cout << "Can't move" << endl;
        return;
    }
    cout << "Moving" << endl;
    set<pair<int, int>> previousPoses;
    while (!processedPos.empty()) {
        auto currentPos = processedPos.top();
        processedPos.pop();
        pair<int, int> targetPos = {currentPos.first + vectorCommand.first, currentPos.second + vectorCommand.second};
        map[targetPos.first][targetPos.second] = map[currentPos.first][currentPos.second];
        if (currentPos == robotPos) {
            robotPos = targetPos;
        }
        previousPoses.insert(currentPos);
        previousPoses.erase(targetPos);
    }
    for (auto prevPos : previousPoses) {
        map[prevPos.first][prevPos.second] = '.';
    }
}

void ResolveCommands(const string & commands, char map[X][Y], pair<int, int> &robotPos) {
    for (char command : commands) {
        cout << "Move " << command << ":" << endl;
        ResolveCommand(command, map, robotPos);
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                cout << map[x][y];
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    ifstream in("Input.txt");

    char map[X][Y];
    pair<int, int> robotPos;

    int y = 0;
    string lineTmp;
    while (y < Y) {
        getline(in, lineTmp);
        int x = 0;
        for (char a : lineTmp) {
            if (a == 'O') {
                map[x][y] = '[';
            } else {
                map[x][y] = a;
            }
            x++;
            if (a == '@') {
                robotPos.first = x-1;
                robotPos.second = y;
                map[x][y] = '.';
            } else if (a == 'O') {
                map[x][y] = ']';
            } else {
                map[x][y] = a;
            }
            x++;
        }
        y++;
    }

    cout << "Init: " << endl;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            cout << map[x][y];
        }
        cout << endl;
    }
    cout << endl;

    getline(in, lineTmp);
    while (getline(in, lineTmp)) {
        ResolveCommands(lineTmp, map, robotPos);
    }

    int sum = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (map[x][y] != '[') {
                continue;
            }
            sum += 100 * y + x;
        }
    }
    cout << "Sum: " << sum;
}
