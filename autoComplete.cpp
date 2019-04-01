#include <memory>
#include <string>
#include <map>
#include "autoComplete.h"
#include "iCommand.h"

using namespace std;

// map<string, unsigned int> words;
// map<string, unsigned int> temp;
words = AutoMap;
temp = AutoMap;

string AutoComplete::search(string s) {
    for(map<string, unsigned int>::iterator iter = words.begin(); iter != words.end(); ++iter) {
        if(iter.rfind(s, 0) == 0) {
            temp[iter->first] = iter->second;
        }
    }

    string max_k;
    int max_v = 0;

    for(map<string, unsigned int>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
        if(iter->second > max_v) {
            max_k = iter->first;
            max_v = iter->second;
        }
    }

    temp.clear();

    return max_k;
}

void AutoComplete::update(string s) {
    iter = words.find(s);
    if(iter == words.end()) {
        words[s] = 1;
    } else {
        iter->second += 1;
    }
}

void AutoComplete::del(string s) {
    iter = words.find(s);
    if(iter != words.end()) {
        if(iter->second == 1) {
            words.erase(iter);
        } else if(iter->second > 1) {
            iter->second -= 1;
        }
    }
}
