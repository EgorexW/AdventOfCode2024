#include <fstream>
#include <iostream>
using namespace std;

long long ResolvePattern(string patternLeft, const vector<string> & towels, vector<string> insertedTowels, long long indexesVisited[100]) {
    if (patternLeft.empty()) {
        return 1;
    }
    if (indexesVisited[patternLeft.length()] != -1) {
        return indexesVisited[patternLeft.length()];
    }
    long long sum = 0;
    for (int i = 0; i < towels.size(); i++) {
        if (towels[i] == patternLeft.substr(0, towels[i].length())) {
            insertedTowels.push_back(towels[i]);
            sum += ResolvePattern(patternLeft.substr(towels[i].length(), patternLeft.length() - towels[i].length()), towels, insertedTowels, indexesVisited);
        }
    }
    indexesVisited[patternLeft.length()] = sum;
    return sum;
}

int main() {
    ifstream in("Input.txt");

    vector<string> towels;

    string lineTmp;
    getline(in, lineTmp);

    string towel;
    for (char a : lineTmp) {
        if (a == ',') {
            towels.push_back(towel);
            towel = "";
            continue;
        }
        if (a == ' ') {
            continue;
        }
        towel += a;
    }
    towels.push_back(towel);

    getline(in, lineTmp);

    long long sum = 0;
    while (getline(in, lineTmp)) {
        long long indexes[lineTmp.length()];
        for (int i = 0; i < lineTmp.length() + 1; i++) {
            indexes[i] = -1;
        }
        long long result = ResolvePattern(lineTmp, towels, {}, indexes);
        sum += result;
        cout << result << " : " << lineTmp << endl;
    }

    cout << sum;
}
