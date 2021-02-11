#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "chess_errors.h"
#include "position.h"
#include "../pieces/pieces.h"

#define True 1
#define False 0
#define DIMENSIONS 8

typedef uint8_t Bool;

typedef struct Board
{
	uint32_t row[DIMENSIONS];
} Board;

Board *create_board();
Piece get_piece(Board *board, int8_t row, int8_t column);
Bool remove_piece(Board *board, int8_t row, int8_t column);
Bool move_piece(Board *board, Position *from, Position *to);

CellType get_cell_type(Piece piece);
Bool is_valid_move(Board *board, Piece piece, Position *from, Position *to);
Bool is_taking_piece(Piece piece, Piece next_piece);

void print_chess_piece(Piece piece);
void print_hex_board(Board *board);
void print_condenced_hex_board(Board *board);
void pretty_print_board(Board *board);

#endif
