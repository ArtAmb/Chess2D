#pragma once
#include "ChessEnums.h"

class SimpleChessField {
	CHESS_ROW row;
	CHESS_COLUMN column;
public:
	SimpleChessField(CHESS_ROW row, CHESS_COLUMN column) : row(row), column(column) {}
	CHESS_ROW getRow() { return row; }
	CHESS_COLUMN getColumn() { return column; }

	bool operator==(SimpleChessField f) {
		return f.getColumn() == column && f.getRow() == row;
	}
};