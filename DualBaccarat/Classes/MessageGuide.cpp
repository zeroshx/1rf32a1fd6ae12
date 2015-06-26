#include "MessageGuide.h"

MessageGuide::MessageGuide()
{
}
MessageGuide::~MessageGuide()
{

}
MessageGuide* MessageGuide::getInstance()
{
	static MessageGuide ins;
	return &ins;
}
ClippingRectangleNode* MessageGuide::create(MESSAGE_TYPE type, const std::string& msg)
{	
	//setClippingRegion(Rect(0, 0, DESIGN_WIDTH, DESIGN_HEIGHT));
	//setAnchorPoint(Point(0, 0));
	//setPosition(Vec2(0, 0));
	std::string path;
	if (type == POSITIVE) {
		path = "bg_positive.png";
	}
	else if (type == NEGATIVE) {
		path = "bg_negative.png";
	}
	else {
		path = "bg_normal.png";
	}

	auto text = Label::createWithTTF(msg, _font, 40);

	auto background = ImageView::create("message_guide/" + path);
	background->ignoreContentAdaptWithSize(false);
	background->setScale9Enabled(true);
	background->setContentSize(text->getContentSize() + Size(40,40));
	background->setCapInsets(Rect(14, 14, 14, 14));
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Vec2(0, background->getContentSize().height));

	text->setPosition(background->getContentSize() / 2);
	background->addChild(text);

	auto clippingNode = ClippingRectangleNode::create();
	clippingNode->setContentSize(background->getContentSize());
	clippingNode->setClippingRegion(Rect(0, 0, background->getContentSize().width, background->getContentSize().height));
	clippingNode->setAnchorPoint(Point(0.5, 0));
		
	if (_list.size() > 0) {
	
		auto lastNode = _list.back();
		if (lastNode->getPositionY() < 200) {
			clippingNode->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - 300));
		}
		else {
			clippingNode->setPosition(Vec2(_visibleSize.width / 2, lastNode->getPositionY() - clippingNode->getContentSize().height));
		}
	}
	else {

		clippingNode->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - 300));
	}	
	clippingNode->addChild(background);

	auto act_move = MoveTo::create(0.5f, Vec2(0, 0));
	auto act_delay = DelayTime::create(2.0f);
	auto act_remove = CallFuncN::create(CC_CALLBACK_1(MessageGuide::onMessageRemoved, this));
	auto act = Sequence::create(act_move, act_delay, act_remove, nullptr);
	background->runAction(act);

	_list.push_back(clippingNode);
	
	return clippingNode;
}
void MessageGuide::onMessageRemoved(Ref *pSender)
{
	auto me = static_cast<ImageView*>(pSender);
	auto parent = static_cast<ClippingRectangleNode*>(me->getParent());
	_list.remove(parent);
	me->removeFromParent();
}