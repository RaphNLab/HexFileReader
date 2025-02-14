#include "include/memory.h"


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
    
    retVal =(uint8_t)(((buf[index] << 4) && BYTE_MASK)) | ((buf[index + 1] && BYTE_MASK));
    
    return retVal;
}


uint16_t memory_readUint16(uint8_t *buf, uint8_t index)
{
    uint16_t retVal = 0;
    
    retVal = memory_readbyte(buf, index);
    retVal |= memory_readbyte(buf, (index + 2));
    
    return retVal;
}


uint32_t memory_readUint32(uint8_t *buf, uint8_t index)
{
    uint32_t retVal = 0;
    
    retVal = memory_readbyte(buf, index);
    retVal |= memory_readbyte(buf, (index + 2));
    retVal |= memory_readbyte(buf, (index + 4));
    retVal |= memory_readbyte(buf, (index + 6));
    
    return retVal;
}


uint8_t memory_readUInt8BigEnd(const uint8_t * const buf, uint16_t index)
{
	return (uint8_t)buf[index];   								
}

uint16_t memory_readUInt16BigEnd(const uint8_t * const buf, uint16_t index)
{
	uint16_t val;
	val  = (uint16_t)(buf[index] << 8);   	// msb (high) byte first
	val |= (uint16_t)buf[index + 1];   		// lsb (low) byte last
	return val;
}

uint16_t memory_readUInt16LitEnd(const uint8_t * const buf, uint16_t index)
{
	uint16_t val;
	val  = (uint16_t)buf[index + 1]; 		// msb (high) byte first
	val |= (uint16_t)(buf[index] << 8);  	// lsb (low) byte last
	return val;
}


uint32_t memory_readUInt32BigEnd(const uint8_t * const buf, uint16_t index)
{
	uint32_t val;
	val  = (uint32_t)(buf[index] << 24);   		// msb (high) byte first
	val |= (uint32_t)(buf[index + 1] << 16);  	// lsb (low) byte last
	val |= (uint32_t)(buf[index + 2] << 8);   	// lsb (low) byte last
	val |= (uint32_t)buf[index  + 3];    		// lsb (low) byte last
	return val;
}

void memory_writeUInt8ToUInt8ArrBigEnd(uint8_t val, uint8_t *array, uint16_t index)
{
	array[index] = val;
}

void memory_writeUInt16ToUInt8ArrBigEnd(uint16_t val, uint8_t *array, uint16_t index)
{
	array[index] = (uint8_t)(val >> 8);
	array[index + 1] = (uint8_t)(val & 0xff);
}

void memory_writeUInt16ToUInt8ArrLitEnd(uint16_t val, uint8_t *array, uint16_t index)
{
	array[index] = (uint8_t)(val & 0xff);
	array[index + 1] = (uint8_t)(val >> 8);
}



void memory_writeUInt32ToUInt8ArrBigEnd(uint32_t val, uint8_t *array, uint16_t index)
{
	array[index] = (uint8_t)(val >> 24);
	array[index + 1] = (uint8_t)((val >> 16) & 0xff);
	array[index + 2] = (uint8_t)((val >> 8) & 0xff);
	array[index + 3] = (uint8_t)(val & 0xff);
}

void memory_writeUInt32ToUInt8ArrLitEnd(uint32_t val, uint8_t *array, uint16_t index)
{
	array[index] = (uint8_t)(val & 0xff);
	array[index + 1] = (uint8_t)((val >> 8) & 0xff);
	array[index + 2] = (uint8_t)((val >> 16) & 0xff);
	array[index + 3] = (uint8_t)(val >> 24);
}


uint32_t memory_readUInt32LitEnd(const uint8_t * const buf, uint16_t index)
{
	uint32_t val;
	val = (uint32_t)buf[index];    					// lsb (low) byte last
	val |= (uint32_t)(buf[index + 1] << 8);   		// lsb (low) byte last
	val |= (uint32_t)(buf[index + 2] << 16);  		// lsb (low) byte last
	val |= (uint32_t)(buf[index + 3] << 24);   		// msb (high) byte first
	return val;
}