#include <fstream>
#include <iostream>

using namespace std;

bool TrySum(unsigned long long int goal, const vector<unsigned long long int> & numbers, unsigned long long int currentSum, int i) {
    if (i == numbers.size()) {
        if (currentSum == goal) {
            return true;
        }
        return false;
    }
    if (TrySum(goal, numbers, currentSum + numbers[i], i + 1)) {
        return true;
    }
    unsigned long long int digitsCount = ceil(log10(numbers[i]+1));
    unsigned long long int mult = pow(10, digitsCount);
    unsigned long long int newSum = currentSum * mult + numbers[i];
    if (TrySum(goal, numbers, newSum, i + 1)) {
        return true;
    }
    return TrySum(goal, numbers, currentSum * numbers[i], i + 1);
}

unsigned long long int Evaluate(const string & line) {
    unsigned long long int number = 0;
    unsigned long long int goal = 0;
    vector<unsigned long long int> numbers;
    for (int i = 0; i <= line.size(); i++) {
        char a = line[i];
        if (isdigit(a)) {
            number *= 10;
            number += a - '0';
            continue;
        }
        if (a == ':') {
            goal = number;
            i++;
        } else {
            numbers.push_back(number);
        }
        number = 0;
    }
    if (TrySum(goal, numbers, numbers[0], 1)) {
        return goal;
    }
    cout << line << endl;
    return 0;
}

int main() {
    ifstream in("Input.txt");
    string lineTmp;
    unsigned long long int sum = 0;
    while (getline(in, lineTmp)) {
        sum += Evaluate(lineTmp);
    }
    cout << sum;
}
