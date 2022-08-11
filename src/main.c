#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include "ui.h"
#include "matrix.h"
#include "error_procedure.h"

#define ITERATIONS 300
#define REFRESH_DELAY 50000L

int main(void) {
	if(!init_ui())
		errExit("init_ui");

	matrix_init();

	for(int i = 0; i < ITERATIONS; i++) {
		matrix_update();
		show_matrix();
		usleep(REFRESH_DELAY);
	}

	cleanup_ui();

	return EXIT_SUCCESS;
}
