#ifndef HEXFILE_H_
#define HEXFILE_H_

#include "global.h"


#define MAX_RECORD_SIZE     0x10U
#define HEX_FILE_MAX_COL    524U
#define FILE_SIZE           0x800U
#define END_CHAR            '\n'

#define BYTE_SIZE_POS       1U
#define LSB_ADDR_POS        3U
#define RECORD_TYPE_POS     7U
#define DATA_POS            9U
#define BYTE_MASK           0xFF

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



/*
* @brief extract section address
*/
typedef enum
{
    DATA_RECORD             = 00,
    EOF_RECORD              = 01,
    EXT_SEG_ADDR_RECORD     = 02,
    START_SEG_ADDR_RECORD   = 03,
    EXT_LIN_ADDR_RECORD     = 04,
    START_LIN_ADDR_RECORD   = 05
}recordType_t;


typedef enum
{
    HEXFILE_ERROR = 0,
    HEXFILE_OK,
    HEXFILE_EOF,
    HEXFILE_CRC_ERROR,
    HEXFILE_DATA_RECORD_EVAL_OK,
    HEXFILE_LIN_ADDR_MSB,
    HEXFILE_OPTION_SETTING_MEM,
    HEXFILE_NO_OPTION_SETTING_MEM,
    HEXFILE_UNDEFINED_RECORD
}hexErrorCode_t;

/*
* @brief extract section address
*/
typedef struct
{
    char startCode;
    uint8_t byteSize;
    uint8_t data[HEX_FILE_MAX_COL];
    uint8_t crc;
    uint16_t lsbAddr;
    recordType_t recordType;
}hexRecord_t;


extern uint32_t fileSize;
extern uint32_t firmwaresize;
extern uint8_t *hexFileDataBuf;

/*
* @brief extract section address
*/
void eveluateFile(char *hexFileName);

/*
* @brief extract section address
*/
void retreiveSegtionAddr(char *hexFile, uint32_t *addr);

void storeFirmwareToTable(uint8_t *FirmwareBuf, char *fileName, uint32_t size);

uint32_t countFileLines(char *fileName);

#endif
