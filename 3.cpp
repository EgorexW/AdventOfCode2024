#include <fstream>
#include <iostream>

using namespace std;

int GetMult(string lineTmp, int i) {
    int j = 0;
    if (lineTmp[i + j] != 'm') {
        return 0;
    }
    j++;
    if (lineTmp[i + j] != 'u') {
        return 0;
    }
    j++;
    if (lineTmp[i + j] != 'l') {
        return 0;
    }
    j++;
    if (lineTmp[i + j] != '(') {
        return 0;
    }
    j++;
    int a = 0;
    while (true) {
        if (!isdigit(lineTmp[i + j])) {
            break;
        }
        a *= 10;
        a += (int)(lineTmp[i + j] - '0');
        j ++;
    }
    if (a == 0) {
        return 0;
    }
    if (lineTmp[i + j] != ',') {
        return 0;
    }
    j++;
    int b = 0;
    while (true) {
        if (!isdigit(lineTmp[i + j])) {
            break;
        }
        b *= 10;
        b += (int)(lineTmp[i + j] - '0');
        j ++;
    }
    if (b == 0) {
        return 0;
    }
    if (lineTmp[i + j] != ')') {
        return 0;
    }
    return a * b;
}

bool GetEnabled(string lineTmp, int i, bool enabled) {
    int j = 0;
    if (lineTmp[i + j] != 'd') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] != 'o') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] == '(') {
        j++;
        if (lineTmp[i + j] != ')') {
            return enabled;
        }
        return true;
    }
    if (lineTmp[i + j] != 'n') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] != '\'') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] != 't') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] != '(') {
        return enabled;
    }
    j++;
    if (lineTmp[i + j] != ')') {
        return enabled;
    }
    return false;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;

    int sum = 0;
    bool enabled = true;

    while (getline(in, lineTmp)) {
        for (int i = 0; i < lineTmp.size(); i++) {
            enabled = GetEnabled(lineTmp, i, enabled);
            if (!enabled) {
                continue;
            }
            sum += GetMult(lineTmp, i);
        }
    }
    cout << sum;
}
