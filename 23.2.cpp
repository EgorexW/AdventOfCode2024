#include <fstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

map<set<string>, set<string>> processedParties;

set<string> CreateHighiestParty(set<string> party, set<string> possibleAdditions, map<string, set<string>> connections) {
    if (processedParties.contains(party)) {
        return processedParties[party];
    }
    auto highestParty = party;
    if (possibleAdditions.empty()) {
        return highestParty;
    }
    vector<pair<string, set<string>>> computersSorted[possibleAdditions.size()];
    for (const auto& computer : possibleAdditions) {
        auto newPossibleAdditions = possibleAdditions;
        newPossibleAdditions.erase(computer);
        for (const auto& otherComputer : possibleAdditions) {
            if (!connections[computer].contains(otherComputer)) {
                newPossibleAdditions.erase(otherComputer);
            }
        }
        computersSorted[possibleAdditions.size() - newPossibleAdditions.size() - 1].emplace_back(computer, set(newPossibleAdditions)); //[]
    }
    for (const auto& computers : computersSorted) {
        for (const auto& computer: computers) {
            auto newParty = party;
            newParty.insert(computer.first);
            if (newParty.size() + computer.second.size() <= highestParty.size()) {
                break;
            }
            auto foundParty = CreateHighiestParty(newParty, computer.second, connections);
            if (foundParty.size() > highestParty.size()) {
                highestParty = foundParty;
            }
        }
    }
    processedParties[party] = highestParty;
    return highestParty;
}
int main() {
    ifstream in("Input.txt");

    map<string, set<string>> connections;
    string lineTmp;
    while (getline(in, lineTmp)) {
        string a = lineTmp.substr(0, 2);
        string b = lineTmp.substr(3, 2);
        connections[a].insert(b);
        connections[b].insert(a);
    }

    set<string> highestParty;
    for (const auto& computer : connections) {
        auto party = CreateHighiestParty({computer.first}, connections[computer.first], connections);
        if (party.size() > highestParty.size()) {
            highestParty = party;
            cout << "New highest party: ";
            for (const auto& partyMember : highestParty) {
                cout << partyMember << ",";
            }
        } else {
            cout << "No new highest party";
        }
        cout << endl;
    }

    for (const auto& partyMember : highestParty) {
        cout << partyMember << ",";
    }
    cout << endl;
}