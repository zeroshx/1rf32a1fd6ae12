#include "SceneLobby.h"

USING_NS_CC;

Scene* SceneLobby::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneLobby::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneLobby::init()
{
	CCLOG(__FUNCTION__);
    if ( !Layer::init() )
    {
        return false;
    }
	
	// ui position setting

	// background init
	initView();

    return true;
}
void SceneLobby::onEnter()
{
	Node::onEnter();
}
void SceneLobby::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	
	addListener();
}
void SceneLobby::onExit()
{
	Node::onExit();

	removeListener();
}
void SceneLobby::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}
void SceneLobby::addListener()
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
void SceneLobby::removeListener()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

void SceneLobby::initView()
{	
	auto bg = Sprite::create("grid.png");
	bg->setPosition(_center);
	this->addChild(bg);

	auto gp = Sprabel::create("lobby/bg_cash.png", "123,321,321");
	gp->setPosition(Vec2(1450, 1000));
	this->addChild(gp);

	auto rp = Sprabel::create("lobby/bg_cash.png", "123,321,321");
	rp->setPosition(Vec2(900, 1000));
	this->addChild(rp);
	
	auto ticket = Sprabel::create("lobby/bg_ticket.png", "121");
	ticket->setPosition(Vec2(500, 1000));
	this->addChild(ticket);

	auto runItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneLobby::menuCallback1, this));
	runItem->setScale(2.0);
	runItem->setPosition(Vec2(240, 120));

	auto stopItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneLobby::menuCallback2, this));
	stopItem->setScale(2.0);
	stopItem->setPosition(Vec2(360, 120));	

	auto urlItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneLobby::menuCallback3, this));
	urlItem->setScale(2.0);
	urlItem->setPosition(Vec2(480, 120));

	auto settingItem = MenuItemImage::create(
		"lobby/setting.png",
		"lobby/setting.png",
		CC_CALLBACK_1(SceneLobby::menuCallback4, this));
	settingItem->setPosition(Vec2(1800, 1000));

	auto baccaratItem = MenuItemImage::create(
		"lobby/baccarat_normal.png",
		"lobby/baccarat_selected.png",
		CC_CALLBACK_1(SceneLobby::menuCallback5, this));
	baccaratItem->setPosition(Vec2(600, 120));

	// create menu, it's an autorelease object
	_menu = Menu::create(runItem, stopItem, urlItem, settingItem, baccaratItem, NULL);
	_menu->setPosition(Vec2::ZERO);
	this->addChild(_menu, 1);

	_letterBoard = LetterBoard::create();	
	this->addChild(_letterBoard);

	_progressCircle = ProgressCircle::create();
	this->addChild(_progressCircle);
}

void SceneLobby::menuCallback1(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	_letterBoard->run("fdjalkfjalkfjlkajlfkajflksjalk");		
	_progressCircle->run();
	
}
void SceneLobby::menuCallback2(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	_letterBoard->stop();	
	_progressCircle->stop();
}
void SceneLobby::menuCallback3(Ref* pSender)
{
	CCLOG(__FUNCTION__);

	DialogBuilder db;
	auto dialog = db.build(0);
	dialog->show();

	//Application::getInstance()->openURL("http://www.naver.com/");
}
void SceneLobby::menuCallback4(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	auto ranking = Ranking::create();
	if (ranking) {
		for (int i = 0; i < 50; i++)
		{
			ranking->setItem(i, TIER::BRONZE, "Zeros", "123,123,123");
		}
		ranking->show();
	}
}
void SceneLobby::menuCallback5(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	auto baccaratType = BaccaratMode::create();
	if (baccaratType) {
		baccaratType->setDelegate(this);
		baccaratType->show();
	}
}

void SceneLobby::loadResources()
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


void SceneLobby::onTextureLoadingBegan(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneLobby::onTextureLoaded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneLobby::onTextureLoadingEnded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);	
}
void SceneLobby::onClickPositiveButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneLobby::onClickNegativeButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneLobby::onSinglePlaySelected(BaccaratMode* pSender)
{
	CCLOG(__FUNCTION__);
	auto scene = SceneIntro::createScene();
	_director->replaceScene(scene);
}
void SceneLobby::onWorldClassSelected(BaccaratMode* pSender)
{
	CCLOG(__FUNCTION__);
	auto scene = SceneLogin::createScene();
	_director->replaceScene(scene);
}