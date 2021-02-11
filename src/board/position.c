#include "position.h"

Position *create_position(int8_t row, int8_t column)
{ // Will not accept anything that is out of bounds, thus can assume anything that is `Movement` will be valid
	if (invalid_command(row, column))
	{
		fprintf(stderr, "Invalid row or column, must be within the bounds of the board. Received: column: %d, row :%d ", row, column);
		return NULL;
	}

	Position *position = malloc(sizeof(Position));

	if (position == NULL)
	{
		errno = ENOMEM;
		fprintf(stderr, "Failed to allocate memory for 'Movement\n'");
		exit(1);
	}

	position->row = row;
	position->column = column;

	return position;
}
