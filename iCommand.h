// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

// Source: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/

#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <string>

using namespace std;

#define KILO_TAB_STOP 8

// variable of type erow contains all data associated with a row of text
typedef struct erow {
    int size;
    int rsize;
    char *chars;
    char *render;
} erow;

// editorConfig contains all editor states which are modified by user inputs
struct editorConfig {
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    int dirty;
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct termios orig_termios;
};

// General input command object
class ICommand {
    public:
        ICommand(editorConfig* e);
        
        // Each specific command objects will have their own
        // implementation to execute, undo, and redo procedures.
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
        // virtual string search() = 0;
        // virtual void update() = 0;
        // virtual void del() = 0;

    protected:
        editorConfig* E; // E is the single shared instance of the struct EditorConfig
        int cx, cy; // Each command object need to remember the cursor's position before executing the corresponding procedures.

        // methods adapted from the base code
        void editorUpdateRow(erow *row);

        void editorInsertRow(int at, char *s, size_t len);
};

class BackSpaceCommand : public ICommand {
    public:
        BackSpaceCommand(editorConfig* e);

        void execute();

        void undo();

        void redo();

        // string search();

        // void update();

        // void del();

    private:
        char del_char = '\0';

        // methods adapted from the base code
        void editorFreeRow(erow *row);

        void editorDelRow(int at);

        void editorRowDelChar(erow *row, int at);

        void editorRowAppendString(erow *row, char *s, size_t len);

        void editorDelChar();
};


class InsertCharacterCommand : public ICommand {
    public:
        InsertCharacterCommand(editorConfig* e, int input_char);

        void execute();

        void undo();

        void redo();

        // string search();

        // void update();

        // void del();

    private:
        int c;

       // methods adapted from the base code
        void editorRowInsertChar(erow *row, int at, int c);

        void editorInsertChar(int c);
};


class InsertNewLineCommand : public ICommand {
    public:
        InsertNewLineCommand(editorConfig* e);

        void execute();

        void undo();

        void redo();

        // string search();

        // void update();

        // void del();

    private:
        // method adapted from the base code
        void editorInsertNewline();
};

#endif
