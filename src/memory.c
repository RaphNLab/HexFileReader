#include "memory.h"


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
       free(buffer[i]);
    }
    free(buffer);
}


void memory_copy(uint8_t *src, uint8_t *dest, uint16_t size)
{
    for(int i = 0; i < size; i++)
    {
        dest[i] = src[i]; 
    }
}


uint8_t memory_readbyte(uint8_t *buf, uint8_t index)
{
    uint8_t retVal = 0;
    
	retVal = (uint8_t)((buf[index] << 4) & (uint8_t)MY_BYTE_MASK);
    retVal |= (uint8_t)(buf[index + 1] & (uint8_t)MY_BYTE_MASK);
    
    return retVal;
}


uint16_t memory_readUint16(uint8_t *buf, uint8_t index)
{
    uint16_t retVal = 0;
    
    retVal = (uint16_t)((memory_readbyte(buf, index) << 8) & 0xFFFF);
    retVal |= (uint16_t)(memory_readbyte(buf, (uint8_t)(index + 2)) & 0xFFFF);
    
    return retVal;
}


uint32_t memory_readUint32(uint8_t *buf, uint8_t index)
{
    uint32_t retVal = 0;
    
    retVal = (uint32_t)(memory_readbyte(buf, index) << 24);
    retVal |= (uint32_t)(memory_readbyte(buf, (uint8_t)(index + 2U)) << 16);
    retVal |= (uint32_t)(memory_readbyte(buf, (uint8_t)(index + 4U)) << 8);
    retVal |= (uint32_t)memory_readbyte(buf, (uint8_t)(index + 6U));
    
    return retVal;
}