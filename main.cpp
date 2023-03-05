
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

const char* filename = "listing_0038_many_register_mov";

const uint8 mov = 0b10001000;
char *regs[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", 
				 "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };

char *rm_mod11[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", 
					 "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };

char *rm_mod11[] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", 
					 "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };


void convertToBinary(uint8 n) {
	if (n > 1)
		convertToBinary(n >> 1);
	printf("%d", n & 1);
}


int main(void) {

	FILE* in_file = fopen(filename, "rb");
	if (!in_file) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	struct stat sb;
	if (stat(filename, &sb) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	uint8* file_contents = (uint8 *)malloc(sb.st_size);
	fread(file_contents, sb.st_size, 1, in_file);


	for(uint i=0; i<sb.st_size; i+=2) {

		uint8 opcode = file_contents[i] & 0b11111100;

		if(opcode == mov) {
			uint8 d = ( file_contents[i] >> 1 ) & 0b00000001;
			uint8 w = ( file_contents[i] >> 0 ) & 0b00000001;
			uint8 mod = ( file_contents[i + 1] >> 6 ) & 0b00000011;
			uint8 reg = ( file_contents[i + 1] >> 3 ) & 0b00000111;
			uint8 rm =  ( file_contents[i + 1] >> 0 ) & 0b00000111;

			char op[] = "mov";
			char *dst;
			char *src;

			if(mod == 0b11) {
				if(d == 1) {
					// reg = dst
					dst = regs_mod11[ (w << 3) + reg ];
					src = regs_mod11[ (w << 3) + rm ];
				}
				else {
					// reg = src
					src = regs_mod11[ (w << 3) + reg ];
					dst = regs_mod11[ (w << 3) + rm ];
				}
			}
			else if(mod == 0b11) {

			}



			printf("%s %s, %s\n", op, dst, src);
		}
	}
}

