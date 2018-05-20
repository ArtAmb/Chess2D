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

	SimpleChessField move(int rowOff, int colOff) {
		int newRow = row + rowOff;
		int newCol = column + colOff;

		if (newRow < CHESS_ROW::R_1)
			newRow = CHESS_ROW::R_1;
		if (newRow > CHESS_ROW::R_8)
			newRow = CHESS_ROW::R_8;

		if (newCol < CHESS_COLUMN::C_A)
			newCol = CHESS_COLUMN::C_A;
		if (newCol > CHESS_COLUMN::C_H)
			newCol = CHESS_COLUMN::C_H;

		return SimpleChessField((CHESS_ROW)newRow, (CHESS_COLUMN)newCol);
	}

};