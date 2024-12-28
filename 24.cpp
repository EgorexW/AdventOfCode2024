#include <fstream>
#include <iostream>
#include <map>
#include <unordered_set>
using namespace std;

enum Condition {
    AND,
    OR,
    XOR
};
struct Rule {
    explicit Rule(const string & lineTmp) {
        in1 = lineTmp.substr(0, 3);
        int nextIndex = 8;
        if (lineTmp.substr(4, 2) == "OR") {
            condition = Condition::OR;
            nextIndex = 7;
        } else if (lineTmp.substr(4, 3) == "AND") {
            condition = Condition::AND;
        } else {
            condition = Condition::XOR;
        }
        in2 = lineTmp.substr(nextIndex, 3);
        out = lineTmp.substr(nextIndex + 7, 3);
    }

    string in1;
    string in2;
    string out;
    Condition condition;
};

string GetBinValue(char var, map<string, bool> variables) {
    string valueInBin;
    for (const auto& [key, value] : variables) {
        if (key[0] != var) {
            continue;
        }
        valueInBin += to_string(value);
    }
    reverse(valueInBin.begin(), valueInBin.end());
    return valueInBin;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    map<string, bool> variables;
    while (getline(in, lineTmp)) {
        if (lineTmp == "") {
            break;
        }
        variables[lineTmp.substr(0, 3)] = lineTmp[5] - '0';
    }

    vector<Rule> rules;
    while (getline(in, lineTmp)) {
        rules.push_back(Rule(lineTmp));
    }

    while (!rules.empty()) {
        for (int i = rules.size() - 1; i >= 0; i--) {
            const auto& rule = rules[i];
            bool value = false;
            if (!variables.contains(rule.in1) || !variables.contains(rule.in2)) {
                continue;
            }
            if (rule.condition == Condition::AND) {
                value = variables[rule.in1] && variables[rule.in2];
            } else if (rule.condition == Condition::OR) {
                value = variables[rule.in1] || variables[rule.in2];
            } else {
                value = variables[rule.in1] ^ variables[rule.in2];
            }
            variables[rule.out] = value;
            rules.erase(rules.begin() + i);
        }
    }

    string zValueInBin = GetBinValue('z', variables);
    string xValueInBin = GetBinValue('x', variables);
    string yValueInBin = GetBinValue('y', variables);
    long long desiredZValue = stoll(xValueInBin, 0, 2) + stoll(yValueInBin, 0, 2);
    string desiredZValueInBin = bitset<6>(desiredZValue).to_string();

    cout << "X value: " << xValueInBin << endl;
    cout << "Y value: " << yValueInBin << endl;
    cout << "Desired Z value in bin: " << desiredZValueInBin << endl;
    cout << "Actual  Z value in bin: " << zValueInBin << endl;
}
