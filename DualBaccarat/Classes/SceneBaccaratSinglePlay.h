﻿#ifndef __SCENE_BACCARAT_SINGLEPLAY_H__
#define __SCENE_BACCARAT_SINGLEPLAY_H__

#include "PublicApi.h"
#include "DialogBuilder.h"
#include "ProgressCircle.h"
#include "TextureLoadingManager.h"
#include "BaccaratRecord.h"
#include "VirtualServer.h"
#include "Dealer.h"
#include "ModuleDelegate.h"
#include "BettingManager.h"
#include "MessageGuide.h"
//#include "Money.h"

class SceneBaccaratSinglePlay : 
	public Layer, 
	public TextureLoadingDelegate, 
	public DialogDelegate,
	public VirtualServerDelegate,
	public ModuleDelegate,
	public BettingManagerDelegate,
	public BaccaratRecordDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();    
    
    // implement the "static create()" method manually
	CREATE_FUNC(SceneBaccaratSinglePlay);
	
	// scene life cycle
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	virtual void onTextureLoadingBegan(TextureLoadingManager* tlm);
	virtual void onTextureLoaded(TextureLoadingManager* tlm);
	virtual void onTextureLoadingEnded(TextureLoadingManager* tlm);

	virtual void onClickPositiveButton(Dialog* pDialog, int index);
	virtual void onClickNegativeButton(Dialog* pDialog, int index);	

	virtual void onStageReady();
	virtual void onStageShuffle();
	virtual void onStageBetting(int time);
	virtual void onStageDealing(std::vector<PokerCard> cardset);
	virtual void onStageGameover(WINNER winner, PAIR pair, std::vector<EXTRA_WINNER> extras);

	virtual void onRequestBetting(BettingRecord paper);

	virtual void onFullRecordBoard();

	// listener
	void addListener();
	void removeListener();

	// texture resource loading
	void loadResources();
	
	// init background view 
	void initView();

	// module delegate
	virtual void onModuleInit();
	virtual void onModuleBegan();
	virtual void onModuleWorking();
	virtual void onModuleEnded();

	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	void menuCallback3(Ref* pSender);
	void menuCallback4(Ref* pSender);
	void menuCallback5(Ref* pSender);
	void menuCallback6(Ref* pSender);
	void menuCallback7(Ref* pSender);
	void menuCallback8(Ref* pSender);

private:

	ProgressCircle *_progressCircle;
	BaccaratRecord *_record;
	VirtualServer *_server;
	Dealer *_dealer;
	BettingManager *_betManager;
};

#endif // __SCENE_BACCARAT_SINGLEPLAY_H__
