#ifndef PIECES_H
#define PIECES_H

#include <stdint.h>

#define get_direction(type, start, movement) (type == Colour ? start + movement : start - movement)

#define Colour 			1
#define Colourless 		2
#define Vacant 			3
#define OutOfBounds 	4

typedef uint8_t CellType;
typedef int8_t Piece;


#endif
