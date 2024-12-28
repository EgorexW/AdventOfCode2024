#include <fstream>
#include <iostream>
using namespace std;

vector<pair<int, int>> CreateCodeInstructions(const string & code) {
    pair<int, int> currentPos;
    vector<pair<int, int>> instructions;
    for (int i = 0; i < code.length(); i++) {
        auto targetPos = GetNrPos(code[i]);
        pair<int, int> moveVector = {targetPos.first - currentPos.first, targetPos.second - currentPos.second};
        instructions.push_back(moveVector);
        currentPos = targetPos;
    }
    return instructions;
}

int Evaluate(const string & code) {
    auto movements1 = CreateCodeInstructions(code);
    auto movements2 = CreateMoveInstructions(movements1);
    auto movements3 = CreateMoveInstructions(movements2);
    auto movementsLength = CalculateLength(movements3);
    return movementsLength * stoi(code.substr(0, code.length() - 1));
}

int main(){
    ifstream in("Input.txt");

    string lineTmp;
    int sum = 0;
    while (getline(in, lineTmp)) {
        sum += Evaluate(lineTmp);
    }
    cout << sum;
}
