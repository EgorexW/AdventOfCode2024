#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

int CountXMASes(const vector<string> & lines) {
    int matches = 0;
    for (int x = 1; x < lines[0].length() - 1; x++) {
        for (int y = 1; y < lines.size() - 1; y++) {
            if (lines[y][x] != 'A') {
                continue;
            }

            char leftUp = lines[y-1][x-1];
            char rightDown = lines[y+1][x+1];
            char leftDown = lines[y+1][x-1];
            char rightUp = lines[y-1][x+1];

            if (((leftUp == 'M' && rightDown == 'S') ||
                (leftUp == 'S' && rightDown == 'M')) &&
                ((leftDown == 'M' && rightUp == 'S') ||
                (leftDown == 'S' && rightUp == 'M'))) {
                matches ++;
            }
        }
    }
    return matches;
}

int main() {
    ifstream in("Input.txt");

    vector<string> lines;
    string lineTmp;
    while (getline(in, lineTmp)) {
        lines.push_back(lineTmp);
    }

    int sum = CountXMASes(lines);

    cout << sum;
}
