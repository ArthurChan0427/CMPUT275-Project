// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

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
