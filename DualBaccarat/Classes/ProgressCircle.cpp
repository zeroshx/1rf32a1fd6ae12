#include "ProgressCircle.h"

ProgressCircle::ProgressCircle()
{		
}
ProgressCircle::~ProgressCircle()
{
}
ProgressCircle* ProgressCircle::create()
{
	ProgressCircle *sprite = new (std::nothrow) ProgressCircle();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
bool ProgressCircle::init()
{
	this->initWithFile("progress_circle/icon.png");	
	this->setPosition(_center);
	this->setVisible(false);
	this->setGlobalZOrder(99999);

	_state = MODULE_STATE::IDLE;

	return true;
}
void ProgressCircle::run()
{
	if (_state == MODULE_STATE::IDLE) {

		_state = MODULE_STATE::START;
		
		auto act0 = RotateBy::create(0.2f, 40.0f);
		auto act1 = RepeatForever::create(act0);
		this->setVisible(true);
		this->runAction(act1);		

		_state = MODULE_STATE::DONE;
	}
}
void ProgressCircle::stop()
{	
	if (_state == MODULE_STATE::DONE) {
		
		this->setVisible(false);
		this->stopAllActions();

		_state = MODULE_STATE::IDLE;
	}
}