#include "Dealer.h"

Dealer::Dealer()
{		
}
Dealer::~Dealer()
{
}
Dealer* Dealer::create()
{
	Dealer *dealer = new (std::nothrow) Dealer();
	if (dealer && dealer->init())
	{
		dealer->autorelease();
		return dealer;
	}
	CC_SAFE_DELETE(dealer);
	return nullptr;
}
bool Dealer::init()
{
	setContentSize(_visibleSize);

	_timer = Label::createWithBMFont("dealer/timer.fnt","");
	_timer->setPosition(Vec2(1700, 600));
	_timer->setVisible(false);
	this->addChild(_timer);
	
	_dealingLayer = Layer::create();
	_dealingLayer->setContentSize(_visibleSize);
	this->addChild(_dealingLayer);
	
	_dealingPos[0] = Vec2(600, 500);
	_dealingPos[1] = Vec2(1100, 500);
	_dealingPos[2] = Vec2(800, 500);
	_dealingPos[3] = Vec2(1300, 500);

	_dealingPos[4] = Vec2(1400, 700);
	_dealingPos[5] = Vec2(1700, 700);

	return true;
}
void Dealer::shuffleAnimation()
{

}
void Dealer::gameoverAnimation(Winner winner)
{	
	Sprite *spr;

	if (winner == Winner::PLAYER) {

		spr = Sprite::create("dealer/player.png");		
	}
	else if (winner == Winner::BANKER) {

		spr = Sprite::create("dealer/banker.png");
	}
	else {

		spr = Sprite::create("dealer/tie.png");
	}

	spr->setAnchorPoint(Point(0.5, 0));
	spr->setPosition(Vec2(-spr->getContentSize().width / 2, _visibleSize.height / 2));
	this->addChild(spr);

	auto act1 = EaseBackOut::create(MoveTo::create(1.0f, Vec2(_visibleSize / 2)));
	auto act2 = DelayTime::create(1.0f);
	auto act3 = CallFuncN::create(CC_CALLBACK_1(Dealer::onGameoverAnimationEnded, this));
	auto act = Sequence::create(act1, act2, act3, nullptr);
	spr->runAction(act);

	if (winner != Winner::TIE) {
		auto win = Sprite::create("dealer/win.png");
		win->setAnchorPoint(Point(0.5, 1));
		win->setPosition(Vec2(_visibleSize.width + win->getContentSize().width / 2, _visibleSize.height / 2));
		this->addChild(win);

		auto _act3 = RemoveSelf::create();
		auto _act = Sequence::create(act1->clone(), act2->clone(), _act3, nullptr);
		win->runAction(_act);
	}
}
void Dealer::onGameoverAnimationEnded(Ref *target)
{
	CCLOG(__FUNCTION__);
	Sprite *spr = (Sprite*)target;
	spr->removeFromParent();

	_dealingLayer->removeAllChildren();
}
void Dealer::bettingTimerAnimation(int time)
{
	_timer->setVisible(true);
	_timer->setString(StringUtils::format("%d", time));
}
void Dealer::cardDealingAnimation(std::vector<PokerCard> cardset)
{
	_timer->setVisible(false);

	_cardset.clear();
	_cardset = cardset;	
	_curDealing = CARD_OWNER::PLAYER1;
	this->scheduleOnce(schedule_selector(Dealer::dealingController), 0);
}
void Dealer::dealingController(float unused)
{
	if (_curDealing != CARD_OWNER::NONE) {

		this->scheduleOnce(schedule_selector(Dealer::dealing), 0);
	}
}
void Dealer::dealing(float unused)
{
	// 1. find target card.
	PokerCard *p;
	for (auto iter : _cardset) 
	{
		if (iter.getOwner() == _curDealing) {

			p = &iter;
			break;
		}
	}

	auto spr = Sprite::create("dealer/card2.png");
	spr->setPosition(_visibleSize);
	_dealingLayer->addChild(spr);
		
	// 2. seperate dealing type and adjust action
	if (CARD_OWNER::PLAYER1 <= _curDealing && _curDealing <= CARD_OWNER::BANKER2) {
				
		auto act1 = EaseExponentialOut::create(MoveTo::create(1.5f, _dealingPos[_curDealing - 1]));
		auto act2 = CallFunc::create(CC_CALLBACK_0(Dealer::onDealingAnimationEeded, this));
		auto act = Sequence::create(act1, act2, nullptr);
		spr->runAction(act);
	}
	else {
		
	}	
}
void Dealer::onDealingAnimationEeded()
{
	switch (_curDealing) {
	case CARD_OWNER::PLAYER1: _curDealing = CARD_OWNER::BANKER1; break;
	case CARD_OWNER::BANKER1: _curDealing = CARD_OWNER::PLAYER2; break;
	case CARD_OWNER::PLAYER2: _curDealing = CARD_OWNER::BANKER2; break;
	case CARD_OWNER::BANKER2: _curDealing = CARD_OWNER::PLAYER3; break;
	case CARD_OWNER::PLAYER3: _curDealing = CARD_OWNER::BANKER3; break;
	case CARD_OWNER::BANKER3: _curDealing = CARD_OWNER::NONE; break;
	}
	this->scheduleOnce(schedule_selector(Dealer::dealingController), 0);
}
std::string Dealer::getImageName(PokerCard *p)
{
	std::string name = "card";

	switch (p->getName()) {
	case CARD_NAME::_A_: name += "_a_"; break;
	case CARD_NAME::_2_: name += "_2_"; break;
	case CARD_NAME::_3_: name += "_3_"; break;
	case CARD_NAME::_4_: name += "_4_"; break;
	case CARD_NAME::_5_: name += "_5_"; break;
	case CARD_NAME::_6_: name += "_6_"; break;
	case CARD_NAME::_7_: name += "_7_"; break;
	case CARD_NAME::_8_: name += "_8_"; break;
	case CARD_NAME::_9_: name += "_9_"; break;
	case CARD_NAME::_10_: name += "_10_"; break;
	case CARD_NAME::_J_: name += "_j_"; break;
	case CARD_NAME::_Q_: name += "_q_"; break;
	case CARD_NAME::_K_: name += "_k_"; break;
	}

	switch (p->getSymbol()) {
	case CARD_SYMBOL::CLOVER : name += "clover"; break;
	case CARD_SYMBOL::DIAMOND : name += "diamond"; break;
	case CARD_SYMBOL::HEART : name += "hert"; break;
	case CARD_SYMBOL::SPADE : name += "spade"; break;
	}

	return name + ".png";

}
