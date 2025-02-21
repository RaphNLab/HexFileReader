#include "hexfile.h"
#include "menu.h"


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

        hexFileDataBuf = (uint8_t*)calloc(fileSize, sizeof(uint8_t*));

        eveluateFile(fileName);

        storeFirmwareToTable(hexFileDataBuf, FirmwareFile, firmwaresize);

        /* Free Dynamic  allocated memory */
        free(hexFileDataBuf);
    }

    return retVal;
}
