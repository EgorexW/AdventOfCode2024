#include <fstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
    ifstream in("Input.txt");

    map<string, set<string>> connections;
    string lineTmp;
    while (getline(in, lineTmp)) {
        string a = lineTmp.substr(0, 2);
        string b = lineTmp.substr(3, 2);
        connections[a].insert(b);
        connections[b].insert(a);
    }

    set<tuple<string, string, string>> threes;
    for (const auto& first : connections) {
        for (const auto& second : first.second) {
            if (second < first.first) {
                continue;
            }
            for (const auto& third : connections[second]){
                if (third < second) {
                    continue;
                }
                if (!first.second.contains(third)) {
                    continue;
                }
                threes.insert({first.first, second, third});
            }
        }
    }

    int sum = 0;
    for (const auto& tuple : threes) {
        if (get<0>(tuple)[0] == 't' || get<1>(tuple)[0] == 't' || get<2>(tuple)[0] == 't') {
            sum ++;
            cout << get<0>(tuple) << ", " << get<1>(tuple) << ", " << get<2>(tuple) << endl;
        }
    }
    cout << sum << endl;
}