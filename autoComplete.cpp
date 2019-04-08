// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

#include <memory>
#include <string>
#include <map>
#include "autoComplete.h"
#include "iCommand.h"

using namespace std;

map<string, unsigned int> words;
map<string, unsigned int> temp;
// words = AutoMap();
// temp = AutoMap();

string AutoComplete::search(string s) {
    // find strings starting with substring s
    for(map<string, unsigned int>::iterator iter = words.begin(); iter != words.end(); ++iter) {
        if((iter->first).rfind(s, 0) == 0) {
            temp[iter->first] = iter->second;
        }
    }

    string max_k;
    int max_v = 0;

    // find string containing substring with the most number of occurrences
    for(map<string, unsigned int>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
        if(iter->second > max_v) {
            max_k = iter->first;
            max_v = iter->second;
        }
    }

    temp.clear();

    return max_k.erase(0, s.length());
}

void AutoComplete::update(string s) {
    map<string, unsigned int>::iterator iter = words.find(s);
    if(iter == words.end()) {
        words[s] = 1;
    } else {
        iter->second += 1;
    }
}

// void AutoComplete::del(string s) {
//     map<string, unsigned int>::iterator iter = words.find(s);
//     if(iter != words.end()) {
//         if(iter->second == 1) {
//             words.erase(iter);
//         } else if(iter->second > 1) {
//             iter->second -= 1;
//         }
//     }
// }
