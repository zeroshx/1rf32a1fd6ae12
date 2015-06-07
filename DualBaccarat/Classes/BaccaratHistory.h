#ifndef __BACCARAT_HISTORY_H__
#define __BACCARAT_HISTORY_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

#define LETTERBOARD_SIZE	Size(DESIGN_WIDTH, 80)
#define BASE_RESULT_COUNT	24
#define BOARD_WIDTH_COUNT	15
#define BOARD_HEIGHT_COUNT	6

enum class GameResult
{
	PLAYER,
	PLAYER_PAIR_P,
	PLAYER_PAIR_B,
	PLAYER_PAIR_PB,
	BANKER,
	BANKER_PAIR_P,
	BANKER_PAIR_B,
	BANKER_PAIR_PB,
	TIE,
	TIE_PAIR_P,
	TIE_PAIR_B,
	TIE_PAIR_PB
};

class BaccaratHistory : public Layer
{
public:

	BaccaratHistory();
	~BaccaratHistory();

	static BaccaratHistory* create();
	virtual bool init();
	void push(GameResult result);
	void show();
	void hide();
	void reset();
	
private:

	

private:
	
	bool _isRunning;

	Sprite *_bg_baseResult;
	Sprite *_bg_gameResult1Depth;
	Sprite *_bg_gameResult2Depth;
	Sprite *_bg_gameResult3Depth;
	Sprite *_bg_gameResult4Depth;
	
	Vec2 _current;
	int _baseCount;
	GameResult _baseResult[BASE_RESULT_COUNT];
	GameResult _gameResult[BOARD_WIDTH_COUNT][BOARD_HEIGHT_COUNT];
	
};

#endif // __BACCARAT_HISTORY_H__
