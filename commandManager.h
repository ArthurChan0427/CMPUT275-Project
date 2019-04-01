#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <memory>
#include <stack>
#include "iCommand.h"

using namespace std;

typedef stack<shared_ptr<ICommand>> commandStack_t;

class CommandManager {
    private:
        commandStack_t undoStack;
        commandStack_t redoStack;

    public:
        void executeCmd(shared_ptr<ICommand> command);

        void undo();

        void redo();
};

#endif