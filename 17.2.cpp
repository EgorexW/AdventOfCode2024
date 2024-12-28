#include <fstream>
#include <iostream>
using namespace std;

int A;
int B;
int C;

vector<int> outputs;

int ComboOperand(int operand) {
    switch (operand) {
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        default:
            return operand;
    }
}

int DIV(int operand) {
    operand = ComboOperand(operand);
    return A;
}

void BitXOR(int operand) {
    B = B ^ operand;
}

int ResolveInstruction(int instruction, int operand, int i) {
    switch (instruction) {
        case 0:
            A = DIV(operand);
            break;
        case 1:
            BitXOR(operand);
            break;
        case 2:
            B = ComboOperand(operand) % 8;
            break;
        case 3:
            if (A != 0) {
                return operand;
            }
            break;
        case 4:
            BitXOR(C);
            break;
        case 5:
            outputs.push_back(ComboOperand(operand) % 8);
            break;
        case 6:
            B = DIV(operand);
            break;
        case 7:
            C = DIV(operand);
            break;
        default:
            cerr << "Unknown instruction: " << instruction << endl;
    }
    return i + 2;
}

int main() {
    ifstream in("Input.txt");

    string lineTmp;
    getline(in, lineTmp);
    getline(in, lineTmp);
    int initB = stoi(lineTmp.substr(12, lineTmp.length() - 12));
    getline(in, lineTmp);
    int initC = stoi(lineTmp.substr(12, lineTmp.length() - 12));
    getline(in, lineTmp);
    getline(in, lineTmp);
    string program = lineTmp.substr(9, lineTmp.length() - 9);

    vector<int> instructions;
    for (char a : program) {
        if (a == ',') {
            continue;
        }
        instructions.push_back(a - '0');
    }

    for (int i = 0; i < instructions.size();) {
        i = ResolveInstruction(instructions[i], instructions[i+1], i);
    }
}
