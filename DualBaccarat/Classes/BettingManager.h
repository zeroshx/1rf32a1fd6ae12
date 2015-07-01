#ifndef __BETTING_MANAGER_H__
#define __BETTING_MANAGER_H__

#include "PublicApi.h"
#include "ModuleDelegate.h"
#include "ui/CocosGUI.h"
#include "BettingManagerDelegate.h"

USING_NS_CC;
using namespace ui;

#define FAKE_BET	"FAKE"
#define REAL_BET	"REAL"

#define BET_LAYER_TAG	10

#define COUNT_CHIP_ZONE		16
#define CHIP_ZONE_INTERVAL	30
class ChipZone
{
public :
	Vec2 _offset;
	int _chipSize;
	int _chipCount;
	int _zOrder;
};

class BettingManager : public cocos2d::Layer
{
public:	
	
	BettingManager();
	~BettingManager();

	void reset();

	static BettingManager* create();
	bool init();

	void setDelegate(BettingManagerDelegate *bmd);
	void enable();
	void disable();
	void bettingOpen();
	void bettingClose();

private:

	void initBettingMenu();
	void initBettingType();
	void initBettingInfo();
	void initChipZone();

	void onBetting();
	void onBettingCancel();
	void onChipTouched(Ref *sender, int money);
	void onRebetting(Ref *sender);
	void onBettingTypeTouched(Ref* sender);
	void onGameover();

	void throwChip(int type, int money);
	int getRequiredChips(int money, int chipSize);
	int findChipZone(int type, int chipSize);
		
	BettingManagerDelegate *_delegate;

	Menu *_betMenu;

	Sprite *_betBoard;
	Texture2D *_betType[COUNT_BET_TYPE + 1];
	int _selectedType;

	Label *_myChips;
	Label *_potChips;

	BettingRecord _previousBet;
	BettingRecord _finalBet;
	BettingRecord _trialBet;

	bool _isBetted;
	bool _isOpened;

	int _userMaxBet;

	ChipZone _chipZone[COUNT_BET_TYPE][COUNT_CHIP_ZONE];
};

#endif // __DIALOG_H__