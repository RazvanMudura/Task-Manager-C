#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


#include "cjson/cJSON.h"
#include "source/colors.c"
#include "source/tasks.c"
#include "source/utils.c"
#include "source/ascii.c"



enum commands {
    ADD = 1,
    REMOVE = 2,
    READ = 3,
    LIST = 4,
    HELP = 5,
    EXIT = 6
};






void runCommand() {

    char input[100];
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';



    char* trimmedInput = Trim (input);
    char* command = parseCommand (trimmedInput);



    bool hasArguments = true;
    if (strcmp (command, trimmedInput) == 0) hasArguments = false;



    char* arguments;
    if (hasArguments) 
       arguments = parseArguments (trimmedInput);
    



    switch (convertCommand(command)) {
        case ADD: {
            if (!hasArguments) {
                printColor ("Please enter the required arguments!", "red");
                break;
            }

            char* title = parseTitleAdd (arguments);
            char* description = parseDescriptionAdd (arguments);


            if (strcmp (title, "") == 0 || strcmp (description, "") == 0) {
                printColor ("Wrong Arguments Passed!", "red");
                break;
            }


            addTask (title, description);
            break;
        }



        case REMOVE: {
            if (!hasArguments) {
                printColor ("Please enter the required arguments!", "red");
                break;
            }


            char* title = parseTitle (arguments);


            if (strcmp (title, "") == 0) {
                printColor("Wrong Arguments Passed!", "red");
                break;
            }


            removeTask (title);
            break;
        }

        

        case READ: {
            if (!hasArguments) {
                printColor ("Please enter the required arguments!", "red");
                break;
            }

            char* title = parseTitle (arguments);


            if (strcmp(title, "") == 0) {
                printColor ("Wrong arguments passed!", "red");
                break;
            }


            readTask (title);
            break;
        }

        

        case LIST: {
            if (hasArguments) {
                printColor ("This commmand doesn't require any arguments!", "red");
                break;
            }

            listTasks ();
            break;
        }



        case HELP: {
            if (hasArguments) {
                printColor ("This commmand doesn't require any arguments!", "red");
                break;
            }

            printColor (
                "Commands:                         \n"
                "- add -t='' -b='' : adds a task   \n"
                "- remove -t='' : removes a task   \n"
                "- read -t='' : reads a task       \n"
                "- list : lists all tasks          \n"
                "- help : shows available commands \n"
                "- exit : exits the app            \n",
                "cyan"
            );
            break;
        }



        case EXIT: {
            if (hasArguments) {
                printColor ("This commmand doesn't require any arguments!", "red");
                break;
            }

            printColor ("Exiting...", "yellow");
            return;
        }



        default: {
            printColor ("Command not found!", "red");
            break;
        }
    }


    runCommand ();
}




int main(int argc, char *argv[]) {
    startAscii ();
    loadTasks ();
    runCommand ();
}