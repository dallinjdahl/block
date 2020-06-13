# block
Simple library for block access to files in C, with sample implementation.  It basically functions as a form of primitive memory mapped file access, one block at a time.  This allows for easy manipulation of bytes in memory that are automatically transferred to disk when you leave the block.  The entire library is in the single header file `block.h`, and is intended to be customized by the user to fit their implementation preferences.  See the following table for customization tips.
block.h macro/variable | Description
--- | ---
BBITS | defines the left-shift amount for the block size.  In other words, with a value of x, the block size will be 2^x cells. (default `8` for 256 cell blocks)
CELL | defines the left-shift amount for cell size, i.e. for a value x, the cell size will be 2^x bytes. (default `1`, for 16bit cells)
bname | defines the name of the block file to use (default `"block.img"`)
bnum | sets initial block number (default `0`)

## bedit.c
This is a basic ed-style block editor a la forth in C.  Only for demonstration and testing.
### Commands
Command | Description
--- | ---
b*xx* | load block *xx*
x*xx xxxx xxxx...* | insert hexadecimal numbers (*xxxx xxxx...*) at *xx* in current block
i*xx ccccc...* | insert ascii text *ccccc...* until end of line at *xx* in current block
p | print all ascii-printable characters in current block with `.` as placeholder for non-ascii
h | dump block as hexadecimal digits
q | quit

