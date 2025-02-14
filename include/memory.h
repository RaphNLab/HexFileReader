#ifndef MEMORY_H_
#define MEMORY_H_

#include "global.h"
#define MY_BYTE_MASK           0xFFU


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