#include "LetterBoard.h"

USING_NS_CC;

LetterBoard::LetterBoard()
{
	
}
LetterBoard::~LetterBoard()
{

}
LetterBoard* LetterBoard::create()
{
	LetterBoard *ret = new (std::nothrow) LetterBoard();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}
bool LetterBoard::init()
{	
	setClippingRegion(Rect(0, 0, LETTERBOARD_WIDTH, LETTERBOARD_HEIGHT));
	setAnchorPoint(Point(0, 0));
	setPosition(Vec2(0, 0));

	_background = Sprite::create("letterboard/background.png");
	_background->setAnchorPoint(Point(0, 0));
	_background->setPosition(Vec2(0, 0));
	this->addChild(_background);

	_label = Label::createWithTTF("", _font, LETTER_SIZE, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	_label->setAnchorPoint(Point(0, 0.5));
	_label->setPosition(Vec2(LETTERBOARD_WIDTH, _background->getContentSize().height / 2));
	_background->addChild(_label);

	_state = MODULE_STATE::IDLE;
	
	return true;
}
void LetterBoard::setSentence(const std::string& sentence)
{
	_label->setString(sentence);
}
void LetterBoard::run()
{
	if (_state == MODULE_STATE::IDLE && _label->getStringLength() > 0) {

		_state = MODULE_STATE::START;

		auto length = _label->getStringLength();
		auto dest = (length * LETTER_SIZE) + LETTERBOARD_WIDTH;
		auto time = (dest / 1000) * LETTER_SPEED;

		auto act0 = MoveBy::create(time, Vec2(-dest, 0));
		auto act1 = CallFunc::create(CC_CALLBACK_0(LetterBoard::onMoveEnded, this));
		auto seq = Sequence::create(act0, act1, NULL);
		auto repeat = RepeatForever::create(seq);
		_label->runAction(repeat);

		_state = MODULE_STATE::DONE;
	}
}
void LetterBoard::run(const std::string& sentence)
{
	setSentence(sentence);
	run();
}
void LetterBoard::stop()
{
	if (_state == MODULE_STATE::DONE) {
		
		_label->stopAllActions();
		onMoveEnded();

		_state = MODULE_STATE::IDLE;
	}
}
void LetterBoard::onMoveEnded()
{
	_label->setPosition(Vec2(LETTERBOARD_WIDTH, _background->getContentSize().height / 2));
}
