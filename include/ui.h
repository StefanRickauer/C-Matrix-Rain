#ifndef _UI_H
#define _UI_H

// Window size

#define MAXX 160 	//width
#define MAXY 50		//tall

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

#include <stdbool.h>

typedef struct {
	char char_value;
	int intensity;
} cell;

// extern - defined elsewhere
extern cell matrix[MAXX][MAXY];

// prototypes
bool init_ui();
void cleanup_ui();
void show_matrix();

#endif
