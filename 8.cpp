#include <fstream>
#include <iostream>
#include <map>
using namespace std;

int X = 50;
int Y = 50;

int main() {
    ifstream in("Input.txt");

    map<char, vector<pair<int, int>>> antennasTypes;

    string lineTmp;
    int y = 0;
    while (getline(in, lineTmp)) {
        int x = 0;
        for (char a : lineTmp) {
            if (a != '.') {
                antennasTypes[a].emplace_back(x, y);
                // cout << "Antenna type: " << a << ", Position: (" << x << ", " << y << ")" << endl;
            }
            x++;
        }
        y++;
    }

    bool locations[X][Y];
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            locations[i][j] = false;
        }
    }

    for(const auto& antennasType : antennasTypes) {
        auto antennas = antennasType.second;
        for (int i = 0; i < antennas.size(); i++) {
            for (int j = i + 1; j < antennas.size(); j++) {
                auto firstAntenna = antennas[i];
                auto secondAntenna = antennas[j];
                int disX = secondAntenna.first - firstAntenna.first;
                int disY = secondAntenna.second - firstAntenna.second;
                int mult = 0;
                while (true) {
                    int x1 = secondAntenna.first + disX * mult;
                    int y1 = secondAntenna.second + disY * mult;
                    int x2 = firstAntenna.first - disX * mult;
                    int y2 = firstAntenna.second - disY * mult;
                    bool found = false;
                    if (x1 >= 0 && x1 < X && y1 >= 0 && y1 < Y) {
                        found = true;
                        locations[x1][y1] = true;
                    }
                    if (x2 >= 0 && x2 < X && y2 >= 0 && y2 < Y) {
                        found = true;
                        locations[x2][y2] = true;
                    }
                    if (found == false) {
                        break;
                    }
                    mult ++;
                }
            }
        }
    }

    int count = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (locations[x][y]) {
                cout << '#';
                count++;
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    cout << count << endl;
    return 0;
}
