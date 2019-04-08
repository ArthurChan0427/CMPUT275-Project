// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

// Source: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/

#include <memory>
#include <stack>
#include "commandManager.h"
#include "iCommand.h"

using namespace std;

void CommandManager::executeCmd(shared_ptr<ICommand> command) {
    redoStack = commandStack_t(); // clear the redo-command stack
    command->execute(); // execute the command
    undoStack.push(command); // add the command object to the undo-command stack
}

void CommandManager::undo() {
    if (undoStack.size() <= 0) return;
    undoStack.top()->undo(); // undo the most recent command
    redoStack.push(undoStack.top()); // add the command object to the redo-command stack
    undoStack.pop(); // remove the command object from the undo-command stack
}

void CommandManager::redo() {
    if (redoStack.size() <= 0) return;
    redoStack.top()->redo(); // redo the most recent undone command
    undoStack.push(redoStack.top()); // add the command object to the undo-command stack
    redoStack.pop(); // remove the command object from the redo-command stack
}
