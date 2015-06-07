#ifndef __BACCARAT_RECORD_ITEM_H__
#define __BACCARAT_RECORD_ITEM_H__

#include "PublicApi.h"

enum class Pair
{
	NONE,
	PLAYER,
	BANKER,
	BOTH
};

enum class Continuation
{
	NONE,
	KEEP,
	INVERSE
};

class BaccaratRecordItem
{
public:

	BaccaratRecordItem();
	~BaccaratRecordItem();

	void reset();
	Winner reverseWinner();

	bool _isUsed;
	bool _isDrawn;
	int _x;
	int _y;
	int _row;
	int _column;
	int _number;
	int _columnCount;
	Continuation _continuation;
	Winner _winner;
	Pair _pair;
	BaccaratRecordItem *_root;
};

#endif // __BACCARAT_RECORD_ITEM_H__
