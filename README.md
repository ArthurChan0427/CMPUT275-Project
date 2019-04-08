Makefile Targets:
    1. all: Compile all source codes into executables. In this package,
            there is only one final executable "kilo".

    2. kilo: Link all objects required and build the executable kilo

    3. kilo.o: Compiles kilo.cpp with other dependencies

    4. commandManager.o: Compiles commandManager.cpp with other dependencies

    5. autoComplete.o: Compiles autoComplete.cpp with other dependencies
    
    6. iCommand.o: Compiles iCommand.cpp with other dependencies

    7. clean: Remove all object files and executables

Online Sources:
    Base code: https://viewsourcecode.org/snaptoken/kilo/
    Command design pattern for Undo/Redo: http://gernotklingler.com/blog/implementing-undoredo-with-the-command-pattern/
    
