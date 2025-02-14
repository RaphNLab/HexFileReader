#ifndef MEMORY_H_
#define MEMORY_H_

#include "include/global.h"
#define BYTE_MASK           0xFFU


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

/**
 * @brief Read uint8_t from a given buffer as big endian
 * @param buf const uint8_t* const. buffer to read from
 * @param index uint16_t. start index
 * @retval uint8_t
*/
uint8_t memory_readUInt8BigEnd(const uint8_t * const buf, uint16_t index);

/**
 * @brief Read uint16_t from a given buffer as big endian
 * @param buf const uint8_t* const. buffer to read from
 * @param index uint16_t. start index
 * @retval uint16_t
*/
uint16_t memory_readUInt16BigEnd(const uint8_t * const buf, uint16_t index);

/**
 * @brief Read uint32_t from a given buffer as big endian
 * @param buf const uint8_t* const. buffer to read from
 * @param index uint16_t. start index
 * @retval uint32_t
*/
uint32_t memory_readUInt32BigEnd(const uint8_t * const buf, uint16_t index);

/**
 * @brief Read uint16_t from a given buffer as little endian
 * @param buf const uint8_t* const. buffer to read from
 * @param index uint16_t. start index
 * @retval uint16_t
*/
uint16_t memory_readUInt16LitEnd(const uint8_t * const buf, uint16_t index);

/**
 * @brief Read uint32_t from a given buffer as little endian
 * @param buf const uint8_t* const. buffer to read from
 * @param index uint16_t. start index
 * @retval uint32_t
*/
uint32_t memory_readUInt32LitEnd(const uint8_t * const buf, uint16_t index);


/**
 * @brief write uint8_t into uint8_t buffer as big endian
 * @param array uint8_t *. buffer to write to
 * @param index uint16_t. start index
 * @retval None
*/
void memory_writeUInt8ToUInt8ArrBigEnd(uint8_t val, uint8_t *array, uint16_t index);

/**
 * @brief write uint16_t into uint8_t buffer as big endian
 * @param array uint8_t *. buffer to write to
 * @param index uint16_t. start index
 * @retval None
*/
void memory_writeUInt16ToUInt8ArrBigEnd(uint16_t val, uint8_t *array, uint16_t index);

/**
 * @brief write uint32_t into uint8_t buffer as big endian
 * @param array uint8_t*. buffer to write to
 * @param index uint16_t. start index
 * @retval None
*/
void memory_writeUInt32ToUInt8ArrBigEnd(uint32_t val, uint8_t *array, uint16_t index);

/**
 * @brief write uint16_t into uint8_t buffer as little endian
 * @param array uint8_t*. buffer to write to
 * @param index uint16_t. start index
 * @retval None
*/
void memory_writeUInt16ToUInt8ArrLitEnd(uint16_t val, uint8_t *array, uint16_t index);

/**
 * @brief write uint32_t into uint8_t buffer as little endian
 * @param array uint8_t*. buffer to write to
 * @param index uint16_t. start index
 * @retval None
*/
void memory_writeUInt32ToUInt8ArrLitEnd(uint32_t val, uint8_t *array, uint16_t index);


#endif