#include "SceneBaccaratSinglePlay.h"

USING_NS_CC;

Scene* SceneBaccaratSinglePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SceneBaccaratSinglePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneBaccaratSinglePlay::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	// background init
	initView();

	auto btn = Button::create("CloseNormal.png", "CloseSelected.png");
	btn->setPosition(Vec2(1900, 1050));
	btn->addClickEventListener(CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback1, this));
	this->addChild(btn);

	return true;
}
void SceneBaccaratSinglePlay::onEnter()
{
	Node::onEnter();
}
void SceneBaccaratSinglePlay::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	
	addListener();

	_user->setChips("1000000000000");
	_user->setMaxBet("100000000");

	_server->run();
}
void SceneBaccaratSinglePlay::onExit()
{
	Node::onExit();

	removeListener();
}
void SceneBaccaratSinglePlay::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}
void SceneBaccaratSinglePlay::addListener()
{
	// 1. touch event
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [](Touch* touch, Event* event){

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 2. keyboard listener	
	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){

		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{

			break;
		}
		case EventKeyboard::KeyCode::KEY_MENU:
		{

			break;
		}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}
void SceneBaccaratSinglePlay::removeListener()
{
	_eventDispatcher->removeEventListenersForTarget(this);	
}

void SceneBaccaratSinglePlay::initView()
{
	auto bg = Sprite::create("singlegame/background.png");
	bg->setPosition(_center);
	//bg->setScale(1.2f);
	this->addChild(bg);	

	_server = VirtualServer::create();
	_server->setDelegate(this);
	this->addChild(_server);
	
	_betManager = BettingManager::create();
	_betManager->setDelegate(this);
	this->addChild(_betManager, 2);

	_dealer = Dealer::create();
	this->addChild(_dealer, 3);

	_record = BaccaratRecord::create();
	_record->setDelegate(this);
	this->addChild(_record, 4);	

	_progressCircle = ProgressCircle::create();
	this->addChild(_progressCircle, 4);
}
void SceneBaccaratSinglePlay::loadResources()
{
	// image
	auto tlm = TextureLoadingManager::getInstance();
	tlm->init();
	tlm->setDelegate(this);
	/*
	tlm->addTexture("xxxx1");
	tlm->addTexture("xxxx2");
	tlm->addTexture("xxxx3");
	tlm->begin();
	*/
		
	//sound
}
void SceneBaccaratSinglePlay::menuCallback1(Ref* pSender)
{
	static bool toggle = true;

	if (toggle){
		
		_server->serverPause();
		toggle = false;
		TOAST(MessageGuide::NEGATIVE, "Server Stop.");
	}
	else {

		_server->serverResume();
		toggle = true;
		TOAST(MessageGuide::POSITIVE, "Server Run.");
	}
}
void SceneBaccaratSinglePlay::menuCallback2(Ref* pSender)
{
	//CCLOG(__FUNCTION__);
	//_record->push(WINNER::PLAYER, PAIR::BANKER);
	//_record->drawLatestRecord();
	
}
void SceneBaccaratSinglePlay::menuCallback3(Ref* pSender)
{
	//_record->push(WINNER::TIE, PAIR::BOTH);
	//_record->drawLatestRecord();

	
}
void SceneBaccaratSinglePlay::menuCallback8(Ref* pSender)
{
	//_record->reset();

	
}
void SceneBaccaratSinglePlay::menuCallback4(Ref* pSender)
{
	
}
void SceneBaccaratSinglePlay::menuCallback5(Ref* pSender)
{	
	
}
void SceneBaccaratSinglePlay::menuCallback6(Ref* pSender)
{
	
}
void SceneBaccaratSinglePlay::menuCallback7(Ref* pSender)
{
	
}

void SceneBaccaratSinglePlay::onTextureLoadingBegan(TextureLoadingManager* tlm)
{
	
}
void SceneBaccaratSinglePlay::onTextureLoaded(TextureLoadingManager* tlm)
{
	
}
void SceneBaccaratSinglePlay::onTextureLoadingEnded(TextureLoadingManager* tlm)
{
	
}
void SceneBaccaratSinglePlay::onClickPositiveButton(Dialog* pDialog, int index)
{
	
	pDialog->destroy();
}
void SceneBaccaratSinglePlay::onClickNegativeButton(Dialog* pDialog, int index)
{
	
	pDialog->destroy();
}
void SceneBaccaratSinglePlay::onStageReady()
{
	_dealer->reset();
	_betManager->reset();
}
void SceneBaccaratSinglePlay::onStageShuffle()
{
	_record->reset();
	_dealer->shuffleAnimation();
}
void SceneBaccaratSinglePlay::onStageBetting(int time)
{
	_betManager->bettingOpen();
	_dealer->bettingTimerAnimation(time);
}
void SceneBaccaratSinglePlay::onStageDealing(std::vector<PokerCard> cardset)
{	
	_betManager->bettingClose();
	_dealer->cardDealingAnimation(cardset);
}
void SceneBaccaratSinglePlay::onStageGameover(WINNER winner, PAIR pair, std::vector<EXTRA_WINNER> extras)
{	
	_record->push(winner, pair);
	_record->drawLatestRecord();

	_dealer->gameoverAnimation(winner);
}
void SceneBaccaratSinglePlay::onRequestBetting(BettingRecord paper)
{
	_server->sendUserBetReport(paper);
}
void SceneBaccaratSinglePlay::onFullRecordBoard()
{
	_server->requestCardShuffle();
}
void SceneBaccaratSinglePlay::onModuleInit()
{
	
}
void SceneBaccaratSinglePlay::onModuleBegan()
{
	
	//_menu->setEnabled(false);
}
void SceneBaccaratSinglePlay::onModuleWorking()
{
	
}
void SceneBaccaratSinglePlay::onModuleEnded()
{
	//_menu->setEnabled(true);
}