--------------------------------------------------------
Name:  Ryan Jacques         / Arthur Chan
ID:    1523211              / 1425382
Email: rjacques@ualberta.ca / yungjen@ualberta.ca
CMPUT 275, Winter 2019

Final Project: Textfile Editor
--------------------------------------------------------

Included Files:
* kilo.cpp
* iCommand.cpp
* iCommand.h
* commandManager.cpp
* commandManager.h
* autoComplete.cpp
* autoComplete.h
* text
* Makefile
* README

Running Instructions: 
    1. Navigate to the directory containing all files included above
    2. Run 'make kilo' to compile the executable called "kilo"
    3. Run './kilo' to open a blank text editor in Terminal
    4. Run './kilo (name of text file)' to open a text file in Terminal
    5. Navigate the editor using the up-down-left-right arrow keys to move the cursor
    6. Type any character to add that character to the editor
    7. Use ctrl-z to undo, use ctrl-r to redo
    8. *** When typing, the editor will display a recommended word if a word that begins with the word being typed has been saved into the system already
    9. Use ctrl-q to exit the editor

    *** See Notes and Assumptions section for details on how to partially test this functionality

Makefile Targets:
    1. all: Compile all source codes into executables. In this package, there is only one final executable "kilo".

    2. kilo: Link all objects required to build the executable kilo

    3. kilo.o: Compiles kilo.cpp with other dependencies

    4. commandManager.o: Compiles commandManager.cpp with other dependencies

    5. autoComplete.o: Compiles autoComplete.cpp with other dependencies

    6. iCommand.o: Compiles iCommand.cpp with other dependences

    7. clean: Remove all object files and executables

Notes and Assumptions:
    - Please note that the file kilo.cpp is almost entirely unoriginal, taken and adapted from the basic text editor tutorial at https://viewsourcecode.org/snaptoken/kilo/index.html.
    - The auto complete is not fully functional and has been commented out so that other aspects of the text editor can be primarily focussed on. To get a sense of what the auto complete is doing and how it is supposed to work, comment out line 729 of kilo.cpp. The autoComplete class, with functions search and update, functions as it is intended to, but we were unable to proerly display the recommended word in the text editor. When the user begins typing, if it finds a word stored in map<string, unsigned int> words in the autoComplete class, it will print out the remainder of the word in the text editor. However, there are issues with spacing and cursor movement, as well as words only appearing the first time a substring is typed into the editor. We do apologize for this issue that could not be resolved.

Citations:
    1. Code written in class.
    2. Basic text editor tutorial and base code: https://viewsourcecode.org/snaptoken/kilo/index.html
    3. String to char array code: https://www.techiedelight.com/convert-string-char-array-cpp/
    4. Command design pattern for Undo/Redo: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/

