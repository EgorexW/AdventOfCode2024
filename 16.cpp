#include <fstream>
#include <string>
#include <utility>
using namespace std;

int Size = 15;
int X = Size;
int Y = Size;

int main() {
    char map[X][Y];
    ifstream in("Input.txt");
    string lineTmp;

    pair<int, int> startPos;
    pair<int, int> endPos;

    int y = 0;
    while (getline(in, lineTmp)) {
        int x = 0;
        for (char a : lineTmp) {
            if (a == 'S') {
                startPos.first = x;
                startPos.second = y;
                map[x][y] = '.';
            }
            else if (a == 'E') {
                endPos.first = x;
                endPos.second = y;
                map[x][y] = '.';
            }
            else {
                map[x][y] = a;
            }
            x++;
        }
        y++;
    }


}