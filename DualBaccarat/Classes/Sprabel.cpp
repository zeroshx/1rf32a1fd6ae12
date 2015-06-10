#include "Sprabel.h"

Sprabel::Sprabel()
{		
}
Sprabel::~Sprabel()
{
}
Sprabel* Sprabel::create(const std::string spr)
{
	Sprabel *sprabel = new (std::nothrow) Sprabel();
	if (sprabel && sprabel->init(spr, ""))
	{
		sprabel->autorelease();
		return sprabel;
	}
	CC_SAFE_DELETE(sprabel);
	return nullptr;
}
Sprabel* Sprabel::create(const std::string spr, const std::string str)
{
	Sprabel *sprabel = new (std::nothrow) Sprabel();
	if (sprabel && sprabel->init(spr, str))
	{
		sprabel->autorelease();
		return sprabel;
	}
	CC_SAFE_DELETE(sprabel);
	return nullptr;
}
bool Sprabel::init(const std::string spr, const std::string str)
{
	if (!this->initWithFile(spr)){
		return false;
	}
	Size sprSize = this->getContentSize();
	Size labelSize = Size(sprSize.width - 50, sprSize.height);

	_label = Label::createWithTTF(str, _font, sprSize.height - 30, labelSize, TextHAlignment::RIGHT, TextVAlignment::CENTER);
	_label->setAnchorPoint(Point(0.5, 0.5));
	_label->setPosition(labelSize.width / 2, labelSize.height / 2);
	this->addChild(_label);
	
	return true;
}
void Sprabel::setString(const std::string str)
{
	_label->setString(str);
}