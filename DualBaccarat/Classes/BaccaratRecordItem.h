#ifndef __BACCARAT_RECORD_ITEM_H__
#define __BACCARAT_RECORD_ITEM_H__

#include "PublicApi.h"

class BaccaratRecordItem
{
public:

	BaccaratRecordItem();
	~BaccaratRecordItem();

	void reset();
	WINNER reverseWinner();

	bool _isUsed;
	bool _isDrawn;
	int _x;
	int _y;
	int _row;
	int _column;
	int _number;
	int _columnCount;
	CONTINUATION _continuation;
	WINNER _winner;
	PAIR _pair;
	BaccaratRecordItem *_root;
};

#endif // __BACCARAT_RECORD_ITEM_H__
