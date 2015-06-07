#include "BaccaratHistory.h"

BaccaratHistory::BaccaratHistory()
{		
	_baseCount = 0;
	_current = Vec2(0, 0);
}
BaccaratHistory::~BaccaratHistory()
{
}
BaccaratHistory* BaccaratHistory::create()
{
	BaccaratHistory *history = new (std::nothrow) BaccaratHistory();
	if (history && history->init())
	{
		history->autorelease();
		return history;
	}
	CC_SAFE_DELETE(history);
	return nullptr;
}
bool BaccaratHistory::init()
{
	setContentSize(_visibleSize);

	return true;
}
void BaccaratHistory::show()
{
	
}
void BaccaratHistory::hide()
{	
	
}
void BaccaratHistory::push(GameResult result)
{
	// 1. push in base result
	if (_baseCount < BASE_RESULT_COUNT - 1) {

		_baseResult[_baseCount] = result;
		_baseCount++;
	}
	else {

		for (int i = 1; i < BASE_RESULT_COUNT; i++)
		{
			_baseResult[i - 1] = _baseResult[i];
		}

		_baseResult[_baseCount] = result;
	}
}