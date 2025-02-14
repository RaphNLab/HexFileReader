#include "hexfile.h"
#include "memory.h"


/*
* @brief convert each char to byte and return byte buffer
* @param hexChar : buffer containing all characters
* @retval uint8_t *
*/
static void getByteValue(char *hexChar, uint8_t *hexUint);

/*
* @brief Convert single character to byte value
* @param C : charracter to convert
* @retval uint8_t
*/
static uint8_t charTouint8(char c);

/*
* @brief extract section address
*/
static void readHexFileLine(FILE *hexFile, char *datBuf);


/*
* @brief extract section address
*/
static void parseHexRecord(char *hexChar, hexRecord_t *record);



void eveluateFile(char *hexFileName)
{
    FILE *hexFile;
    char hexBuffer[HEX_FILE_MAX_COL] = {0};
    hexRecord_t record;

    hexFile = fopen(hexFileName, "r");
    if(NULL != hexFile)
    {
        do
        {
            // Read each line 
            readHexFileLine(hexFile, hexBuffer);

            printf("%s", hexBuffer);

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


// C037002081B2000839120108AB0C0108

static void readHexFileLine(FILE *hexFile, char *datBuf)
{
    char c = '0';

    for(uint8_t i = 0; i < HEX_FILE_MAX_COL; i++)
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

static void getByteValue(char *hexChar, uint8_t *hexUint)
{
    uint8_t i;
    size_t size = strlen(hexChar);

    for(i = 0; i < size; i++)
    {
        if(hexChar[i] != '\n')
        {
            hexUint[i] = charTouint8(hexChar[i]);
        }
    }
}


static void parseHexRecord(char *hexChar, hexRecord_t *record)
{
    uint8_t hexUint[HEX_FILE_MAX_COL] = {0};
    uint8_t i, j;

    if(hexChar[0] == ':')
    {
        getByteValue(hexChar, hexUint);

        record->startCode = hexChar[0];
        record->byteSize = memory_readbyte(hexUint, BYTE_SIZE_POS);
        record->lsbAddr = memory_readUint16(hexUint, LSB_ADDR_POS);
        record->recordType = memory_readbyte(hexUint, RECORD_TYPE_POS);
        record->crc =  memory_readbyte(hexUint, (uint8_t)(DATA_POS + (record->byteSize * 2)));

        for (i = 0, j = 0; i < (record->byteSize * 2); i += 2, j++)
        {
          record->data[j] =  memory_readbyte(hexUint, (uint8_t)(DATA_POS + i));
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
            case ':':
                retVal = 58;
            break;
            default:
                break;
        }
    }
    return retVal;
}
