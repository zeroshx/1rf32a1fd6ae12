#include "SceneLogin.h"

USING_NS_CC;

Scene* SceneLogin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneLogin::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneLogin::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	// ProgressCircle init
	_progressCircle = ProgressCircle::create();   
    
	// background init
	initView();

    return true;
}
void SceneLogin::onEnter()
{
	Node::onEnter();
}
void SceneLogin::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	
	addListener();
}
void SceneLogin::onExit()
{
	Node::onExit();

	removeListener();
}
void SceneLogin::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}
void SceneLogin::addListener()
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
void SceneLogin::removeListener()
{
	_eventDispatcher->removeEventListenersForTarget(this);	
}

void SceneLogin::initView()
{
	auto label = Label::createWithTTF("THIS IS LOGIN SCENE.", _font, 50);
	label->setPosition(_center);
	this->addChild(label);
}
void SceneLogin::loadResources()
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


void SceneLogin::onTextureLoadingBegan(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneLogin::onTextureLoaded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneLogin::onTextureLoadingEnded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);	
}
void SceneLogin::onClickPositiveButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneLogin::onClickNegativeButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}