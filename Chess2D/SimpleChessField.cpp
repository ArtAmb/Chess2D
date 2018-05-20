#include "SimpleChessField.h"


std::string SimpleChessField::getRowName()
{
	int row = getRow() + 1;
	std::string rowName = std::to_string(row);
	return rowName;
}

std::string SimpleChessField::getColumnName()
{
	CHESS_COLUMN column = getColumn();
	std::string columnName;

	switch (column)
	{
	case 0:
		columnName = "A";
		break;
	case 1:
		columnName = "B";
		break;
	case 2:
		columnName = "C";
		break;
	case 3:
		columnName = "D";
		break;
	case 4:
		columnName = "E";
		break;
	case 5:
		columnName = "F";
		break;
	case 6:
		columnName = "G";
		break;
	case 7:
		columnName = "H";
		break;

	}

	return columnName;
}
