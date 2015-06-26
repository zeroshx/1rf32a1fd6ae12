#ifndef __BETTING_MANAGER_H__
#define __BETTING_MANAGER_H__

#include "PublicApi.h"
#include "ModuleDelegate.h"
#include "ui/CocosGUI.h"
#include "BettingManagerDelegate.h"
#include "AppUser.h"

USING_NS_CC;
using namespace ui;

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

	void onBetting();
	void onBettingCancel();
	void onChipTouched(Ref *sender, int money);
	void onRebetting(Ref *sender);
	void onBettingTypeTouched(Ref* sender);	

	void throwChip(int type, int money);
	int getRequiredChips(int money, int chipSize);
		
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
};

#endif // __DIALOG_H__