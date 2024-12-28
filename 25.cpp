#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    vector<array<string, 7>> inputs;
    array<string, 7> newInput;
    int i = 0;
    while (getline(in, lineTmp)) {
        if (i == 7) {
            inputs.push_back(newInput);
            i = 0;
            continue;
        }
        newInput[i] = lineTmp;
        i++;
    }
    inputs.push_back(newInput);

    vector<array<int, 5>> locks;
    vector<array<int, 5>> keys;
    for (int i = 0; i < inputs.size(); i++) {
        array<int, 5> thisObj;
        if (inputs[i][0] == "#####") {
            for (int x = 0; x < 5; x++) {
                for (int y = 0; y < 7; y++) {
                    if (inputs[i][y][x] == '#') {
                        thisObj[x] = y+1;
                    }
                }
            }
            locks.push_back(thisObj);
        } else {
            for (int x = 0; x < 5; x++) {
                for (int y = 0; y < 7; y++) {
                    if (inputs[i][7-y][x] == '#') {
                        thisObj[x] = y;
                    }
                }
            }
            keys.push_back(thisObj);
        }
    }

    int matches = 0;
    for (int i = 0; i < locks.size(); i++) {
        for (int j = 0; j < keys.size(); j++) {
            if (i == 0) {
                for (int x = 0; x < 5; x++) {
                    cout << keys[j][x] << " ";
                }
                cout <<endl;
            }
            bool match = true;
            for (int x = 0; x < 5; x++) {
                if (locks[i][x] + keys[j][x] > 7) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches++;
            }
        }
        if (i == 0)
            cout << "----" << endl;
        for (int x = 0; x < 5; x++) {
            cout << locks[i][x] << " ";
        }
        cout <<endl;
    }

    cout << matches;
}