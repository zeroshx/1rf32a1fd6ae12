#ifndef __BACCARAT_RECORD_H__
#define __BACCARAT_RECORD_H__

#include "ui\CocosGUI.h"
#include "PublicApi.h"
#include "BaccaratRecordItem.h"
#include "BaccaratRecordScoreboardItem.h"
#include "BaccaratRecordDelegate.h"

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

class BaccaratRecord : public cocos2d::Layer
{
public:
	  
	BaccaratRecord();
	~BaccaratRecord();

	static BaccaratRecord* create();
	virtual bool init();

	void push(WINNER winner, PAIR pair);
	void show();
	void hide();
	void reset();
	void drawLatestRecord();
	void setDelegate(BaccaratRecordDelegate *brd);
	
private:

	void drawPrototype();
	void drawLatestPrototype();
	void drawBase();
	void drawLatestBase();
	void drawDivination(int depth);
	void drawLatestDivination(int depth);
	void drawNextRecord();
	void drawRecommendedItem();
	void updateScoreboard(WINNER winner, PAIR pair);

	void chartPrototype(WINNER winner, PAIR pair);
	void chartBase(WINNER winner, PAIR pair);
	void chartDivination(DIV_DEPTH depth);
	void chartNextRecord(WINNER winner);
	void findRecommendedItem();
	WINNER findNextConsecutiveItem(BaccaratRecordItem* lastItem, DIV_DEPTH depth);
	WINNER findNextConsecutiveItem(DIV_DEPTH depth);

	const std::string getImageName(RECORD_TYPE type, WINNER winner, PAIR pair, CONTINUATION continuity);
	const std::string getStringForWinner(WINNER winner);
	const std::string getStringForPair(PAIR pair);
	const std::string getStringForContinuity(CONTINUATION continuity);

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

	BaccaratRecordDelegate *_delegate;
};

#endif // __BACCARAT_RECORD_H__
