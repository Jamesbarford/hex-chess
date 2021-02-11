#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define invalid_command(row, column) (row < 0 || row > 8 || column > 8 || column < 0)

typedef struct Position
{
	int8_t row;
	int8_t column;
} Position;

Position *create_position(int8_t row, int8_t column);

#endif
