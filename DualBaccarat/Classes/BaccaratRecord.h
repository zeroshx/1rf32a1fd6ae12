#ifndef __BACCARAT_RECORD_H__
#define __BACCARAT_RECORD_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "PublicApi.h"
#include "BaccaratRecordItem.h"
#include "BaccaratRecordScoreboardItem.h"

USING_NS_CC;

#define PROTOTYPE_LENGTH	32

#define BASE_WIDTH_LENGTH	60
#define BASE_HEIGHT_LENGTH	6
#define BASE_FRAME_SIZE		Size(1380, 360)
#define BASE_CONTENT_SIZE	Size(3600, 360)

#define DIV_FRAME_SIZE		Size(1380, 180)
#define DIV_CONTENT_SIZE	Size(1800, 180)

#define DIV2_FRAME_SIZE		Size(780, 180)
#define DIV2_CONTENT_SIZE	Size(1800, 180)

enum class RecordType
{
	PROTOTYPE,
	BASE,
	DIVINATION1TH,
	DIVINATION2ND,
	DIVINATION3RD,
	NEXT_DIV1TH,
	NEXT_DIV2ND,
	NEXT_DIV3RD,
};

enum DIV_DEPTH
{
	FIRST = 1,
	SECOND = 2,
	THIRD = 3
};

enum SCORE_TYPE
{
	BANKER = 0,
	PLAYER = 1,
	TIE = 2,
	BANKER_PAIR = 3,
	PLAYER_PAIR = 4,
	TOTAL = 5
};

class BaccaratRecord : public cocos2d::Layer
{
public:

	enum class MODULE_STATE
	{
		IDLE,
		START,
		DONE
	};
  
	BaccaratRecord();
	~BaccaratRecord();

	static BaccaratRecord* create();
	virtual bool init();

	void push(Winner winner, Pair pair);
	void show();
	void hide();
	void reset();
	void drawLatestRecord();	
	
private:

	void drawPrototype();
	void drawLatestPrototype();
	void drawBase();
	void drawLatestBase();
	void drawDivination(int depth);
	void drawLatestDivination(int depth);
	void drawNextRecord();
	void drawRecommendedItem();
	void updateScoreboard(Winner winner, Pair pair);

	void chartPrototype(Winner winner, Pair pair);
	void chartBase(Winner winner, Pair pair);
	void chartDivination(DIV_DEPTH depth);
	void chartNextRecord(Winner winner);
	void findRecommendedItem();
	Winner findNextConsecutiveItem(BaccaratRecordItem* lastItem, DIV_DEPTH depth);
	Winner findNextConsecutiveItem(DIV_DEPTH depth);

	const std::string getImageName(RecordType type, Winner winner, Pair pair, Continuation continuity);
	const std::string getStringForWinner(Winner winner);
	const std::string getStringForPair(Pair pair);
	const std::string getStringForContinuity(Continuation continuity);

	void onFrameTriggered(Ref *pSender);
	void onFrameAnimCompleted();
	
	BaccaratRecordItem _prototype[PROTOTYPE_LENGTH];
	BaccaratRecordItem *_lastPrototype;

	BaccaratRecordItem _base[BASE_WIDTH_LENGTH][BASE_HEIGHT_LENGTH];
	BaccaratRecordItem *_lastBase;

	BaccaratRecordItem _divination[3][BASE_WIDTH_LENGTH][BASE_HEIGHT_LENGTH];
	BaccaratRecordItem *_lastDivination[3];

	BaccaratRecordItem _nextRecord[2][3];

	BaccaratRecordItem _recommend;

	int _scoreboard[6];
	
	Sprite *_bg_prototype;

	Sprite *_bg_boneFrame;
	Sprite *_bg_base;
	Sprite *_bg_divination[3];
	Sprite *_bg_nextRecord;
	Sprite *_bg_recommend;

	Sprite *_bg_scoreBoard;
	ScoreboardItem *_scoreType[6];

	MODULE_STATE _state;
};

#endif // __BACCARAT_RECORD_H__
