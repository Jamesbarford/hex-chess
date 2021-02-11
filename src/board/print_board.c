#include "board.h"

void print_y_axis()
{
	printf("\tA\tB\tC\tD\tE\tF\tG\tH\n");
}

void print_condenced_hex_board(Board *board)
{
	printf("     76543210\n\n");
	for (uint8_t i = 0; i < DIMENSIONS; ++i)
		printf("%d  0x%08X\n", i, board->row[i]);
}

void print_hex_board(Board *board)
{
	print_y_axis();
	for (uint8_t row = 0; row < DIMENSIONS; ++row)
	{
		printf("%d \t", row + 1);
		for (uint8_t column = 0; column < DIMENSIONS; ++column)
		{
			Piece piece = get_piece(board, row, DIMENSIONS - (column + 1));
			piece == 0 ? printf("\t") : printf("0x%X\t", piece);
		}
		printf("\n\n");
	}
}

void pretty_print_board(Board *board)
{
	print_y_axis();
	char buf[4];
	memset(buf, '\0', 4);
	for (uint8_t row = 0; row < DIMENSIONS; ++row)
	{
		printf("%d \t", row + 1);
		for (uint8_t column = 0; column < DIMENSIONS; ++column)
		{
			Piece piece = get_piece(board, row, DIMENSIONS - (column + 1));
			print_chess_piece(piece);
			printf("\t");
			buf[0] = '\0';
		}
		printf("\n\n");
	}
}

void print_chess_piece(Piece piece)
{
	switch (piece)
	{
	case 0x1:
		printf("%s", "♙");
		break;
	case 0x2:
		printf("%s", "♘");
		break;
	case 0x3:
		printf("%s", "♗");
		break;
	case 0x4:
		printf("%s", "♖");
		break;
	case 0x5:
		printf("%s", "♕");
		break;
	case 0x6:
		printf("%s", "♔");
		break;

	case 0x7:
		printf("%s", "♟");
		break;
	case 0x8:
		printf("%s", "♞");
		break;
	case 0x9:
		printf("%s", "♝");
		break;
	case 0xA:
		printf("%s", "♜");
		break;
	case 0xB:
		printf("%s", "♛");
		break;
	case 0xC:
		printf("%s", "♚");
		break;

	default:
		printf("%s", " ");
		break;
	}
}
