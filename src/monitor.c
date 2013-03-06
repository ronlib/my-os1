#include "monitor.h"

#define MAX_WIDTH 80
#define MAX_LENGTH 25

#define CHAR_BACKSPACE	0x08
#define CHAR_TAB		0x09
#define TAB_WIDTH		4


const u16int CONTROLLER_COMMAND_PORT = 0x3D4;
const u16int CONTROLLER_DATA_PORT = 0x3D5;

const u8int COLOR_BLACK = 0;
const u8int COLOR_WHITE = 15;

const u8int BACKGROUND_SHIFT = 4;
const u8int TEXT_SHIFT = 0;

#define SCREEN_BUFFER 0xB8000

u16int * video_memory = (u16int *)SCREEN_BUFFER;

u8int x_pos = 0, y_pos = 0;

static void move_cursor()
{
	u16int cursorLocation = y_pos * MAX_WIDTH + x_pos;

	outb(CONTROLLER_COMMAND_PORT	, 14);
	outb(CONTROLLER_DATA_PORT, cursorLocation >> 8);
	
	outb(CONTROLLER_COMMAND_PORT, 14);
	outb(CONTROLLER_DATA_PORT, cursorLocation & 0xFF);
}


static void scroll()
{
	if (SCREEN_HEIGHT > y_pos)
	{
		return;
	}
	
	// Setting color settings
	u16int blank = 0x20 | getColorScheme(BLACK, WHITE) << 8;	


	u16int i;
	
	// Moving all lines up if necessary
	for (i = 0 ; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH ; ++i)
	{
		video_memory[i] = video_memory[i + SCREEN_WIDTH];
	}
	
	for (i = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH ; i < SCREEN_HEIGHT * SCREEN_WIDTH ; ++i)
	{
		video_memory[i] = blank;
	}
	
	y_pos = SCREEN_HEIGHT - 1;
	
	return;
	
}

u8int getColorScheme(u8int background, u8int foreground)
{
	return (background & 0x0F) << 4 | (foreground & 0x0F);
}

void monitor_put(char c)
{	
	u8int colorScheme = getColorScheme(BLACK, WHITE);
	

	if (CHAR_BACKSPACE == c && 0 < x_pos)
	{
		--x_pos;
	}


	// We don't support tab character
//	else if (CHAR_TAB == c)
//	{
//
//	}

	else if ('\n' == c)
	{
		x_pos = 0;
		++y_pos;

	}

	else if (' ' <= c)
	{
		video_memory[getVideoBufferLocation(x_pos, y_pos)] = (colorScheme << 8) | c;
		++x_pos;
	}

	
	if (MAX_WIDTH <= x_pos)
	{		
		x_pos = 0;
		++y_pos;
	}

	scroll();

	move_cursor();

}

u16int getVideoBufferLocation(u8int x, u8int y)
{
	return (y * MAX_WIDTH) + x;
}

void monitor_clear()
{
	u8int colorScheme = getColorScheme(BLACK, WHITE);
	u16int blank = colorScheme << 8 | ' ';

	int i;

	for (i = 0 ; i < MAX_LENGTH * MAX_WIDTH ; ++i)
	{
		video_memory[i] = blank;
	}

	x_pos = y_pos = 0;

	move_cursor();
}

void displayString(char * str)
{
	int i = 0;
	
	while (0 != str[i])
	{
		monitor_put(str[i]);
		++i;
	}
}

void monitor_write_hex(u32int n)
{
	monitor_put('0');
	monitor_put('x');
	do
	{
		if (n % 16 > 9)
		{
			monitor_put((n % 16) - 10 + 'A');
		}
		else
		{
			monitor_put((n % 16) + '0');
		}
		
		n = n >> 4;
		
	} while (n > 0);
}

void monitor_write_dec(u32int n)
{
	do
	{
		monitor_put((n % 10) + '0');
		n = n / 10;

	} while (n > 0);
}
