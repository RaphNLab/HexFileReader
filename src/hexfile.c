#include "include/hexfile.h"


void eveluateFile(char *hexFileName)
{
    FILE *hexFile;
    char *hexBuffer[HEX_FILE_MAX_COL];
    hexRecord_t record;

    hexFile = fopen(hexFileName, "r");
    if(NULL != hexFile)
    {
        do
        {
            // Read each line 
            readHexFileLine(hexFile, hexBuffer);
            // Parse every Record
            parseHexRecord(hexBuffer, &record);
        } while (record.recordType != EOF_RECORD);
    }
    else
    {
        printf("Can't open the file\n");
    }

    fclose(hexFile);
}


static void readHexFileLine(FILE *hexFile, char *datBuf)
{
    char c = '0';
    FILE *hexFile;

    for(uint32_t i = 0; i < HEX_FILE_MAX_COL; i++)
    {
        c = (char)fgetc(hexFile);
        datBuf[i] = c;
        if(c == '\n')
        {
            datBuf[i] = 0;
            break;
        }
    }
}

static uint8_t *getByteValue(char *hexChar)
{
    uint8_t i = 0;
    size_t size = strlen(hexChar);
    uint8_t hexUint[HEX_FILE_MAX_COL];

    for(i = 0; i < size; i++)
    {
        if(hexChar[i] != '\n')
        {
            hexUint[i] = charTouint8(hexChar[i]);
        }
    }
    return hexUint;
}


static void parseHexRecord(char *hexChar, hexRecord_t *record)
{
    uint8_t *hexUint;
    uint8_t i;
    if(hexChar[0] != ':')
    {
        hexUint = getByteValue(hexChar);

        record->startCode = hexUint[0];
        record->byteSize = memory_readbyte(hexUint, BYTE_SIZE_POS);
        record->lsbAddr = memory_readUint16(hexUint, LSB_ADDR_POS);
        record->recordType = memory_readbyte(hexUint, RECORD_TYPE_POS);
        record->crc =  memory_readbyte(hexUint, (DATA_POS + record->byteSize));

        for (i = 0; i < record->byteSize; i++)
        {
          record->data[i] =  memory_readbyte(hexUint, (DATA_POS + i));
        }
    }
    else
    {
        printf("Wrong data Record");
    }
}


static uint8_t charTouint8(char c)
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


static void retreiveSegtionAddr(char *hexFile, uint32_t *addr)
{
    /* :020000040800F2 
       :020000040801F1
    */

}