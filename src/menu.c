#include "menu.h"
#include "global.h"


void printMenu(void)
{
    printf("##############################################################\t\n"
          "*\tProvide programm arguments*                                *\t\n"
          "*\tExample: ./hex_file_reader.exe inputFile outputFile        *\t\n"
          "*\tN.B: Give the relative file path if located somewhere else*\t\n"
          "##############################################################\t\n"
    );
}

void printSuccess(char *location)
{
    printf("###############################################################\n"
           "+\t Firmware store successfully                          +\n"
           "+\t File location:                                       +\n"
           "+\t %s +\n"
           "###############################################################\n"
        , location);
}