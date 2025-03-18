#include "hexfile.h"
#include "menu.h"
#include "memory.h"


/*
 * TODO:
 * Read the size of the firmware and fill the table with 0xFF, to complete the page.
 * */

int main(int argc, char *argv[])
{
    int retVal = 0;
    char *fileName;
    char *FirmwareFile;


    if(argc < 3)
    {
        printMenu();
        retVal = -1;
    }
    else
    {
        fileName = argv[1];
        FirmwareFile = argv[2];


    	fileSize = (countFileLines(fileName) * HEX_FILE_MAX_COL);

        hexFileDataBuf = (uint8_t*)calloc((fileSize + FLASH_PAGE_SIZE), sizeof(uint8_t*)); //Add supplementary page to prevent memory overflow

        eveluateFile(fileName);

        storeFirmwareToTable(hexFileDataBuf, FirmwareFile, firmwaresize);

        /* Free Dynamic  allocated memory */
        free(hexFileDataBuf);
    }

    return retVal;
}
