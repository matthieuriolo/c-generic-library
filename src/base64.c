#include "base64.h"

const char* base64_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/*
http://tools.ietf.org/html/rfc4648#section-4
openssl does not create a base64 after this rfc!
*/
char* base64_encode(const void* data, size_t length/*, size_t lineBreaks*/) {
	size_t len = (((length + 2) / 3) * 4);
	
	//len += len / lineBreaks;
	
	char* buffer = (char*)malloc(sizeof(char)*(len+1));
	buffer[len-1] = '\0';
	
	size_t i;
	size_t pos = 0;
	for(i=0;i<len;i+=4) {
		char tmp[] = {0,0,0};
		
		memcpy(tmp, data+pos, length-pos > 3 ? 3 : length-pos);
		
		buffer[i] = base64_characters[tmp[0] >> 2];
		buffer[i+1] = base64_characters[((tmp[0] & 0x03)<<4) | (tmp[1]>>4)];
		buffer[i+2] = base64_characters[((tmp[1] & 0x0F)<<2) | (tmp[2]>>4)];
		buffer[i+3] = base64_characters[(tmp[2] & 0x3F)];
		
		pos+=3;
	}
	
	i=3-(length%3);
	while(i) {
		buffer[len-i]='=';
		i--;
	}
	
	return buffer;
}

void* base64_decode(const char* str, size_t* len) {
	size_t length = strlen(str), i, x, a;
	*len = ((length + 3) /4)*3;
	
	
	//remove paddings
	for(i=0;i<2;i++)
		if(str[length-1]=='=') {
			length--;
			(*len)--;
		}else
			break;
	
	
	char* buffer = malloc(*len);
	for(i=0;i<length;i+=3) {
		size_t pos = (i/3)*4;
		char tmp[4];
		
		//find the corresponding letter
		for(a=0;a<4;a++) {
			for(x=0;x<64;x++) {
				if(str[pos+a]==base64_characters[x]) {
					tmp[a] = x;
					break;
				}
			}
		}
		
		
		//remap it
		buffer[i] = (tmp[0] << 2) | (tmp[1] >> 4);
		buffer[i+1] = (tmp[1]<< 4) | (tmp[2] >> 2);
		buffer[i+2] = (tmp[2] << 6) | tmp[3];
	}
	
	
	return buffer;
}

#endif