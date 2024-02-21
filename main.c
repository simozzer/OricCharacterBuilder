//
// TEST_4
//
// This is a "HELLO WORLD" sample using
// an assembly code routine to display
// the message
//
#include "stdlib.h"
#include "keys.s"

int cursor_x = 2;
int cursor_y = 1;

// Declare the assembly code function
void AdvancedPrint(char x_pos,char y_pos,const char *ptr_message);
void InitializeCharacters();
void UninvertChar(char x_pos, char y_pos);
void InvertChar(char x_pos, char y_pos);


// Stop display of the flashing cursor
void disableCursor()
{
	char *b = (char *)0x26a;
	*b = 42;
}

void printDataForSelectedPixel() 
{
	int selectedCharCol = (cursor_x -2)/6;
	int selectedCharRow = (cursor_y-2)/8;
	int asciiCode = (selectedCharRow*3) + selectedCharCol + 35;

	char str[7];
	sprintf(str,"Col: %d\n", selectedCharCol);
	AdvancedPrint(22,10,str);
	sprintf(str,"Row: %d\n", selectedCharRow);
	AdvancedPrint(22,11,str);
	sprintf(str,"Chr: %d\n",asciiCode);
	AdvancedPrint(22,12,str);
	printBitmapData(2,27,asciiCode);
}

void printLargeCharacterBitmap(char x_pos, char y_pos, unsigned char character)
{
	int x,y;
	unsigned char **c;
	unsigned char mask;
	unsigned char ch;
	
	for (y=0; y < 8; y++){
		// retrieve the byte for line y of the character bitmap data
		c = (unsigned char**)(0xb400 + (character * 8) + y);
		ch = (unsigned char)*c;
		mask = 32;
		for(x=1; x <7; x++) {
			if (ch & mask) {
				AdvancedPrint(x-1+x_pos,y+y_pos,"\"");
			} else {
				AdvancedPrint(x-1+x_pos,y+y_pos,"!");
			}
			mask = mask >> 1;
			
		}
	}
}

void printBitmapData(char x_pos, char y_pos, unsigned char character) 
{
	char str[38] = "                                      ";
	int y;
	unsigned char **c;
	unsigned char ch[8];
	
	for (y=0; y < 8; y++){
		// retrieve the byte for line y of the character bitmap data
		c = (unsigned char**)(0xb400 + (character * 8) + y);
		ch[y] = (unsigned char)*c;
	}	
	sprintf(str, "ASCII %d = %d,%d,%d,%d,%d,%d,%d,%d\n", character, ch[0], ch[1], ch[2], ch[3], ch[4], ch[5], ch[6], ch[7]);
	AdvancedPrint(x_pos,y_pos,str);
}

void setCursorXPos(unsigned char x_pos)
{
	unsigned char *m = (unsigned char*)CURCOL;
	*m = x_pos;
	cursor_x = x_pos;
}

void setCursorYPos(unsigned char y_pos)
{
	unsigned char *m = (unsigned char*)CURROW;
	*m = y_pos;	
	cursor_y = y_pos;
}

void mainLoop()
{	
	char k = key();
	int done = 0;

	setCursorYPos(1);
	setCursorXPos(2);
	InvertChar(cursor_x, cursor_y);

	while (!done) {
		k = key();

		switch(k) {
			case KEY_DOWN:
				UninvertChar(cursor_x, cursor_y);
				setCursorYPos(cursor_y+1);
				printDataForSelectedPixel();
				InvertChar(cursor_x, cursor_y);
				break;
			case KEY_UP:
				UninvertChar(cursor_x, cursor_y);
				setCursorYPos(cursor_y-1);
				printDataForSelectedPixel();
				InvertChar(cursor_x, cursor_y);
				break;
			case KEY_LEFT:
				UninvertChar(cursor_x, cursor_y);
				setCursorXPos(cursor_x-1);
				printDataForSelectedPixel();
				InvertChar(cursor_x, cursor_y);
				break;
			case KEY_RIGHT:
				UninvertChar(cursor_x, cursor_y);
				setCursorXPos(cursor_x+1);
				printDataForSelectedPixel();
				InvertChar(cursor_x, cursor_y);
				break;
			case KEY_Q:
				done = 1;
				cls();
				printf("goodbye");
			default:;
				
		}
	}
}

void main()
{
	cls();
	disableCursor();
	InitializeCharacters();
	
	printLargeCharacterBitmap(2,2,35);
	printLargeCharacterBitmap(8,2,36);
	printLargeCharacterBitmap(14,2,37);
	printLargeCharacterBitmap(2,10,38);
	printLargeCharacterBitmap(8,10,39);
	printLargeCharacterBitmap(14,10,40);
	printLargeCharacterBitmap(2,18,41);
	printLargeCharacterBitmap(8,18,42);
	printLargeCharacterBitmap(14,18,43);

	AdvancedPrint(22,2,"#$%");
	AdvancedPrint(22,3,"&'(");
	AdvancedPrint(22,4,")*+");

	printBitmapData(2,27,35);
	mainLoop();
}
