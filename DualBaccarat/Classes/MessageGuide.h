#ifndef __MESSAGE_GUIDE_H__
#define __MESSAGE_GUIDE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define _font			"NanumGothic_Coding.ttf"

#define _director		Director::getInstance()
#define _visibleSize	_director->getVisibleSize()

USING_NS_CC;
using namespace ui;

class MessageGuide
{
public:
	
	enum MESSAGE_TYPE
	{
		NORMAL,
		POSITIVE,
		NEGATIVE
	};

	MessageGuide();
	~MessageGuide();
	
	static MessageGuide* getInstance();
	ClippingRectangleNode* create(MESSAGE_TYPE type, const std::string& msg);
	
private:

	void onMessageRemoved(Ref *pSender);

	std::list<ClippingRectangleNode*> _list;
};

#endif // __MESSAGE_GUIDE_H__
