#include "BaccaratRecordItem.h"

BaccaratRecordItem::BaccaratRecordItem()
{
	reset();
}
BaccaratRecordItem::~BaccaratRecordItem()
{
}
void BaccaratRecordItem::reset()
{
	_x = 0;
	_y = 0;
	_isUsed = false;
	_isDrawn = false;
	_row = 0;
	_column = 0;
	_columnCount = 0;
	_number = 0;
	_continuation = CONTINUATION::NONE;
	_winner = WINNER::NONE;
	_pair = PAIR::NONE;
	_root = nullptr;
}
WINNER BaccaratRecordItem::reverseWinner()
{
	if (_winner == WINNER::BANKER) {

		return WINNER::PLAYER;
	}
	else if (_winner == WINNER::PLAYER) {

		return WINNER::BANKER;
	}
	else {

		return WINNER::NONE;
	}
}