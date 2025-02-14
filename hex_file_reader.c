#include "include/hexfile.h"


int main(void)
{
    char *fileName = "Input_File/PC550_STM32.hex";
    char fileData[FILE_SIZE] = {0};
    
    //size_t cnt = 0;
    uint32_t fileLines = 0;
    

    fileLines = countFileLines(fileName);
        
    char **hexData;
    hexData = memReserve(fileLines, HEX_FILE_MAX_COL);

    readHexFileLine(fileLines, hexData, fileName);

<<<<<<< HEAD
    uint8_t dataUint[16] = {0};
    getByteValue(fileData);
=======
    /*uint8_t dataUint[16] = {0};
    getByteValue(fileData, dataUint);
    */
>>>>>>> e65e432b962c023f36945059d2a0357e2d1e3728

    MemRelease(hexData, HEX_FILE_MAX_COL);    
    return 0;
}

<<<<<<< HEAD
=======
char **memReserve(uint32_t raw, uint32_t col)
{
    uint32_t i;
    char **buffer;

    buffer = (char **)malloc(sizeof(char *) * raw);

    for(i = 0; i < raw; i++)
    {
        buffer[i] = (char *)malloc(sizeof(char) * col);
        memset(buffer[i], 0, (sizeof(char) * col));
    }
    return buffer;
}

void MemRelease(char **buffer, uint32_t col)
{
    for(uint32_t i = 0; i < col; i++)
    {
        char *ptr = buffer[i];
       free(ptr);
    }
    free(buffer);
}


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


>>>>>>> e65e432b962c023f36945059d2a0357e2d1e3728

