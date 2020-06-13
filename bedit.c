#include <stdio.h>
#include "block.h"

#define LINE (line+lix)

char line[256] = {0};
uint8_t lix = 0;
uint8_t eof = 0;
uint8_t eol = 0;

void eatspace() {
	while(*LINE == ' ' || *LINE == '\t') {
		lix++;
	}
}

uint32_t atoi() {
	if(*LINE == ' ' || *LINE == '\t') {
		eatspace();
	}
	uint32_t res = 0;
	uint8_t dig = 0;
	while (('0' <= *LINE && *LINE <= '9') ||
			('a' <= *LINE && *LINE <= 'f')) {
		res <<= 4;
		dig = *LINE - '0';
		if(dig > 9) {
			dig -= 'a'-'9'-1;
		}
		res += dig;
		lix++;
	}
	if(*LINE == 0) {
		eol = 1;
	}
	return res;
}

void rline() {
	int c = 0;
	lix = 1;
	eol = 0;
	for(uint8_t i = 0; i < 255; i++) {
		c = getchar();
		if(c == EOF || c == '\n') {
			line[i] = 0;
			if(c == EOF) {
				eof = 1;
			}
			return;
		}
		line[i] = c;
	}

	while(1) {
		c = getchar();
		if(c == EOF || c == '\n') {
			return;
		}
	}
}

void loadblock() {
	uint32_t i = atoi();
	bget(i);
}

void hexblock() {
	for(int i = 0; i < 16; i++) {
		printf("%x: ", i);
		for(int j = 0; j < 16; j++) {
			printf("%04x ", block[(i<<4)+j]);
		}
		printf("\n");
	}
	fflush(stdout);
}

void editblock() {
	dirt();
	uint16_t addr = atoi();
	while(!eol) {
		uint16_t val = atoi();
		block[addr++] = val;
	}
}

void xtrcpy(char *s, char *d, uint16_t n) {
	for(int i = 0; i < n; i++) {
		if(*s == 0) {
			return;
		}
		*(d++) = *(s++);
	}
}

void asciiblock() {
	dirt();
	uint16_t addr = atoi();
	eatspace();
	xtrcpy(LINE, (char *)(block+addr), 256-lix);
}

void printblock() {
	char x = 0;
	for(int i = 0; i < 16; i++) {
		printf("%x: ", i);
		for(int j = 0; j < 32; j++) {
			x = ((char *)block)[(i<<5)+j];
			if(x < 32 || x > 126) {
				printf(".");
				continue;
			}
			printf("%c", x);
		}
		printf("\n");
	}
	fflush(stdout);

}

int main(int argc, char **argv) {
	bopen();
	while(!eof) {
		printf(">");
		fflush(stdout);
		rline();
		switch(*line) {
		case 'q': bclose(); return 0;
		case 'b': loadblock(); break;
		case 'x': editblock(); break;
		case 'i': asciiblock(); break;
		case 'p': printblock(); break;
		case 'h': hexblock(); break;
		default: printf("?\n");
		}
	}
	bclose();
	printf("\n");
	return 1;
}

