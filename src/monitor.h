#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"


#define BLACK 0
#define WHITE 15

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void monitor_put(char c);

void monitor_clear();

void monitor_write(char *c);

u8int getColorScheme(u8int backgroun, u8int foreground);

void monitor_put(char c);

u16int getVideoBufferLocation(u8int x, u8int y);

void displayString(char * str);

#endif // MONITOR_H
