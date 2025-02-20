#include "hexfile.h"


int main(void)
{
    char *fileName = "C:\\Projekte\\hex_file_reader\\Input_File\\PC550_App.hex";
    char *FirmwareFile = "C:\\Projekte\\hex_file_reader\\Output_File\\firmware.txt";

    fileSize = (countFileLines(fileName) * HEX_FILE_MAX_COL);

    hexFileDataBuf = (uint8_t*)calloc(fileSize, sizeof(uint8_t*));

    eveluateFile(fileName);

    storeFirmwareToTable(hexFileDataBuf, FirmwareFile, firmwaresize);


    free(hexFileDataBuf);
    return 0;
}
