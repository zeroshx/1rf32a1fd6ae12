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
	auto bg = Sprite::create("grid.png");
	bg->setPosition(_center);
	this->addChild(bg);

	auto banker = MenuItemImage::create(
		"baccarat_record/banker.png",
		"baccarat_record/banker.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback1, this));
	banker->setPosition(Vec2(240, 120));

	auto player = MenuItemImage::create(
		"baccarat_record/player.png",
		"baccarat_record/player.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback2, this));
	player->setPosition(Vec2(360, 120));

	auto tie = MenuItemImage::create(
		"baccarat_record/tie.png",
		"baccarat_record/tie.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback3, this));
	tie->setPosition(Vec2(480, 120));

	auto chart1 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback4, this));
	chart1->setScale(2.0);
	chart1->setPosition(Vec2(240, 1000));

	auto chart2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback5, this));
	chart2->setScale(2.0);
	chart2->setPosition(Vec2(360, 1000));

	auto chart3 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback6, this));
	chart3->setScale(2.0);
	chart3->setPosition(Vec2(480, 1000));

	auto chart4 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback7, this));
	chart4->setScale(2.0);
	chart4->setPosition(Vec2(600, 1000));	

	auto reset = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBaccaratSinglePlay::menuCallback8, this));
	reset->setScale(2.0);
	reset->setPosition(Vec2(720, 120));

	// create menu, it's an autorelease object
	auto _menu = Menu::create(banker, player, tie, chart1, chart2, chart3, chart4, reset, NULL);
	_menu->setPosition(Vec2::ZERO);
	this->addChild(_menu, 1);	

	_server = VirtualServer::create();
	_server->setDelegate(this);
	this->addChild(_server);

	_dealer = Dealer::create();
	this->addChild(_dealer,2);

	_record = BaccaratRecord::create();
	this->addChild(_record, 3);

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
	//CCLOG(__FUNCTION__);
	_record->push(Winner::BANKER, Pair::PLAYER);
	_record->drawLatestRecord();
}
void SceneBaccaratSinglePlay::menuCallback2(Ref* pSender)
{
	//CCLOG(__FUNCTION__);
	_record->push(Winner::PLAYER, Pair::BANKER);
	_record->drawLatestRecord();
}
void SceneBaccaratSinglePlay::menuCallback3(Ref* pSender)
{
	_record->push(Winner::TIE, Pair::BOTH);
	_record->drawLatestRecord();
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
void SceneBaccaratSinglePlay::menuCallback8(Ref* pSender)
{
	_record->reset();
}

void SceneBaccaratSinglePlay::onTextureLoadingBegan(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneBaccaratSinglePlay::onTextureLoaded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneBaccaratSinglePlay::onTextureLoadingEnded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneBaccaratSinglePlay::onClickPositiveButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneBaccaratSinglePlay::onClickNegativeButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneBaccaratSinglePlay::onStageShuffle()
{
	CCLOG(__FUNCTION__);
	_dealer->shuffleAnimation();
}
void SceneBaccaratSinglePlay::onStageBetting(int time)
{
	CCLOG(__FUNCTION__);
	_dealer->bettingTimerAnimation(time);
}
void SceneBaccaratSinglePlay::onStageDealing(std::vector<PokerCard> cardset)
{
	CCLOG(__FUNCTION__);
	_dealer->cardDealingAnimation(cardset);
}
void SceneBaccaratSinglePlay::onStageGameover(Winner winner)
{
	CCLOG(__FUNCTION__);
	_dealer->gameoverAnimation(winner);
}