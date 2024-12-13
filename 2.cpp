#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <valarray>

using namespace std;

bool TryNrs(bool growing, int lastNr, int currentNr) {
    int diff = currentNr - lastNr;
    if (diff == 0) {
        return false;
    }
    bool higher = diff > 0;
    if (growing != higher) {
        return false;
    }
    if (abs(diff) > 3) {
        return false;
    }
    return true;
}

bool TryBasic(vector<int> numbers, int ignore) {
    int start = 0;
    if (ignore == 0) {
        start = 1;
    }
    bool growing = numbers[numbers.size() - 1] - numbers[start] > 0;
    for (int i = start + 1; i < numbers.size(); i++) {
        if (i == ignore) {
            continue;
        }
        int last_nr = numbers[i-1];
        if (i - 1 == ignore) {
            last_nr = numbers[i-2];
        }
        if (TryNrs(growing, last_nr, numbers[i])) {
            continue;
        }
        return false;
    }
    return true;
}



bool CheckLine(vector<int> numbers, string line) {
    for (int i = 0; i < numbers.size(); i++) {
        if (TryBasic(numbers, i)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    vector<string> lines;
    while (getline(in, lineTmp)) {
        lines.push_back(lineTmp);
    }

    int correctLines = 0;

    for (const string& line : lines) {

        istringstream myStream(line);
        istream_iterator<int> begin(myStream), eof;
        vector numbers(begin, eof);

        if (CheckLine(numbers, line)) {
            cout << "\033[32m" << line << " is correct" << "\033[0m" << endl;
            correctLines++;
        } else {
            cout << "\033[31m" << line << " is incorrect" << "\033[0m" << endl;
        }
    }

    cout << correctLines;
}
