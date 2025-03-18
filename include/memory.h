#ifndef MEMORY_H_
#define MEMORY_H_

#include "global.h"

#define MY_BYTE_MASK           0xFFU


#define FLASH_PAGE_SIZE          	0x400U /* 1KB page size */
#define BOOTLOADER_ADDR_OFFSET		0x0080UL
#define BOOTLOADER_CRC_TABLE_SIZE	0x80U
#define	PLFMCRC_START_MODBUS          0xFFFFU


typedef enum  fwu_status_t
{
	FWU_SUBPAGE_WRITEN = 1,
	FWU_PAGE_WRITEN = 2,
	FWU_RESTART_OK = 1,
	FWU_RESTART_NOT_OK = 2,
	FWU_VERIFY_IS_RUNNING = 1,
	FWU_VERIFY_SUCCESSFUL = 2,
	FWU_VERIFY_NOT_SUCCESSFUL = 3,
	FWU_INVALID_STATUS = 10
}fwu_status_t;


extern const uint8_t firmwarebuffer[45000];


char **memReserve(uint32_t raw, uint32_t col);


void MemRelease(char **buffer, uint32_t col);

/**
 * @brief Copy data from a source to destination buffer
 * @param src uint8_t*. Source buffer
 * @param dest uint8_t. destination buffer
 * @param size uint16_t. Data size
 * @retval None
*/
void memory_copy(uint8_t *src, uint8_t *dest, uint16_t size);

uint8_t memory_readbyte(uint8_t *buf, uint8_t index);

uint16_t memory_readUint16(uint8_t *buf, uint8_t index);

uint32_t memory_readUint32(uint8_t *buf, uint8_t index);





#endif
