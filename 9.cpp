#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream in("Input.txt");
    string line;
    getline(in, line);

    vector<pair<long long, int>> processedLine;

    bool file = true;
    long long fileIndex = 0;
    for (char a : line) {
        long long nr = a - '0';
        long long insert = file ? fileIndex : -1;
        processedLine.emplace_back(insert, nr);
        if (file) {
            fileIndex ++;
        }
        file = !file;
    }

    // for (auto file : processedLine) {
    //     for (int i = 0; i < file.second; i++) {
    //         if (file.first == -1) {
    //             cout << ".";
    //         } else {
    //             cout << file.first;
    //         }
    //     }
    // }
    // cout << endl;

    for (int i = processedLine.size() - 1; i >= 0; i--) {
        auto firstFile = processedLine[i];
        if (firstFile.first == -1) {
            continue;
        }
        for (int j = 0; j < i; j++) {
            auto secondFile = processedLine[j];
            if (secondFile.first != -1) {
                continue;
            }
            if (secondFile.second < firstFile.second) {
                continue;
            }
            processedLine[j].second -= firstFile.second;
            processedLine[i].first = -1;
            processedLine.insert(processedLine.begin() + j, firstFile);

            // for (auto file : processedLine) {
            //     for (int i = 0; i < file.second; i++) {
            //         if (file.first == -1) {
            //             cout << ".";
            //         } else {
            //             cout << file.first;
            //         }
            //     }
            // }
            // cout << endl;
            break;
        }
    }

    long long sum = 0;
    int i = 0;
    for (auto file : processedLine) {
        int j = i + file.second;
        if (file.first == -1) {
            i = j;
            continue;
        }
        while (i < j) {
            sum += i * file.first;
            i++;
        }
    }
    cout << sum;
}