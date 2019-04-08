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

/*
search a list of strings for a string that starts with a given substring, defined as all of the
alphabetical characters the user has typed into the editor since the last space or endline. If 
such a string / strings is/are found, find the string with the most typed occurrences and return it
back to the text editor
*/
string AutoComplete::search(string s) {
    // find strings starting with substring s
    for(map<string, unsigned int>::iterator iter = words.begin(); iter != words.end(); ++iter) {
        if((iter->first).rfind(s, 0) == 0) { // if string at iter-> begins with substring s
            temp[iter->first] = iter->second;
        }
    }

    string max_k;
    int max_v = 0;

    // find string containing substring with the most number of occurrences
    for(map<string, unsigned int>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
        // if the string at iter has more occurrences than any string coming before it, then reset the maximum number of occurrences
        if(iter->second > max_v) {
            max_k = iter->first;
            max_v = iter->second;
        }
    }

    // clear the temp map for future uses
    temp.clear();

    // return the string with the most number of occurrences, minus the substring being searched for
    // in other words, return the rest of the recommended word that has yet to be typed into the editor
    // if there are multiple strings with the most number of occurrences, the first such string instance found will be returned
    return max_k.erase(0, s.length());
}

/*
update the map of strings when a word in the text editor is completed (either by a space or an endline).
If a word already exists in the map, increment its frequency by one. If a word does not already exist in
the map, add it to the map with a frequecny of one. Returns nothing
*/
void AutoComplete::update(string s) {
    // initialize the iterator
    map<string, unsigned int>::iterator iter = words.find(s);
    
    // if word is found
    if(iter == words.end()) {
        words[s] = 1; // add word to the map with a frequency of one
    } else {
        // makes it more likely to be recommended
        iter->second += 1; // increment the frequency of the word by one
    }
}

// delete functionality has been removed from this project
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
