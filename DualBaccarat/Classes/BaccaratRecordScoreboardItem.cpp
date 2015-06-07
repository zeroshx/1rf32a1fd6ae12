#include "BaccaratRecordScoreboardItem.h"

BaccaratRecordScoreboardItem::BaccaratRecordScoreboardItem()
{
}
BaccaratRecordScoreboardItem::~BaccaratRecordScoreboardItem()
{
}
BaccaratRecordScoreboardItem* BaccaratRecordScoreboardItem::create(const std::string& icon, const std::string& name)
{
	BaccaratRecordScoreboardItem *item = new (std::nothrow) BaccaratRecordScoreboardItem();
	if (item && item->init(icon, name))
	{
		item->autorelease();
		return item;
	}
	CC_SAFE_DELETE(item);
	return nullptr;
}
bool BaccaratRecordScoreboardItem::init(const std::string& icon, const std::string& name)
{
	this->setContentSize(ITEM_SIZE);
	
	_icon = Sprite::create(icon);
	_icon->setAnchorPoint(Point(0, 0));
	_icon->setPosition(Vec2(0, 0));
	this->addChild(_icon);
	 
	_name = Sprite::create(name);
	_name->setAnchorPoint(Point(0, 0));
	_name->setPosition(Vec2(70, 0));	
	this->addChild(_name);

	_value = Label::createWithTTF("0", _font, 40);
	_value->setAnchorPoint(Point(0, 0));
	_value->setPosition(340, 0);
	_value->setDimensions(60, 60);
	_value->setHorizontalAlignment(TextHAlignment::RIGHT);
	_value->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(_value);

	return true;
}
void BaccaratRecordScoreboardItem::setScore(const std::string& value)
{
	_value->setString(value);
}
