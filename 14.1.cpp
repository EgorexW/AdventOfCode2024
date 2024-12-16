#include <fstream>
#include <iostream>
#include <map>
#include <valarray>
using namespace std;

int X = 101;
int Y = 103;
int moves = 100;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

pair<int, int> ResolveRobot(int posX, int posY, int vX, int vY) {
    cout << "Resolving robot at (" << posX << ", " << posY << ") with velocity (" << vX << ", " << vY << ")" << endl;
    posX += vX * moves;
    posY += vY * moves;
    cout << "After " << moves << " moves, robot is at (" << posX << ", " << posY << ")" << endl;
    while (posX < 0) {
        posX += X;
    }
    while (posY < 0) {
        posY += Y;
    }
    posX = posX % X;
    posY = posY % Y;
    cout << "After correction robot is at (" << posX << ", " << posY << ")" << endl;
    posX -= (X+1)/2 - 1;
    posY -= (Y+1)/2 - 1;
    cout << "After quadrant cal robot is at (" << posX << ", " << posY << ")" << endl;
    pair<int, int> quadrant = {sgn(posX), sgn(posY)};
    cout << "Quadrant is (" << quadrant.first << ", " << quadrant.second << ")" << endl;
    return quadrant;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    map<pair<int, int>, int> quadrants;
    while (getline(in, lineTmp)) {
        int comma = lineTmp.find_first_of(',');
        int posX = stoi(lineTmp.substr(2, comma-2));
        int space = lineTmp.find_first_of(' ');
        int posY = stoi(lineTmp.substr(comma + 1, space - comma - 1));
        comma = lineTmp.find_last_of(',');
        int vX = stoi(lineTmp.substr(space + 3, comma - 2 - space));
        int vY = stoi(lineTmp.substr(comma + 1, lineTmp.size() - comma - 1));
        auto quardant = ResolveRobot(posX, posY, vX, vY);
        if (quardant.first == 0 || quardant.second == 0) {
            continue;
        }
        quadrants[quardant] ++;
    }

    int sum = 1;
    for (auto quadrant : quadrants) {
        cout << "Quadrant " << quadrant.first.first << ", " << quadrant.first.second << " has " << quadrant.second << " robots." << endl;
        sum *= quadrant.second;
    }
    cout << sum;
}
