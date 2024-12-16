#include <fstream>
#include <map>
using namespace std;

const int Size = 15;
const int X = Size;
const int Y = Size;
const pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct PathfindingNode {
    bool passable;
    map<pair<int, int>, int> scoreFromDir;
    int x;
    int y;

    PathfindingNode(bool passable, int x, int y);
};

int main() {
    ifstream in("Input.txt");

    PathfindingNode map[X][Y];
    pair<int, int> startPos;
    pair<int, int> endPos;

    int y = 0;
    string lineTmp;
    while (y < Y) {
        getline(in, lineTmp);
        int x = 0;
        for (char a : lineTmp) {
            if (a == '#') {
                map[x][y] = PathfindingNode(false, x, y);
            } else {
                map[x][y] = PathfindingNode(true, x, y);
                if (a == 'E') {
                    endPos = {x, y};
                }
                if (a == 'S') {
                    startPos = {x, y};
                }
            }
            x++;
        }
        y++;
    }

    queue<PathfindingNode> queue;
    for (auto dir : dirs) {
        PathfindingNode node = map[endPos.first + dir.first][endPos.second + dir.second];
        node.scoreFromDir[{-dir.first, -dir.second}] = 1;
        queue.push(node);
    }
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        if (!node.passable) {
            continue;
        }
        for (auto dir : dirs) {
            PathfindingNode targetNode = map[node.x + dir.first][node.y + dir.second];

        }
    }
}