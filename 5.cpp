#include <fstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

bool CheckLine(const vector<int> & numbers, map<int, vector<int>> & rules) {
    set<int> numbersEncountered;
    for (int nr : numbers) {
        for (int rule : rules[nr]) {
            if (numbersEncountered.contains(rule)) {
                return false;
            }
        }
        numbersEncountered.insert(nr);
    }
    return true;
}

vector<int> GetNumbers(const string &line) {
    vector<int> numbers;
    for (int x = 0; x < line.size() - 1; x += 3) {
        int nr = stoi(line.substr(x, 2));
        numbers.push_back(nr);
    }
    return numbers;
}

int FindSolution(const vector<int> & numbers, map<int, vector<int>> & rules) {
    int size = numbers.size();
    map<int, int> positions;
    for (int number : numbers) {
        positions[number] = 0;
    }
    for (int number : numbers) {
        for (int rule : rules[number]) {
            if (positions.contains(rule)) {
                positions[rule] ++;
            }
        }
    }
    int middle = (size - 1)/2;
    for (int number : numbers) {
        if (positions[number] == middle) {
            return number;
        }
    }
    return 0;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    map<int, vector<int>> rules;
    while (getline(in, lineTmp)) {
        if (lineTmp == "") {
            break;
        }
        int x1 = stoi(lineTmp.substr(0, 2));
        int x2 = stoi(lineTmp.substr(3, 2));
        rules[x1].push_back(x2);
    }

    int sum = 0;
    while (getline(in, lineTmp)) {
        auto numbers = GetNumbers(lineTmp);
        if (CheckLine(numbers, rules)) {
            continue;
        }
        sum += FindSolution(numbers, rules);
    }
    cout << sum;
}
