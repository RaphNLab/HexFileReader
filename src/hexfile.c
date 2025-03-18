#include "hexfile.h"
#include "memory.h"
#include "menu.h"
#include <time.h>



uint32_t segmentAddrMsb = 0U;
uint32_t segmentAddrLsb = 0U;
bool_t firstDataRecord = FALSE;
bool_t optionSettingMemFound = FALSE;

uint8_t *hexFileDataBuf;
uint32_t fileSize = 0;
uint32_t firmwaresize = 0;


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
* @brief Read the file one line after the other
* @param hexFile FILE*, Pointer to the file to read
* @param datBuf char*, buffer to store the line to read
* @retval void
*/
static void readHexFileLine(FILE *hexFile, char *datBuf);


/*
* @brief Parse hexfile char into hex record
* @param hexChar char*, buffer containing hex file line
* @param record hexRecord_t, record struct
* @retval void
*/
static hexErrorCode_t parseHexRecord(char *hexChar, hexRecord_t *record);

/**
 * @brief Evaluate data record
 * @param record hexRecord_t, record struct
 * @retval hexRecord_t
 */
static hexErrorCode_t evalRecord(hexRecord_t *record);


/**
 * @brief This function fills the resulting firmware buffer with 0xFF bytes if the last page is not 1Kb
 * */
static void complete_file(uint8_t *firmwareBuf, uint32_t actualSize);



void eveluateFile(char *hexFileName)
{
    FILE *hexFile;
    char hexBuffer[HEX_FILE_MAX_COL] = {0};
    hexRecord_t record;
    hexErrorCode_t parseOk = HEXFILE_ERROR;
    hexErrorCode_t evalRecordOk = HEXFILE_ERROR;

    uint32_t writeIdx = 0;

    hexFile = fopen(hexFileName, "r");
    if(NULL != hexFile)
    {
        do
        {
            // Read each line 
            readHexFileLine(hexFile, hexBuffer);

            // Parse every Record
            parseOk = parseHexRecord(hexBuffer, &record);

            if(parseOk == HEXFILE_OK)
            {
                evalRecordOk = evalRecord(&record);
                
                if((evalRecordOk == HEXFILE_DATA_RECORD_EVAL_OK) && !optionSettingMemFound)
                {
                	uint16_t i;
					uint16_t len = (uint8_t)record.byteSize;
                	for(i = 0; i < len; i++)
					{
						// TODO:
						// - Store the firmware data
						hexFileDataBuf[writeIdx] = record.data[i];
						writeIdx++;
					}
                }
                if((evalRecordOk = HEXFILE_LIN_ADDR_MSB) || (evalRecordOk == HEXFILE_OPTION_SETTING_MEM))
                {
                    continue;
                }
            }
            else if(parseOk == HEXFILE_CRC_ERROR)
            {
                printf("ERROR: Wrong CRC\n");
            }
            else
            {
                printf("ERROR: Unable to parse hex record\n");
            }
        } while (record.recordType != EOF_RECORD);
        // Notice how much data was written
        //firmwaresize = writeIdx;
        // Complete the file and store the real firmware size
        complete_file(hexFileDataBuf, writeIdx);
    }
    else
    {
        printf("ERROR: Can't open the file\n"
               "ERROR: No such file or directory\n"
        );
    }

    fclose(hexFile);
}

static void readHexFileLine(FILE *hexFile, char *dataBuf)
{
    char c = '0';
    uint16_t i = 0;

    do
    {
        c = (char)fgetc(hexFile);
        dataBuf[i] = c;
        i++;
    } while (c != '\n');

    dataBuf[i] = 0;
    
}

static void getByteValue(char *hexChar, uint8_t *hexUint)
{
    uint16_t i;
    size_t size = strlen(hexChar);

    for(i = 0; i < size; i++)
    {
        if(hexChar[i] != '\n')
        {
            hexUint[i] = charTouint8(hexChar[i]);
        }
    }
}


static hexErrorCode_t parseHexRecord(char *hexChar, hexRecord_t *record)
{
    uint8_t hexUint[HEX_FILE_MAX_COL] = {0};
    uint16_t i, j;
    hexErrorCode_t retVal = FALSE;
    uint8_t calcCrc = 0;

    if(hexChar[0] == ':')
    {
        getByteValue(hexChar, hexUint);

        record->startCode = hexChar[0];
        record->byteSize = memory_readbyte(hexUint, BYTE_SIZE_POS);
        record->lsbAddr = memory_readUint16(hexUint, LSB_ADDR_POS);
        record->recordType = memory_readbyte(hexUint, RECORD_TYPE_POS);
        record->crc =  memory_readbyte(hexUint, (uint8_t)(DATA_POS + (uint8_t)(record->byteSize * 2)));

        calcCrc = record->byteSize;
        calcCrc += (uint8_t)((record->lsbAddr >> 8) & BYTE_MASK) + (uint8_t)(record->lsbAddr & BYTE_MASK);
        calcCrc += (uint8_t)record->recordType + (uint8_t)record->crc;

        for (i = 0, j = 0; i < (record->byteSize * 2); i += 2, j++)
        {
          record->data[j] =  memory_readbyte(hexUint, (uint8_t)(DATA_POS + i));
          calcCrc += record->data[j];
        }

        if(calcCrc != 0)
        {
            retVal = HEXFILE_CRC_ERROR;
        }
        retVal = HEXFILE_OK;
    }
    else
    {
        printf("Wrong data Record\n");
    }
    return retVal;
}


static hexErrorCode_t evalRecord(hexRecord_t *record)
{
    hexErrorCode_t retVal = HEXFILE_ERROR;

    switch (record->recordType)
    {
    case DATA_RECORD:
    {
        /* Handle data record */

        /* Find a correct way to save hex data*/
        uint32_t addr = 0;
        segmentAddrLsb = record->lsbAddr;
        addr = (uint32_t)(segmentAddrMsb | segmentAddrLsb);

        if(addr == OPTION_SETTING_MEM)
        {
            // Jump to the next section record
            optionSettingMemFound = TRUE;
            retVal = HEXFILE_OPTION_SETTING_MEM;
        }
        else
        {
        	/* Handle only if record != option setting */
        	if(!optionSettingMemFound)
        	{
				if(!firstDataRecord)
				{
					// Store the start address
					firstDataRecord = TRUE;
				}
        	}
            retVal = HEXFILE_DATA_RECORD_EVAL_OK;
        }
    }
        break;
    case EOF_RECORD:
        /* Handle end of file record */
        retVal = HEXFILE_EOF;
        break;
    case EXT_SEG_ADDR_RECORD:
    {
        /* Handle extended segment address record */
        /* Store segment address MSB*/
        uint32_t segAddrMsb = (uint32_t)record->data[0] << 8 | record->data[1];
        segmentAddrMsb = segAddrMsb << 8;
    } 
        break;
    case START_SEG_ADDR_RECORD:
        /* Handle start segment address record */
        break;
    case EXT_LIN_ADDR_RECORD:
    {
        /* Handle Linear segment address record */
        /* Store segment address MSB*/
    	segmentAddrMsb = (uint32_t)(record->data[0] << 24) | (record->data[1] << 16);

        if(optionSettingMemFound)
        {
            optionSettingMemFound = FALSE;
        }
        retVal = HEXFILE_LIN_ADDR_MSB;
    } 
        break;
    case START_LIN_ADDR_RECORD:
    {
        /* Handle start linear address record */
        /* Store segment address MSB*/
    	segmentAddrMsb = (uint32_t)(record->data[0] << 24) | (record->data[1] << 16);
    }
        break;
    default:
        retVal = HEXFILE_UNDEFINED_RECORD;
        break;
    }

    return retVal;
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
        printf("ERROR: Can't open the file\n"
               "ERROR: No such file or directory\n"
        );
    }    
    return retVal;
}


/**
 * @brief This function fills the resulting firmware buffer with 0xFF bytes if the last page is not 1Kb
 * */
static void complete_file(uint8_t *firmwareBuf, uint32_t actualSize)
{
	uint32_t i;
	uint16_t diff = 0;

	diff = FLASH_PAGE_SIZE - (actualSize % FLASH_PAGE_SIZE);

	for(i = actualSize; i < (actualSize + diff); i++)
	{
		firmwareBuf[i] = 0xff;
	}
	firmwaresize = i; //Store the resulting firmware size
}


void storeFirmwareToTable(uint8_t *FirmwareBuf, char *fileName, uint32_t size)
{
    FILE *file;
    uint32_t i;
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    file = fopen(fileName, "w");
    char *header =  "\n\n"
                    "const uint8_t firmwarebuf[] = \n"
                    "{";

    char *end = "\n};\n\n#endif /* INCLUDE_FIRMWARE_H_ */";

    
    if(NULL != file)
    {       
        fprintf(file, "/*\n"
                    "* firmware.h\n"
                    "*\n"
                    "*  Created on:"
        );
        fprintf(file, " %d.%d.%d\n", tm.tm_mday, (tm.tm_mon + 1), (tm.tm_year + 1900));
        fprintf(file, "*      Author: silvere.sacker.ngouf\n"
                      "*/\n"
                      "#ifndef INCLUDE_FIRMWARE_H_\n"
                      "#define INCLUDE_FIRMWARE_H_\n\n"
        );

        fprintf(file, "%s", header);


        for(i = 0; i < size; i++)
        {  
            if((i % 16) == 0)
            {
                fprintf(file, "\n\t");
            }
            fprintf(file, "0x%02X", FirmwareBuf[i]);

            if(i != size -1)
            {
                fprintf(file, ", ");
            }
        }


        fprintf(file, "%s", end);

        printSuccess(fileName);
    }
    else
    {
        printf("ERROR: Can't open the file\n"
               "ERROR: No such file or directory\n"
        );
    }

    fclose(file);
}




