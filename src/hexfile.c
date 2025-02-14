#include "include/hexfile.h"


uint32_t countFileLines(char *fileName)
{
    uint32_t retVal = 0;
    FILE *file;
    char c = '0';

    file = fopen(fileName, "r");
    if(NULL != file)
    {       
        do
        {
            c = (char)fgetc(file);
            if(c == '\n')
            {
                retVal++;
            }
        } while (c != EOF);
        fclose(file);
    }
    else
    {
        printf("Can't open the file\n");
    }    
    return retVal;
}


//":10B00000C037002081B2000839120108AB0C0108DA\n��������"

void readHexFileLine(uint32_t lineSize, char **datBuf, char *hexFileName)
{
    char c = '0';
    FILE *hexFile;

    hexFile = fopen(hexFileName, "r");
    if(NULL != hexFile)
    {
        for(uint32_t i = 0; i < lineSize; i++)
        {
            for(uint32_t j = 0; j < HEX_FILE_MAX_COL; j++)
            {
                c = (char)fgetc(hexFile);
                datBuf[i][j] = c;
                if(c == '\n')
                {
                    datBuf[i][j] = 0;
                    break;
                }
            }
            printf("%s", datBuf[i]);
        }
        fclose(hexFile);
    }
    else
    {
        printf("Can't open the file\n");
    }
}

uint8_t *getByteValue(char *hexChar)
{
    uint8_t i = 0;
    size_t size = strlen(hexChar);
    uint8_t hexUint[size];

    for(i = 0; i < size; i++)
    {
        if(hexChar[i] != '\n')
        {
            hexUint[i] = charTouint8(hexChar[i]);
        }
    }
    return hexUint;
}


void parseHexRecord(char *hexChar, hexRecord_t *record)
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


uint8_t charTouint8(char c)
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