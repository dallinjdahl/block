#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define BBITS 8
#define BSIZE (1<<BBITS)

#define CELL 1
char *bname = "block.img";
uint16_t block[BSIZE] = {0};
uint8_t dirty = 0;
uint32_t bnum = 0;
int bfd;

void bload(int i) {
	memset(block, 0, BSIZE<<CELL);
	lseek(bfd, (i<<BBITS)<<CELL, SEEK_SET);
	read(bfd, block, BSIZE<<CELL);
	bnum = i;
}

void bopen() {
	bfd = open(bname, O_RDWR | O_CREAT);
	bload(bnum);
}

void bcommit() {
	lseek(bfd, (bnum<<BBITS)<<CELL, SEEK_SET);
	write(bfd, block, BSIZE<<CELL);
	printf("writing block %d at %d\n", bnum, (bnum<<BBITS)<<CELL);
}

void bclose() {
	bcommit();
	close(bfd);
}

void bget(int i) {
	if(dirty) {
		bcommit();
		dirty = 0;
	}
	bload(i);
}

void dirt() {
	dirty = 1;
}
