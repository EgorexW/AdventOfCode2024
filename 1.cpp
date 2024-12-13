#include <iostream>
#include <map>
#include <set>
#include <valarray>

using namespace std;

int main()
{
    int tmp1, tmp2;
    vector<int> list1;
    pmr::map<int, int> list2;

    while (true) {
        cin >> tmp1;
        if (tmp1 < 0) {
            break;
        }
        cin >> tmp2;
        list1.push_back(tmp1);
        list2[tmp2] ++;
    }

    int sum = 0;

    auto iterator1 = list1.begin();

    while (true) {
        sum += *iterator1 * list2[*iterator1];
        ++iterator1;
        if (iterator1 == list1.end()) {
            break;
        }
    }

    cout << sum;
}
