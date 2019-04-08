// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

// Source: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <memory>
#include <stack>
#include "iCommand.h"

using namespace std;

typedef stack<shared_ptr<ICommand>> commandStack_t;

class CommandManager {
    private:
        // executed command objects are stored in undoStack and redoStack
        commandStack_t undoStack;
        commandStack_t redoStack;

    public:
        void executeCmd(shared_ptr<ICommand> command);

        void undo();

        void redo();
};

#endif
