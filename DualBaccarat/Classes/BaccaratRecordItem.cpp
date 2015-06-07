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
	_continuation = Continuation::NONE;
	_winner = Winner::NONE;
	_pair = Pair::NONE;
	_root = nullptr;
}
Winner BaccaratRecordItem::reverseWinner()
{
	if (_winner == Winner::BANKER) {

		return Winner::PLAYER;
	}
	else if (_winner == Winner::PLAYER) {

		return Winner::BANKER;
	}
	else {

		return Winner::NONE;
	}
}