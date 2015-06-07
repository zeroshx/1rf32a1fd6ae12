#include "SceneIntro.h"

USING_NS_CC;

Scene* SceneIntro::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneIntro::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneIntro::init()
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
void SceneIntro::onEnter()
{
	Node::onEnter();
}
void SceneIntro::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	
	addListener();
}
void SceneIntro::onExit()
{
	Node::onExit();

	removeListener();
}
void SceneIntro::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}
void SceneIntro::addListener()
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
void SceneIntro::removeListener()
{
	_eventDispatcher->removeEventListenersForTarget(this);	
}

void SceneIntro::initView()
{
	auto label = Label::createWithTTF("THIS IS INTRO SCENE.", _font, 50);
	label->setPosition(_center);
	this->addChild(label);
}
void SceneIntro::loadResources()
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


void SceneIntro::onTextureLoadingBegan(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneIntro::onTextureLoaded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneIntro::onTextureLoadingEnded(TextureLoadingManager* tlm)
{
	CCLOG(__FUNCTION__);
}
void SceneIntro::onClickPositiveButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}
void SceneIntro::onClickNegativeButton(Dialog* pDialog, int index)
{
	CCLOG(__FUNCTION__);
	pDialog->destroy();
}