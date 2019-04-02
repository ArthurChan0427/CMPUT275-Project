#ifndef AUTO_COMPLETE_H
#define AUTO_COMPLETE_H

#include <memory>
#include <string>
#include <map>
#include "iCommand.h"

using namespace std;

typedef map<string, unsigned int> autoMap;

class AutoComplete {
    private:
        autoMap words;
        autoMap temp;

    public:
        string search(string s);

        void update(string s);

        // void del(string s);
};

#endif
