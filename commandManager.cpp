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
    redoStack = commandStack_t();
    command->execute();
    undoStack.push(command);
}

void CommandManager::undo() {
    if (undoStack.size() <= 0) return;
    undoStack.top()->undo();
    redoStack.push(undoStack.top());
    undoStack.pop();
}

void CommandManager::redo() {
    if (redoStack.size() <= 0) return;
    redoStack.top()->redo();
    undoStack.push(redoStack.top());
    redoStack.pop();
}
