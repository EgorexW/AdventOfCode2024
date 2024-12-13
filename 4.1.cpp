#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
int CheckHorizontal(const vector<string> & lines) {
    regex expression("(?=XMAS)|(?=SAMX)");
    int sum = 0;
    for (const auto& line : lines) {
        auto words_begin = sregex_iterator(line.begin(), line.end(), expression);
        auto words_end = sregex_iterator();
        sum += distance(words_begin, words_end);
    }
    return sum;
}

int CheckVertical(const vector<string> & lines) {
    int matches = 0;
    for (int x = 0; x < lines[0].length(); x++) {
        for (int y = 0; y < lines.size() - 3; y++) {
            if (lines[y][x] == 'X' && lines[y+1][x] == 'M' && lines[y+2][x] == 'A' && lines[y+3][x] == 'S') {
                matches++;
            }
            if (lines[y][x] == 'S' && lines[y+1][x] == 'A' && lines[y+2][x] == 'M' && lines[y+3][x] == 'X') {
                matches++;
            }
        }
    }
    return matches;
}

int CheckDiagonalDownRight(const vector<string> & lines) {
    int matches = 0;
    for (int x = 0; x < lines[0].length() - 3; x++) {
        for (int y = 0; y < lines.size() - 3; y++) {
            if (lines[y][x] == 'X' && lines[y+1][x+1] == 'M' && lines[y+2][x+2] == 'A' && lines[y+3][x+3] == 'S') {
                matches++;
            }
            if (lines[y][x] == 'S' && lines[y+1][x+1] == 'A' && lines[y+2][x+2] == 'M' && lines[y+3][x+3] == 'X') {
                matches++;
            }
        }
    }
    return matches;
}

int CheckDiagonalUpRight(const vector<string> & lines) {
    int matches = 0;
    for (int x = 3; x < lines[0].length(); x++) {
        for (int y = 0; y < lines.size() - 3; y++) {
            if (lines[y][x] == 'X' && lines[y+1][x-1] == 'M' && lines[y+2][x-2] == 'A' && lines[y+3][x-3] == 'S') {
                matches++;
            }
            if (lines[y][x] == 'S' && lines[y+1][x-1] == 'A' && lines[y+2][x-2] == 'M' && lines[y+3][x-3] == 'X') {
                matches++;
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

    int sum = 0;
    sum += CheckHorizontal(lines);
    sum += CheckVertical(lines);
    sum += CheckDiagonalDownRight(lines);
    sum += CheckDiagonalUpRight(lines);

    cout << sum;
}
