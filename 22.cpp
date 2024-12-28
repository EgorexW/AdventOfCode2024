#include <fstream>
#include <iostream>
#include <map>
using namespace std;

const int NrOfBuyers = 1526;
map<array<int, 4>, array<int, NrOfBuyers>> changeSequenceScores;

long long ProcessSecretNr(long long nr, long long result) {
    nr = result ^ nr;
    nr %= 16777216;
    return nr;
}

void CalculateNr(long long nr, int i, int thisIndex) {
    vector<int> changes;
    int prevPrice = nr % 10;
    while (i > 0) {
        nr = ProcessSecretNr(nr, nr * 64);
        nr = ProcessSecretNr(nr, nr / 32);
        nr = ProcessSecretNr(nr, nr * 2048);
        int price = nr % 10;
        changes.push_back(price - prevPrice);
        prevPrice = price;
        if (changes.size() >= 4) {
            map<array<int, 4>, array<int, NrOfBuyers>>::key_type lastChanges = {changes[changes.size()-4], changes[changes.size()-3], changes[changes.size()-2], changes[changes.size()-1]};
            int currentScore = changeSequenceScores[lastChanges][thisIndex];
            if (price > currentScore) {
                changeSequenceScores[lastChanges][thisIndex] = price;
            }
        }
        i --;
    }
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    int i = 0;
    while (getline(in, lineTmp)) {
        CalculateNr(stoi(lineTmp), 2000, i);
        i++;
        cout << i*100/NrOfBuyers << endl;
    }
    cout << endl;
    pair<int, array<int, 4>> maxSum = {0, {0, 0, 0, 0}};
    for (auto score : changeSequenceScores) {
        long long sum = 0;
        for (int i = 0; i < NrOfBuyers; i++) {
            sum += score.second[i];
        }
        if (sum > maxSum.first) {
            maxSum = {sum, score.first};
        }
    }
    cout << maxSum.first << " : ";
    for (int i = 0; i < 4; i++) {
        cout << maxSum.second[i] << ", ";
    }
}
