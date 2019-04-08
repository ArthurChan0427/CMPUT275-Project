// ------------------------------------------------------------------------------------
//    Name:  Ryan Jacques         / Arthur Chan
//    ID:    1523211              / 1425382
//    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
//    CMPUT 275, Winter 2019
//
//    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
// ------------------------------------------------------------------------------------

// Source: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/

#include "iCommand.h"

using namespace std;

// Below contains the implementation of all command object methods.
// All implementations except those for the execute, undo, and redo methods are adapted from the base code.

ICommand::ICommand(editorConfig* e) {
    this->E = e;
}

void ICommand::editorUpdateRow(erow *row) {
    int tabs = 0;
    for (int j = 0; j < row->size; j++) 
        if (row->chars[j] == '\t') tabs++;

    free(row->render);
    row->render = (char*) malloc(row->size + tabs*(KILO_TAB_STOP - 1) + 1);

    int idx = 0;
    for (int j = 0; j < row->size; j++) {
        if (row->chars[j] == '\t') {
            row->render[idx++] = ' ';
            while (idx % KILO_TAB_STOP != 0) row->render[idx++] = ' ';
        } else {
            row->render[idx++] = row->chars[j];
        }
    }
    row->render[idx] = '\0';
    row->rsize = idx;
}

void ICommand::editorInsertRow(int at, char *s, size_t len) {
    if (at < 0 || at > E->numrows) return;

    E->row = (erow*) realloc(E->row, sizeof(erow) * (E->numrows + 1));
    memmove(&E->row[at + 1], &E->row[at], sizeof(erow) * (E->numrows - at));

    E->row[at].size = len;
    E->row[at].chars = (char*) malloc(len + 1);
    memcpy(E->row[at].chars, s, len);
    E->row[at].chars[len] = '\0';

    E->row[at].rsize = 0;
    E->row[at].render = NULL;
    editorUpdateRow(&E->row[at]);

    E->numrows++;
    E->dirty++;
}

BackSpaceCommand::BackSpaceCommand(editorConfig* e) : ICommand(e) {}

void BackSpaceCommand::execute() {
    editorDelChar(); // delete a character or an empty line
    this->cx = E->cx; // remember the cursor's location immediately after the executing the command
    this->cy = E->cy;
}

void BackSpaceCommand::undo() {
    E->cx = this->cx; // restore the cursor's location that were remembered
    E->cy = this->cy;
    if (del_char == '\0') {
        // If an empty line was deleted, insert a new line
        InsertNewLineCommand insertNewLineCommand(E);
        insertNewLineCommand.execute();
    } else {
        // otherwise, insert the character that was deleted
        InsertCharacterCommand insertCharacterCommand(E, del_char);
        insertCharacterCommand.execute();
    }
    this->cx = E->cx; // again, remember the cursor's location immediately after executing the command
    this->cy = E->cy;
}

void BackSpaceCommand::redo() {
    E->cx = this->cx;
    E->cy = this->cy;
    execute();
}

void BackSpaceCommand::editorFreeRow(erow *row) {
    free(row->render);
    free(row->chars);
}

void BackSpaceCommand::editorDelRow(int at) {
    if (at < 0 || at >= E->numrows) return;
    editorFreeRow(&E->row[at]);
    memmove(&E->row[at], &E->row[at + 1], sizeof(erow) * (E->numrows - at - 1));
    E->numrows--;
    E->dirty++;
}

void BackSpaceCommand::editorRowDelChar(erow *row, int at) {
    if (at < 0 || at >= row->size) return;
    
    memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
    row->size--;
    editorUpdateRow(row);
    E->dirty++;
}

void BackSpaceCommand::editorRowAppendString(erow *row, char *s, size_t len) {
    row->chars = (char*) realloc(row->chars, row->size + len + 1);
    memcpy(&row->chars[row->size], s, len);
    row->size += len;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
    E->dirty++;
}

void BackSpaceCommand::editorDelChar() {
    if (E->cy == E->numrows) return;
    if (E->cx == 0 && E->cy == 0) return;

    erow *row = &E->row[E->cy];
    if (E->cx > 0) {
        this->del_char = row->chars[E->cx - 1];
        editorRowDelChar(row, E->cx - 1);
        E->cx--;
    } else {
        E->cx = E->row[E->cy - 1].size;
        editorRowAppendString(&E->row[E->cy - 1], row->chars, row->size);
        editorDelRow(E->cy);
        E->cy--;
    }
}

InsertCharacterCommand::InsertCharacterCommand(editorConfig* e, int input_char) : ICommand(e) {
    this->c = input_char;
}

void InsertCharacterCommand::execute() {
    editorInsertChar(c);
    this->cx = E->cx;
    this->cy = E->cy;
}

void InsertCharacterCommand::undo() {
    E->cx = this->cx;
    E->cy = this->cy;
    BackSpaceCommand backSpaceCommand(E);
    backSpaceCommand.execute();
    this->cx = E->cx;
    this->cy = E->cy;
}

void InsertCharacterCommand::redo() {
    E->cx = this->cx;
    E->cy = this->cy;
    execute();
}

void InsertCharacterCommand::editorRowInsertChar(erow *row, int at, int c) {
    if (at < 0 || at > row->size) at = row->size;
    row->chars = (char*) realloc(row->chars, row->size + 2);
    memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);
    row->size++;
    row->chars[at] = c;
    editorUpdateRow(row);
    E->dirty++;
} 

void InsertCharacterCommand::editorInsertChar(int c) {
    if (E->cy == E->numrows) {
        editorInsertRow(E->numrows, (char*)"", 0);
    }
    editorRowInsertChar(&E->row[E->cy], E->cx, c);
    E->cx++;
}

InsertNewLineCommand::InsertNewLineCommand(editorConfig* e) : ICommand(e) {}

void InsertNewLineCommand::execute() {
    editorInsertNewline();
    this->cx = E->cx;
    this->cy = E->cy;
}

void InsertNewLineCommand::undo() {
    E->cx = this->cx;
    E->cy = this->cy;
    BackSpaceCommand backSpaceCommand(E);
    backSpaceCommand.execute();
    this->cx = E->cx;
    this->cy = E->cy;
}

void InsertNewLineCommand::redo() {
    E->cx = this->cx;
    E->cy = this->cy;
    execute();
}

void InsertNewLineCommand::editorInsertNewline() {
    if (E->cx == 0) {
        editorInsertRow(E->cy, (char*) "", 0);
    } else {
        erow *row = &E->row[E->cy];
        editorInsertRow(E->cy + 1, &row->chars[E->cx], row->size - E->cx);
        row = &E->row[E->cy];
        row->size = E->cx;
        row->chars[row->size] = '\0';
        editorUpdateRow(row);
    }
    E->cy++;
    E->cx = 0;
}
