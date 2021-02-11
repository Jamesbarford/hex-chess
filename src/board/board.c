#include "board.h"

Board *create_board()
{
	Board *board = (Board *)malloc(sizeof(uint32_t) * DIMENSIONS);
	if (board == NULL)
	{
		errno = ENOMEM;
		fprintf(stderr, "Failed to allocate memory for 'Board\n'");
		exit(EXIT_FAILURE);
	}

	board->row[0] = 0x42365324;
	board->row[1] = 0x11111111;
	board->row[2] = 0x00000000;
	board->row[3] = 0x00000000;
	board->row[4] = 0x00000000;
	board->row[5] = 0x00000000;
	board->row[6] = 0x77777777;
	board->row[7] = 0xA89BC98A;

	return board;
}

Piece get_piece(Board *board, int8_t row, int8_t column)
{
	if (invalid_command(row, column))
	{
		fprintf(stderr, "Invalid row, must be between 1-8, received: %d \n'", row);
		return INVALID_PIECE;
	}

	return (board->row[row] >> (column << 2) & 0xF);
}

Bool remove_piece(Board *board, int8_t row, int8_t column)
{
	if (invalid_command(row, column))
	{
		fprintf(stderr, "Invalid row, must be between 1-8, received: %d \n'", row);
		return False;
	}

	board->row[row] &= ~((0xFFFFFFFF >> 0x1C) << (column << 2));

	return True;
}

Bool move_piece(Board *board, Position *from, Position *to)
{
	Piece piece = get_piece(board, from->row, from->column);
	Piece next_piece = get_piece(board, to->row, to->column);

	if (!is_valid_move(board, piece, from, to) || piece == -1)
	{
		fprintf(stderr, "Invalid move of piece: %08X, from row: %d, column :%d to -> row: %d, column %d\n", piece, from->row, from->column, to->row, to->column);
		return False;
	}

	// Some scoring? Taking a piece!!!
	if (is_taking_piece(piece, next_piece))
		remove_piece(board, to->row, to->column);

	board->row[to->row] |= piece << ((to->column) << 2);
	remove_piece(board, from->row, from->column);

	return True;
}

CellType get_cell_type(Piece piece)
{
	switch (piece)
	{
	case 0x0:
		return Vacant;

	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
		return Colourless;

	case 0x7:
	case 0x8:
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return Colour;

	default:
		return OutOfBounds;
	}
}
