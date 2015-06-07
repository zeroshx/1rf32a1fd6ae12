#include "Dialog.h"

Dialog::Dialog()
{

}
Dialog::~Dialog()
{

}
Dialog* Dialog::create()
{
	Dialog* dialog = new (std::nothrow) Dialog();
	if (dialog && dialog->init()) {
		dialog->autorelease();
		return dialog;
	}
	CC_SAFE_DELETE(dialog);
	return nullptr;
}
bool Dialog::init()
{
	_index = 0;

	auto size = Director::getInstance()->getWinSize();
	_bg = Sprite::create("dialog/bg.png");
	_bg->setPosition(size.width / 2, size.height / 2);
	this->addChild(_bg);

	_title = "듀얼바카라";
	_titleImage = Sprite::create("dialog/title_bg.png");
	_titleImage->setAnchorPoint(Point(0.5, 1));
	_titleImage->setPosition(Vec2(_bg->getContentSize().width / 2,
		_bg->getContentSize().height - 25));
	_bg->addChild(_titleImage, 2);

	_message = "Dual Baccarat Dialog Message.";
	_messageImage = Sprite::create("dialog/message_bg.png");
	_messageImage->setAnchorPoint(Point(0.5, 1));
	_messageImage->setPosition(Vec2(_bg->getContentSize().width / 2,
		_bg->getContentSize().height - _titleImage->getContentSize().height - 50));
	_bg->addChild(_messageImage, 1);	

	_positiveText = "OK";
	_positiveImage = MenuItemImage::create("dialog/btn_normal.png", "dialog/btn_selected.png", 
		CC_CALLBACK_1(Dialog::onClickPositive, this));
	_positiveImage->setAnchorPoint(Point(0.5, 0));

	_negativeText = "Cancel";
	_negativeImage = MenuItemImage::create("dialog/btn_normal.png", "dialog/btn_selected.png",
		CC_CALLBACK_1(Dialog::onClickNegative, this));
	_negativeImage->setAnchorPoint(Point(0.5, 0));

	_scene = _director->getRunningScene();

	_delegate = nullptr;

	return true;
}
void Dialog::show()
{
	//set title
	_titleLabel = Label::createWithTTF(_title, _font, 30, Size(680,80), TextHAlignment::CENTER, TextVAlignment::CENTER);
	_titleLabel->setAnchorPoint(Vec2(0.5, 0.5));
	_titleLabel->setPosition(_titleImage->getContentSize().width / 2, _titleImage->getContentSize().height / 2);
	_titleImage->addChild(_titleLabel);

	//set message
	_messageLabel = Label::createWithTTF(_message, _font, 20, Size(680,280), TextHAlignment::CENTER, TextVAlignment::CENTER);
	_messageLabel->setAnchorPoint(Vec2(0.5, 0.5));
	_messageLabel->setPosition(_messageImage->getContentSize().width / 2, _messageImage->getContentSize().height / 2);
	_messageImage->addChild(_messageLabel);

	//set button
	_positiveLabel = Label::createWithTTF(_positiveText, _font, 20, Size(180, 80), TextHAlignment::CENTER, TextVAlignment::CENTER);
	_positiveLabel->setAnchorPoint(Vec2(0.5, 0.5));
	_positiveLabel->setPosition(_positiveImage->getContentSize().width / 2, _positiveImage->getContentSize().height / 2);
	_positiveImage->addChild(_positiveLabel);

	//set button
	_negativeLabel = Label::createWithTTF(_negativeText, _font, 20, Size(180, 80), TextHAlignment::CENTER, TextVAlignment::CENTER);
	_negativeLabel->setAnchorPoint(Vec2(0.5, 0.5));
	_negativeLabel->setPosition(_negativeImage->getContentSize().width / 2, _negativeImage->getContentSize().height / 2);
	_negativeImage->addChild(_negativeLabel);

	Menu* menu;
	if (_btnType == BUTTON_TYPE_1) {

		menu = Menu::create(_positiveImage, NULL);
	}
	else {

		menu = Menu::create(_positiveImage, _negativeImage, NULL);
	}
	menu->setPosition(Vec2(_bg->getContentSize().width / 2, 25));
	menu->alignItemsHorizontallyWithPadding(100);

	_bg->addChild(menu);
	_bg->setScale(0);
	_bg->setOpacity(0);

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	_bg->runAction(action);
	_scene->addChild(this);	
}
void Dialog::destroy()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}
void Dialog::setIndex(int index)
{
	_index = index;
}
void Dialog::setTitle(const std::string& title)
{
	_title = title;
}
void Dialog::setMessage(const std::string& message)
{
	_message = message;
}
void Dialog::setPositiveButtonText(const std::string& positiveText)
{
	_positiveText = positiveText;
}
void Dialog::setNegativeButtonText(const std::string& negativeText)
{
	_negativeText = negativeText;
}
void Dialog::onClickPositive(Ref* sender)
{
	if (_delegate != nullptr) {
		_delegate->onClickPositiveButton(this, this->_index);		
	}
	else {
		destroy();
	}
}
void Dialog::onClickNegative(Ref* sender)
{
	if (_delegate != nullptr) {
		_delegate->onClickNegativeButton(this, this->_index);
	}
	else {
		destroy();
	}	
}
void Dialog::setDelegate(DialogDelegate* dialogDelegate)
{
	_delegate = dialogDelegate;
}
void Dialog::setButtonType(int type)
{
	_btnType = type;
}
