#include <fstream>
#include <iostream>
#include <set>
using namespace std;

const pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int Size = 70;
pair<int, int> endPos = {Size, Size};

bool CheckForPath(set<pair<int, int>> blockedPos) {
    set<pair<int, int>> posToProcess = {{0, 0}};
    int startBlockedPos = blockedPos.size();
    bool found = false;
    for (int i = 1; i <= Size * Size - startBlockedPos; i++) {
        set<pair<int, int>> futurePosToProcess;
        for (auto pos : posToProcess) {
            for (auto dir : dirs) {
                pair<int, int> newPos = {pos.first + dir.first, pos.second + dir.second};
                if (newPos.first < 0 || newPos.first > Size || newPos.second < 0 || newPos.second > Size) {
                    continue;
                }
                if (blockedPos.contains(newPos)) {
                    continue;
                }
                if (newPos == endPos) {
                    found = true;
                    break;
                }
                futurePosToProcess.insert(newPos);
            }
            if (found) {
                break;
            }
            blockedPos.insert(pos);
        }
        if (found) {
            break;
        }
        posToProcess = futurePosToProcess;
    }
    return found;
}

int main() {
    ifstream in("Input.txt");

    vector<pair<int, int>> allBlockedPos;

    string lineTmp;
    while (getline(in, lineTmp)) {
        int comma = lineTmp.find_first_of(',');
        int x = stoi(lineTmp.substr(0, comma));
        int y = stoi(lineTmp.substr(comma + 1, lineTmp.length() - comma - 1));
        allBlockedPos.emplace_back(x, y);
    }


    int max = allBlockedPos.size() - 1;
    int min = 0;
    int i = max / 2;

    while(true) {
        set<pair<int, int>> blockedPos(allBlockedPos.begin(), allBlockedPos.begin() + i + 1);
        bool found = CheckForPath(blockedPos);
        if (found) {
            blockedPos.insert(allBlockedPos[i + 1]);
            bool nextFound = CheckForPath(blockedPos);
            if (!nextFound) {
                cout << allBlockedPos[i+1].first << "," << allBlockedPos[i+1].second;
                break;
            }
            min = i + 1;
        } else {
            max = i - 1;
        }
        i = (max - min)/2 + min;
    }
}
