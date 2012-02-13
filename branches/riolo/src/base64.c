#include "base64.h"

const char* base64_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const void* data, size_t length) {
	size_t len = base64_encode_length(length);
	
	char* buffer = (char*)malloc(sizeof(char)*(len+1));
	buffer[len] = '\0';
	//memcpy(buffer + (len-2), "==", 2);
	
	size_t i;
	size_t pos = 0;
	for(i=0;i<len;i+=4) {
		char tmp[] = {0,0,0};
		
		memcpy(tmp, data+pos, length-pos > 3 ? 3 : length-pos);
		/*
		buffer[i] = base64_characters[(tmp[0] >> 2) & 0x0F];
		buffer[i+1] = base64_characters[((tmp[0] & 0x03)<<4) | (tmp[1]>>4)];
		buffer[i+2] = base64_characters[((tmp[1] & 0x0F)<<2) | (tmp[2]>>4)];
		buffer[i+3] = base64_characters[(tmp[2] & 0x3F)];
		*/
		
		buffer[i] = base64_characters[(tmp[0] >> 2) & 0x3F];
		buffer[i+1] = base64_characters[((tmp[0]<<4) & 0x30) | ((tmp[1]>>4) & 0x0F)];
		buffer[i+2] = base64_characters[((tmp[1] << 2) & 0x3C) | ((tmp[2]>>6) & 0x03)];
		buffer[i+3] = base64_characters[(tmp[2] & 0x3F)];
		
		pos+=3;
	}
	
	i = (3 - (length % 3)) % 3;
	while(i) {
		buffer[len-i]='=';
		i--;
	}
	
	return buffer;
}


size_t base64_encode_length(size_t length) {
	return (((length + 2) / 3) * 4);
}

size_t base64_decode_length(const char* str, size_t *length) {
	*length = strlen(str);
	size_t len = ((*length + 3) / 4)*3;/*, i;
	
	/*printf("expected length for encoding: %s %lu %lu\n", str, len, *length);
	
	//remove paddings
	for(i=0;i<2;i++)
		if(str[*length-1]=='=') {
			(*length)--;
			len--;
		}else
			break;
	printf("expected length for encoding: %s %lu %lu\n", str, len, *length);*/
	return len;
}

void* base64_decode(const char* str, size_t* len) {
	size_t length, i, a;
	*len = base64_decode_length(str, &length);
	
	size_t paddings = 0;
	
	char* buffer = (char*)malloc(*len*sizeof(char));
	for(i=0; i<length; i+=3) {
		size_t pos = (i/3)*4;
		char tmp[4] = {0,0,0,0};
		
		//find the corresponding letter
		for(a=0;a<4;a++) {
			if(str[pos+a] != '=') {
				char* val = strchr(base64_characters, str[pos+a]);
				if(val == NULL) {
					free(buffer);
					return NULL;
				}
			
				tmp[a] = val - base64_characters;
			}else
				paddings++;
		}
		
		//remap it
		
		buffer[i] = (tmp[0] << 2) | (tmp[1] >> 4);
		buffer[i+1] = (tmp[1]<< 4) | (tmp[2] >> 2);
		buffer[i+2] = (tmp[2] << 6) | tmp[3];
	}
	
	//printf("detected paddings %lu\n", paddings);
	*len = *len - paddings;
	buffer = realloc(buffer, *len);
	
	return buffer;
}
