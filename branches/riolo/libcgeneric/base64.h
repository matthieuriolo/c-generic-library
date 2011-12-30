#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
http://tools.ietf.org/html/rfc4648#section-4
openssl does not create a base64 after this rfc!
this version of base64 does not include any linebreaks!
*/

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
 * @fn char* base64_encode_length(size_t)
 * @param length is the length in bytes for the data
 * @return length of the base64 representation
 *
 * @brief returns the length of the base64 representation
 */
size_t base64_encode_length(size_t length);

/**
 * @fn char* base64_decode_length(const char*, size_t*)
 * @param const char is a base64 string
 * @param length is the length of the string without the paddings (the = at the end)
 * @return length of the decoded data
 *
 * @brief returns the length of the decoded data
 */
size_t base64_decode_length(const char* str, size_t* length);


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