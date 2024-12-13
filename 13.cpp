#include <fstream>
#include <iostream>

using namespace std;

struct Game {
    int aX;
    int aY;
    int bX;
    int bY;
    long long goalX;
    long long goalY;
};

long long ResolveGame(const Game & game) {
    long long b = (game.goalY*game.aX-game.goalX*game.aY)/(game.bY*game.aX-game.bX*game.aY);
    long long a = (game.goalX-b*game.bX)/game.aX;
    if (game.aX*a + game.bX*b != game.goalX) {
        return 0;
    }
    if (game.aY*a + game.bY*b != game.goalY) {
        return 0;
    }
    return a*3 + b;
}

int main() {
    ifstream in("Input.txt");

    long long sum = 0;

    string lineTmp;
    while (getline(in, lineTmp)) {
        auto newGame = Game();
        newGame.aX = stoi(lineTmp.substr(12, 2));
        newGame.aY = stoi(lineTmp.substr(18, 2));
        getline(in, lineTmp);
        newGame.bX = stoi(lineTmp.substr(12, 2));
        newGame.bY = stoi(lineTmp.substr(18, 2));
        getline(in, lineTmp);
        auto comma = lineTmp.find_first_of(',');
        newGame.goalX = stoi(lineTmp.substr(9, comma - 9)) + 10000000000000;
        newGame.goalY = stoi(lineTmp.substr(comma + 4, lineTmp.size() - comma - 4)) + 10000000000000;
        cout << "Game details: aX=" << newGame.aX << ", aY=" << newGame.aY
            << ", bX=" << newGame.bX << ", bY=" << newGame.bY
            << ", goalX=" << newGame.goalX << ", goalY=" << newGame.goalY << endl;
        long long score = ResolveGame(newGame);
        cout << "Score: " << score << endl;
        sum += score;
        getline(in, lineTmp);
    }

    cout << sum;
}
