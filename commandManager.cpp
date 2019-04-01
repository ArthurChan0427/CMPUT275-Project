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
