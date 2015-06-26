#include "BaccaratMode.h"

BaccaratMode::BaccaratMode()
{		
}
BaccaratMode::~BaccaratMode()
{
}
BaccaratMode* BaccaratMode::create()
{
	BaccaratMode *baccarat = new (std::nothrow) BaccaratMode();
	if (baccarat && baccarat->init())
	{
		baccarat->autorelease();
		return baccarat;
	}
	CC_SAFE_DELETE(baccarat);
	return nullptr;
}
bool BaccaratMode::init()
{	
	this->setContentSize(_visibleSize);
	
	auto background = Sprite::create("baccarat_mode/background.png");
	background->setPosition(_visibleSize / 2);
	this->addChild(background);

	auto singlePlay = MenuItemImage::create(
		"baccarat_mode/singleplay_normal.png",
		"baccarat_mode/singleplay_selected.png",
		CC_CALLBACK_1(BaccaratMode::onSinglePlaySelected, this));
	singlePlay->setPosition(background->getPosition() - Vec2(200, 30));

	auto worldClass = MenuItemImage::create(
		"baccarat_mode/worldclass_normal.png",
		"baccarat_mode/worldclass_selected.png",
		CC_CALLBACK_1(BaccaratMode::onWorldClassSelected, this));
	worldClass->setPosition(background->getPosition() + Vec2(200, -30));

	auto exit = MenuItemImage::create(
		"baccarat_mode/exit_normal.png",
		"baccarat_mode/exit_selected.png",
		CC_CALLBACK_1(BaccaratMode::onExitSelected, this));
	exit->setPosition((background->getPosition() + background->getContentSize() / 2) - Vec2(50, 50));

	auto menu = Menu::create(singlePlay, worldClass, exit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	this->setScale(0);
	this->setOpacity(0);

	return true;
}
void BaccaratMode::show()
{
	_moduleDelegate->onModuleBegan();

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	this->runAction(action);
	_director->getRunningScene()->addChild(this, 2);
}
void BaccaratMode::onSinglePlaySelected(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	_delegate->onSinglePlaySelected(this);
	_moduleDelegate->onModuleEnded();
	destroy();
}
void BaccaratMode::onWorldClassSelected(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	_delegate->onWorldClassSelected(this);
	_moduleDelegate->onModuleEnded();
	destroy();
}
void BaccaratMode::onExitSelected(Ref* pSender)
{
	CCLOG(__FUNCTION__);
	_moduleDelegate->onModuleEnded();
	destroy();
}
void BaccaratMode::setDelegate(BaccaratModeDelegate* dg1, ModuleDelegate* dg2)
{
	_delegate = dg1;
	_moduleDelegate = dg2;
}
void BaccaratMode::destroy()
{
	this->removeAllChildren();
	this->removeFromParent();
}