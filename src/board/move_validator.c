#include "board.h"

Bool is_king(Piece piece)
{
	return piece == 0x6 || piece == 0xC;
}

Bool is_taking_piece(Piece piece, Piece next_piece)
{
	CellType intent = get_cell_type(next_piece);
	CellType current = get_cell_type(piece);

	if (current == intent)
		return False;

	switch (intent)
	{
	case Vacant:
	case OutOfBounds:
		return False;

	case Colourless:
	case Colour:
		return True;

	default:
		return False;
	}
}

Bool is_start_postion(Piece piece, Position *position)
{
	switch (piece)
	{
	case 0x1:
		return position->row == 1 && (position->column >= 0 && position->column <= 7);
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
		return False;

	case 0x7:
		return position->row == 6 && position->column >= 0 && position->column <= 7;
	case 0x8:
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return False;

	default:
		return False;
	}
}

/**
 *
 * PAWN
 *
 */
Bool is_valid_pawn_move(Board *board, Piece piece, Position *from, Position *to)
{
	Bool valid_row;
	Bool valid_column;
	CellType type = get_cell_type(piece);
	Piece next_piece = get_piece(board, to->row, to->column);

	if (is_start_postion(piece, from))
	{
		valid_row = to->row == get_direction(type, from->row, 1) || get_direction(type, from->row, 2);
		valid_column = from->column == to->column;
		return valid_row && valid_column;
	}
	else if (to->row == get_direction(type, from->row, 1))
	{
		if (is_taking_piece(piece, next_piece))
			return from->column == from->column + 1 || from->column == from->column - 1;
		else
			return from->column == to->column;
	}

	fprintf(stderr, "Piece being moved is not a pawn: 0x%X, valid pawns are 0x1 and 0x7", piece);
	return False;
}

/**
 *
 * KNIGHT 
 *
 * 0x0F0F0
 * 0xF000F
 * 0x00200
 * 0xF000F
 * 0x0F0F0
 * */
Bool is_valid_knight_move(Position *from, Position *to)
{
	if (to->row == from->row + 1 || to->row == from->row - 1)
		if (to->column == from->column + 2 || to -> column == from->column - 2)
			return True;

	if (to->row == from->row + 2 || to->row == from->row - 2)
		if (to->column == from->column - 1 || to->column == from->column + 1)
			return True;

	return False;
}

/**
 *
 * BISHOP
 *
 * y - y1 = m(x - x1)
 *
 * y - y1
 * ------ = 1
 * x - x1
 *
 * 0xAAAAA
 * 0x00000
 * 0x00F00
 * 0x00000
 * 0x0FFFF
 * */
Bool is_valid_bishop_move(Board *board, Position *from, Position *to)
{
	uint8_t next_row, next_column;
	Piece next_piece;
	CellType next_type;

	if (abs((from->row - to->row) / (from->column - to->column)) != 1)
		return False;

	for (uint8_t i = 0; i < abs(from->row - to->row) - 1; ++i)
	{
		next_column = from->column > to->column ? from->column - i : from->column + i;
		next_row = from->row > to->row ? from->row - i : from->row + i;

		next_piece = get_piece(board, next_row, next_column);
		next_type = get_cell_type(next_piece);

		if (next_type != Vacant)
			return False;
	}

	return True;
}

/*
 * ROOK
 * */
Bool is_valid_rook_move(Board *board, Position *from, Position *to)
{
	uint8_t next_row, next_column;
	Piece next_piece;
	CellType next_type;

	// vertical
	if (from->column == to->column)
	{
		for (int8_t i = 0; i < abs(from->row - to->row); ++i)
		{
			next_row = from->row > to->row ? from->row - i : from->row + i;
			next_piece = get_piece(board, next_row, to->column);
			next_type = get_cell_type(next_piece);

			if (next_type != Vacant)
				return False;
		}
	}
	// horizontal
	else if (from->row == to->row)
	{
		for (int8_t i = 0; i < abs(from->column - to->column); ++i)
		{
			next_column = from->column > to->column ? from->column - i : from->column + i;
			next_piece = get_piece(board, to->row, next_column);
			next_type = get_cell_type(next_piece);

			if (next_type != Vacant)
				return False;
		}
	}

	return False;
}

/**
 *
 * QUEEN
 *
 * essentially can move like a bishop or castle
 * */
Bool is_valid_queen_move(Board *board, Position *from, Position *to)
{
	return is_valid_rook_move(board, from, to) || is_valid_bishop_move(board, from, to);
}


Bool is_moveable(Board *board, Position *from, Position *to)
{
	Piece current_space = get_piece(board, from->row, from->column);
	Piece next_space = get_piece(board, to->row, to->column);
	CellType current_type = get_cell_type(current_space);
	CellType next_type = get_cell_type(next_space);

	if (next_space == current_space)
		return False;

	// cannot take a king
	if (is_king(next_space))
		return False;

	// cannot move onto a cell with the same colour as the current piece.
	if (current_type == next_type)
		return False;

	return True;
}

Bool is_valid_move(Board *board, Piece piece, Position *from, Position *to)
{
	if (!is_moveable(board, from, to))
		return False;

	switch (piece)
	{
	case 0x1:
	case 0x7:
		return is_valid_pawn_move(board, piece, from, to);

	case 0x2:
	case 0x8:
		return is_valid_knight_move(from, to);

	case 0x3:
	case 0x9:
		return is_valid_bishop_move(board, from, to);

	case 0x4:
	case 0xA:
		return is_valid_rook_move(board, from, to);

	case 0x5:
	case 0xB:
		return is_valid_queen_move(board, from, to);

	case 0x6:
	case 0xC:
		return False;

	default:
		return False;
	}
}

