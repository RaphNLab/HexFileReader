#include "include/hexfile.h"


int main(void)
{
    char *fileName = "Input_file/PC550_STM32.hex";
    char fileData[FILE_SIZE] = {0};
    
    //size_t cnt = 0;
    uint32_t fileLines = 0;
    

    fileLines = countFileLines(fileName);
        
    char **hexData;
    hexData = memReserve(fileLines, HEX_FILE_MAX_COL);

    readHexFileLine(fileLines, hexData, fileName);

    uint8_t dataUint[16] = {0};
    getByteValue(fileData);

    MemRelease(hexData, HEX_FILE_MAX_COL);    
    return 0;
}


