#include <fstream>
#include <iostream>
#include <map>
#include <valarray>
using namespace std;

int X = 101;
int Y = 103;
int moves = 10000000;

struct Robot {
    int posX;
    int posY;
    int vX;
    int vY;
};

void MoveRobot(Robot &robot) {
    robot.posX += robot.vX;
    robot.posY += robot.vY;
    while (robot.posX < 0) {
        robot.posX += X;
    }
    while (robot.posY < 0) {
        robot.posY += Y;
    }
    robot.posX = robot.posX % X;
    robot.posY = robot.posY % Y;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    vector<Robot> robots;

    while (getline(in, lineTmp)) {
        int comma = lineTmp.find_first_of(',');
        int posX = stoi(lineTmp.substr(2, comma-2));
        int space = lineTmp.find_first_of(' ');
        int posY = stoi(lineTmp.substr(comma + 1, space - comma - 1));
        comma = lineTmp.find_last_of(',');
        int vX = stoi(lineTmp.substr(space + 3, comma - 2 - space));
        int vY = stoi(lineTmp.substr(comma + 1, lineTmp.size() - comma - 1));
        robots.push_back(Robot(posX, posY, vX, vY));
    }

    for (int i = 0; i < moves; i++) {
        for (auto robot : robots) {
            MoveRobot(robot);
        }
        map<pair<int, int>, int> positions;
        for (const auto &robot : robots) {
            positions[{robot.posX, robot.posY}]++;
        }

        int maxXCount = 0, maxYCount = 0;
        map<int, int> xCounts, yCounts;

        for (const auto &robot : robots) {
            xCounts[robot.posX]++;
            yCounts[robot.posY]++;
        }

        for (const auto &xCount : xCounts) {
            maxXCount = max(maxXCount, xCount.second);
        }

        for (const auto &yCount : yCounts) {
            maxYCount = max(maxYCount, yCount.second);
        }

        if (maxXCount < robots.size() / 2 || maxYCount < robots.size() / 2) {
            continue;
        }
        cout << "Move: " << (i+1) << endl;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                bool found = false;
                for (const auto &robot : robots) {
                    if (robot.posX == x && robot.posY == y) {
                        cout << '#';
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << '.';
                }
            }
            cout << endl;
        }
    }
}
