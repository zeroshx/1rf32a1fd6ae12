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

	_letterBoard->run("Welcome to Dual Baccarat!");

	_profile->setNickName("ZEROSHX");
	_profile->setTier(TIER::DIAMOND);
	_profile->setTopRankPoint("321,315,123");
	_profile->setHighDividend("123,543,163");
	_profile->setWinningStreak("12");
	_profile->setChips("432,124,163");
	_profile->setRankPoint("164,744,243");
	_profile->setTicket("214");
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
	
	_profile = Profile::create();
	this->addChild(_profile, 1);

	_letterBoard = LetterBoard::create();
	this->addChild(_letterBoard, 1);

	_progressCircle = ProgressCircle::create();
	this->addChild(_progressCircle, 10);

	auto notice = MenuItemImage::create("lobby/menu_notice_normal.png",
		"lobby/menu_notice_selected.png",
		CC_CALLBACK_0(SceneLobby::onNoticeSelected, this));
	notice->setPosition(Vec2(120,800));

	auto cafe = MenuItemImage::create("lobby/menu_cafe_normal.png",
		"lobby/menu_cafe_selected.png",
		CC_CALLBACK_0(SceneLobby::onCafeSelected, this));
	cafe->setPosition(Vec2(120, 600));

	auto ranking = MenuItemImage::create("lobby/menu_ranking_normal.png",
		"lobby/menu_ranking_selected.png",
		CC_CALLBACK_0(SceneLobby::onRankingSelected, this));
	ranking->setPosition(Vec2(150, 180));

	auto mission = MenuItemImage::create("lobby/menu_mission_normal.png",
		"lobby/menu_mission_selected.png",
		CC_CALLBACK_0(SceneLobby::onMissionSelected, this));
	mission->setPosition(Vec2(370, 180));

	auto tier = MenuItemImage::create("lobby/menu_tier_normal.png",
		"lobby/menu_tier_selected.png",
		CC_CALLBACK_0(SceneLobby::onTierSelected, this));
	tier->setPosition(Vec2(590, 180));

	auto store = MenuItemImage::create("lobby/menu_store_normal.png",
		"lobby/menu_store_selected.png",
		CC_CALLBACK_0(SceneLobby::onStoreSelected, this));
	store->setPosition(Vec2(810, 180));

	auto baccarat = MenuItemImage::create("lobby/menu_baccarat_normal.png",
		"lobby/menu_baccarat_selected.png",
		CC_CALLBACK_0(SceneLobby::onBaccaratSelected, this));
	baccarat->setPosition(Vec2(550, 600));

	auto roadmap = MenuItemImage::create("lobby/menu_roadmap_normal.png",
		"lobby/menu_roadmap_selected.png",
		CC_CALLBACK_0(SceneLobby::onRoadmapSelected, this));
	roadmap->setPosition(Vec2(1000, 600));

	auto configuration = MenuItemImage::create("lobby/menu_configuration_normal.png",
		"lobby/menu_configuration_selected.png",
		CC_CALLBACK_0(SceneLobby::onConfigurationSelected, this));
	configuration->setPosition(Vec2(1800, 1000));

	// create menu, it's an autorelease object
	_menu = Menu::create(notice, cafe, ranking, mission, tier, store, 
		baccarat, roadmap,
		configuration, nullptr); 
	_menu->setPosition(Vec2::ZERO);
	_menu->setSwallowsTouches(false);
	this->addChild(_menu, 1);
}

void SceneLobby::onBaccaratSelected()
{
	CCLOG(__FUNCTION__);	
	auto baccaratMode = BaccaratMode::create();
	if (baccaratMode) {
		baccaratMode->setDelegate(this);
		baccaratMode->show();
	}
}
void SceneLobby::onRoadmapSelected()
{
	CCLOG(__FUNCTION__);
	
}
void SceneLobby::onNoticeSelected()
{
	CCLOG(__FUNCTION__);
	_progressCircle->run();
}
void SceneLobby::onCafeSelected()
{
	CCLOG(__FUNCTION__);
	Application::getInstance()->openURL("http://section.cafe.naver.com/");
}
void SceneLobby::onRankingSelected()
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
void SceneLobby::onMissionSelected()
{
	CCLOG(__FUNCTION__);
	
}
void SceneLobby::onTierSelected()
{
	CCLOG(__FUNCTION__);
	
}
void SceneLobby::onStoreSelected()
{
	CCLOG(__FUNCTION__);
	auto store = Store::create();
	this->addChild(store, 2);
}
void SceneLobby::onConfigurationSelected()
{
	CCLOG(__FUNCTION__);

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
	

}
void SceneLobby::onWorldClassSelected(BaccaratMode* pSender)
{
	CCLOG(__FUNCTION__);
	
}