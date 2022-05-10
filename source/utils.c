int convertCommand (char* command) {

    if (strcmp (command, "add") == 0) return 1;
    if (strcmp (command, "remove") == 0) return 2;
    if (strcmp (command, "read") == 0) return 3;
    if (strcmp (command, "list") == 0) return 4;
    if (strcmp (command, "help") == 0) return 5;
    if (strcmp (command, "exit") == 0) return 6;
    
    return 0;
}



char* Trim (char* string) {
    for (int index = strlen(string) - 1; string[index] == ' '; index--) 
        string[index] = '\0';

    string[strlen(string)] = '\0';

    while (isspace(*string)) 
        string++;


    return string;
}



char* parseCommand (char* string) {
    char* command = malloc(100 * sizeof(char));

    for (int index = 0; string[index] != ' ' && string[index] != '\0'; index++) 
        command[index] = string[index];
    
    command[strlen(command)] = '\0';


    return command;
}



char* parseArguments (char* string) {
    char* arguments = malloc(100);


    for (int index = 0, i = 0, counter = 0; index < strlen(string); index++) {
        if (string[index] == ' ') counter++;
        if (counter >= 1) arguments[i++] = string[index];
    }
    arguments[strlen(arguments)] = '\0';


    return Trim(arguments);
}



char* parseTitle (char* string) {
    char* trimmedString = Trim(string);
    bool isShort = false, isLong = false;


    if (trimmedString[strlen(trimmedString) - 1] != '\'' || strlen(trimmedString) < 5) return "";
    if (trimmedString[0] == '-' && trimmedString[1] == 't' && trimmedString[2] == '=' && trimmedString[3] == '\'') isShort = true;
    if (
        trimmedString[0] == '-' && trimmedString[1] == '-' && trimmedString[2] == 't' && trimmedString[3] == 'i' &&
        trimmedString[4] == 't' && trimmedString[5] == 'l' && trimmedString[6] == 'e' && trimmedString[7] == '=' && trimmedString[8] == '\''
    ) isLong = true;



    if (!isLong && !isShort) return "";


    if (isShort) trimmedString += 4;
    if (isLong) trimmedString += 9;


    trimmedString[strlen(trimmedString) - 1] = '\0';


    return trimmedString;
}


char* parseTitleAdd (char* string) {
    char* result = malloc(100);
    bool isShort = false, isLong = false;

    strcpy(result, Trim(string));

    if (result[0] == '-' && result[1] == 't' && result[2] == '=' && result[3] == '\'') isShort = true;
    if (
        result[0] == '-' && result[1] == '-' && result[2] == 't' && result[3] == 'i' &&
        result[4] == 't' && result[5] == 'l' && result[6] == 'e' && result[7] == '=' && result[8] == '\''
    ) isLong = true;

    if (!isLong && !isShort) return "";

    if (isShort) result += 4;
    if (isLong) result += 9;


    int i;
    for (i = 0; result[i] != '\''; i++) {}
    result[i] = '\0';


    return result;
}


char* parseDescriptionAdd (char* string) {
    char* result = malloc(100);
    bool isShort = false, isLong = false;


    strcpy(result, Trim(string));



    if (result[strlen(result) - 1] != '\'') return "";


    if (strstr(result, "-d='") != NULL) {
        result = strstr(result, "-d='");
        isShort = true;
    }
    if (strstr(result, "--description='") != NULL) {
        result = strstr(result, "--description='");
        isLong = true;
    }



    if (!isLong && !isShort) return "";

    if (isShort) result += 4;
    if (isLong) result += 15;
    

    int i;
    for (i = 0; result[i] != '\''; i++) {}
    result[i] = '\0';

    return result;
}