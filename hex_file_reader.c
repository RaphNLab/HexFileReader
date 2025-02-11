#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_RECORD_SIZE     0x10U
#define HEX_FILE_MAX_COL    44U
#define FILE_SIZE           0x800U
#define END_CHAR            '\n'

#define BYTE_SIZE_POS       1U
#define LSB_ADDR_POS        3U
#define RECORD_TYPE_POS     7U
#define DATA_POS            9U

#define RENESAS_MCU         1U
#define STM32_MCU           0U

#if RENESAS_MCU
#define MIN_FLASH_ADDR      0xFFF00000U
#define MAX_FLASH_ADDR      0xFFFFFFFFU
#define OPTION_SETTING_MEM  0x00120040U
#elif STM32_MCU
#define MIN_FLASH_ADDR      0x08000000U
#define MAX_FLASH_ADDR      0xFFFFFFFFU
#endif


typedef enum
{
    DATA_RECORD             = 00,
    EOF_RECORD              = 01,
    EXT_SEG_ADDR_RECORD     = 02,
    START_SEG_ADDR_RECORD   = 03,
    EXT_LIN_ADDR_RECORD     = 04,
    START_LIN_ADDR_RECORD   = 05
}recordType_t;


typedef struct
{
    char startCode;
    uint8_t byteSize;
    uint8_t data[16];
    uint8_t crc;
    uint16_t lsbAddr;
    recordType_t recordType;
}hexRecord_t;


void retreiveSegtionAddr(char *hexFile, uint32_t *addr);
uint8_t calcCrc(char *data);
void getByteValue(char *dataChar, uint8_t *dataUint);
uint8_t charTouint8t(char c);
void readHexFileLine(FILE *hexFileBuf, uint32_t lineSize, char **datBuf);
uint32_t countFileLines(FILE *hexFileBuf);

char **memReserve(uint32_t raw, uint32_t col);

int main(void)
{

    FILE *hexFile;
    char *fileName = "Input_file/PC550_STM32.hex";

    char fileData[FILE_SIZE] = {0};
    //size_t cnt = 0;
    hexFile = fopen(fileName, "r");  
     
    if(hexFile == NULL)
    {
        printf("Can't open the file\n");
    }
    else
    {
        /*
        char c = '0';
        uint32_t i = 0;
        do
        {
            c = (char)fgetc(hexFile);
            fileData[i] = c; 
            i++;
        }
        while((i < 16));
        */

        uint32_t fileLines = 0;
        fileLines = countFileLines(hexFile);


        char **hexData = memReserve(fileLines, HEX_FILE_MAX_COL);

        readHexFileLine(hexFile, fileLines, hexData);

        uint8_t dataUint[16] = {0};
        getByteValue(fileData, dataUint);

        fclose(hexFile);
    }
    return 0;
}

char **memReserve(uint32_t raw, uint32_t col)
{
    char **buffer;
    buffer = (char**)calloc(raw, sizeof(char));
    for(uint32_t i = 0; i < col; i++)
    {
        buffer[i] = (char*)calloc(col, sizeof(char));
    }

    return buffer;
}


uint32_t countFileLines(FILE *hexFileBuf)
{
    uint32_t retVal = 0;
    char c = '0';
    do
    {
        c = (char)fgetc(hexFileBuf);
        if(c == '\n')
        {
            retVal++;
        }
    } while (c != EOF);
    
    return retVal;
}


void readHexFileLine(FILE *hexFileBuf, uint32_t lineSize, char **datBuf)
{
    char c = '0';

    for(uint16_t i = 0; i < lineSize; i++)
    {
        for(uint16_t j = 0; j < HEX_FILE_MAX_COL; j++)
        {
            c = (char)fgetc(hexFileBuf);
            datBuf[i][j] = c;
            if(c == '\n')
            {
                break;
            }
        }
        printf("%s", datBuf[i]);
    }
}

void getByteValue(char *dataChar, uint8_t *dataUint)
{
    uint8_t i = 0, j = 0;
    size_t size = strlen(dataChar);

    for(i = 1; i < size; i++, j++)
    {
        if(dataChar[i] != '\n')
        {
            dataUint[j] = charTouint8t(dataChar[i]);
        }
    }
}

uint8_t charTouint8t(char c)
{
    uint8_t retVal = 0;;

    if((c >= '0') && (c <= '9'))
    {
        retVal = (uint8_t)(c - '0');
    }
    else
    {
        switch (c)
        {
            case 'a':
            case 'A':
                retVal = 10;
            break;
            
            case 'b':
            case 'B':
                retVal = 11;
            break;
            case 'c':
            case 'C':
                retVal = 12;
            break;
            case 'd':
            case 'D':
                retVal = 13;
            break;
            case 'e':
            case 'E':
                retVal = 14;
            break;
            case 'f':
            case 'F':
                retVal = 15;
            break;
            default:
                break;
        }
    }
    return retVal;
}


void retreiveSegtionAddr(char *hexFile, uint32_t *addr)
{
    /* :020000040800F2 
       :020000040801F1
    */

}

uint8_t calcCrc(char *data)
{
    uint8_t retVal = 0;

    return retVal;
}



