#include <fstream>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

const int Count = 10000;

void ResolveRock(pair<long long, long long> rock, map<long long, long long>& newRocks) {
    if (rock.first == 0) {
        rock.first = 1;
        newRocks[rock.first] += rock.second;
        return;
    }
    long long digitsNr = (int)ceil(log10(rock.first + 1));
    if (digitsNr % 2 != 0) {
        rock.first *= 2024;
        newRocks[rock.first] += rock.second;
        return;
    }
    long long pow1 = 1;
    for (int i = 0; i < digitsNr / 2; ++i) {
        pow1 *= 10;
    }
    long long newRock1 = floor(rock.first / pow1);
    long long newRock2 = rock.first - (newRock1 * pow1);

    newRocks[newRock1] += rock.second;
    newRocks[newRock2] += rock.second;
}

int main() {
    ifstream in("Input.txt");

    map<long long, map<int, int>> rocksFromNr;
    map<long long, long long> rocks;
    string line;
    getline(in, line);

    int nrTmp = 0;
    for (auto digit : line) {
        if (digit == ' ') {
            rocks[nrTmp] = 1;
            nrTmp = 0;
            continue;
        }
        nrTmp *= 10;
        nrTmp += digit - '0';
    }
    rocks[nrTmp] = 1;

    for (int i = 0; i < Count; i++) {
        map<long long, long long> newRocks;
        for (auto rock : rocks) {
           ResolveRock(rock, newRocks);
        }
        rocks = newRocks;
    }

    long long sum;

    for (auto rock : rocks) {
        sum += rock.second;
    }

    cout << "Rocks: " << sum;
}
