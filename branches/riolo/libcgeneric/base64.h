#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#ifndef __BASE64_H__
#define __BASE64_H__

/**
 * @fn char* base64_encode(void*, size_t)
 * @param data is some binary data in the memory
 * @param length is the length in bytes for the data
 * @return an ascii string
 *
 * @brief converts any kind of data to base64
 */
char* base64_encode(const void* data, size_t length);



/**
 * @fn void* base64_decode(const char*, size_t*)
 * @param const char* is a base64 representation as c-string
 * @param length will be reset be the function to the length of the data
 * @return the decoded data
 *
 * @brief encodes a string into the binary representation
 */
void* base64_decode(const char* str, size_t* len);

#endif