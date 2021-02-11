#include "./board/board.h"

int main(void)
{
	Board *board = create_board();
	Position *from = create_position(1, 1);
	Position *to = create_position(2, 1);
	move_piece(board, from, to);
	printf("\n\n");
	print_condenced_hex_board(board);
	printf("\n\n");
	Piece p = get_piece(board, 0, 0);
	
	printf("0x%0X -> ", p);
	print_chess_piece(p);
	printf("\n");
	
	Position *from_2 = create_position(7, 1);
	Position *to_2 = create_position(5, 0);
	Piece p_2 = get_piece(board, from_2->row, from_2->column);

	printf("0x%0X -> ", p_2);
	print_chess_piece(p_2);
	printf("\n");
	move_piece(board, from_2, to_2);
	print_condenced_hex_board(board);

	printf("0x%0X : \n", get_piece(board, from_2->row, from_2->column));

	free(board);
}
