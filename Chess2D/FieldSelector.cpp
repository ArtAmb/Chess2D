#include "FieldSelector.h"

void FieldSelector::move(int x, int y)
{
	int intX = int(this->row);
	int intY = int(this->column);

	if (intX + x > 7)
		this->row = (CHESS_ROW)7;
	else if (intX + x < 0)
		this->row = (CHESS_ROW)0;
	else
		row = (CHESS_ROW)(intX + x);

	if (intY + y > 7)
		this->column = (CHESS_COLUMN)7;
	else if (intY + y < 0)
		this->column = (CHESS_COLUMN)0;
	else
		column = (CHESS_COLUMN)(intY + y);

	std::cout << "ROW == " << row << ", COLUMN == " << column << std::endl;

}

void FieldSelector::unselect() {
	selected = false;
	savedPiece->reset();
	savedPiece = NULL;
}

void FieldSelector::absoluteMove(CHESS_ROW x, CHESS_COLUMN y)
{
	this->row = x;
	this->column = y;
}

void FieldSelector::update(SimpleChessField field)
{
	row = field.getRow();
	column = field.getColumn();
}
