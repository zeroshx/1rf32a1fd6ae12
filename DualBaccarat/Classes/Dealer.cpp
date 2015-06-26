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

	_timer = Label::createWithBMFont("dealer/bmf_timer.fnt","");
	_timer->setPosition(Vec2(1750, 950));
	_timer->setVisible(false);
	this->addChild(_timer);

	auto bg_scoreboard_p = Sprite::create("dealer/bg_scoreboard.png");
	bg_scoreboard_p->setPosition(Vec2(100,900));
	this->addChild(bg_scoreboard_p);

	_score_player = Label::createWithBMFont("dealer/bmf_score.fnt", "0");
	_score_player->setPosition(bg_scoreboard_p->getContentSize() / 2);
	_score_player->setScale(0.5);
	bg_scoreboard_p->addChild(_score_player);

	auto bg_scoreboard_b = Sprite::create("dealer/bg_scoreboard.png");
	bg_scoreboard_b->setPosition(Vec2(270, 900));
	this->addChild(bg_scoreboard_b);

	_score_banker = Label::createWithBMFont("dealer/bmf_score.fnt", "0");
	_score_banker->setPosition(bg_scoreboard_b->getContentSize() / 2);
	_score_banker->setScale(0.5f);
	bg_scoreboard_b->addChild(_score_banker);
	
	_dealingLayer = Layer::create();
	_dealingLayer->setContentSize(_visibleSize);
	this->addChild(_dealingLayer);
	
	_dealingPos[CARD_OWNER::PLAYER1] = Vec2(650, 700);
	_dealingPos[CARD_OWNER::BANKER1] = Vec2(1175, 700);
	_dealingPos[CARD_OWNER::PLAYER2] = Vec2(740, 700);
	_dealingPos[CARD_OWNER::BANKER2] = Vec2(1265, 700);
	_dealingPos[CARD_OWNER::PLAYER3] = Vec2(700, 530);
	_dealingPos[CARD_OWNER::BANKER3] = Vec2(1155, 590);

	return true;
}
void Dealer::reset()
{
	_score_player->setString("0");
	_score_banker->setString("0");

	_player_sum = 0;
	_banker_sum = 0;
}
void Dealer::shuffleAnimation()
{
	
}
void Dealer::gameoverAnimation(WINNER winner)
{	
	Sprite *spr;

	if (winner == WINNER::PLAYER) {

		spr = Sprite::create("dealer/player.png");		
	}
	else if (winner == WINNER::BANKER) {

		spr = Sprite::create("dealer/banker.png");
	}
	else {

		spr = Sprite::create("dealer/tie.png");
	}

	spr->setAnchorPoint(Point(0.5, 0));
	spr->setPosition(Vec2(-spr->getContentSize().width / 2, _visibleSize.height / 2));
	this->addChild(spr);

	auto act1 = EaseBackOut::create(MoveTo::create(1.0f, Vec2(_visibleSize / 2)));
	auto act2 = DelayTime::create(2.0f);
	auto act3 = CallFuncN::create(CC_CALLBACK_1(Dealer::onGameoverAnimationEnded, this));
	auto act = Sequence::create(act1, act2, act3, nullptr);
	spr->runAction(act);

	if (winner != WINNER::TIE) {
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
	PokerCard card;

	for (auto iter : _cardset)
	{
		if (iter.getOwner() == _curDealing) {

			card = iter;
			break;
		}
	}

	if (card.isUsed()) {

		// 2. maping card image.
		auto spr = Sprite::create("dealer/" + getImageName(&card));
		spr->setPosition(Vec2(1650, 800));
		spr->setScale(0.25f);
		spr->setRotation(240);
		_dealingLayer->addChild(spr);

		// 2. dealing action
		auto pre_move = EaseExponentialOut::create(MoveTo::create(ANIM_PREDEALING_TIME, _center));
		auto pre_scale = EaseExponentialOut::create(ScaleTo::create(ANIM_PREDEALING_TIME, 1.0f));
		auto pre_rotate = EaseExponentialOut::create(RotateBy::create(ANIM_PREDEALING_TIME, Vec3(0, 720, 480)));
		auto pre_dealing = Spawn::create(pre_move, pre_scale, pre_rotate, nullptr);

		auto middle_func = CallFunc::create(CC_CALLBACK_0(Dealer::onMiddleDealingAnimation, this, card));

		auto delay = DelayTime::create(0.5f);

		SkewTo *skew = nullptr;
		if (card.getOwner() == CARD_OWNER::PLAYER1) {

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, 9.5f, 0);
		}
		else if (card.getOwner() == CARD_OWNER::PLAYER2){

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, 8.5f, 0);
		}
		else if (card.getOwner() == CARD_OWNER::PLAYER3){

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, 0, -6.5f);
		}
		else if (card.getOwner() == CARD_OWNER::BANKER1){

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, -8.5f, 0);
		}
		else if (card.getOwner() == CARD_OWNER::BANKER2){

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, -9.5f, 0);
		}
		else if (card.getOwner() == CARD_OWNER::BANKER3){

			skew = SkewTo::create(ANIM_POSTDEALING_TIME, 0, 8.0f);
		}

		Spawn *post_dealing = nullptr;
		if (card.getOwner() == CARD_OWNER::PLAYER3 || card.getOwner() == CARD_OWNER::BANKER3) {

			Vec3 r;
			if (card.getOwner() == CARD_OWNER::PLAYER3) {

				r = Vec3(0, 0, 90);
			}
			else {

				r = Vec3(0, 0, -90);
			}

			auto post_skew = EaseExponentialOut::create(skew);
			auto post_rotate = EaseExponentialOut::create(RotateBy::create(ANIM_POSTDEALING_TIME, r));
			auto post_move = EaseExponentialOut::create(MoveTo::create(ANIM_POSTDEALING_TIME, _dealingPos[_curDealing]));
			auto post_scale = EaseExponentialOut::create(ScaleTo::create(ANIM_POSTDEALING_TIME, 0.17f, 0.21f));
			post_dealing = Spawn::create(post_skew, post_rotate, post_move, post_scale, nullptr);
		}
		else {

			auto post_skew = EaseExponentialOut::create(skew);
			auto post_move = EaseExponentialOut::create(MoveTo::create(ANIM_POSTDEALING_TIME, _dealingPos[_curDealing]));
			auto post_scale = EaseExponentialOut::create(ScaleTo::create(ANIM_POSTDEALING_TIME, 0.21f, 0.17f));
			post_dealing = Spawn::create(post_skew, post_move, post_scale, nullptr);
		}

		auto end_func = CallFunc::create(CC_CALLBACK_0(Dealer::onDealingAnimationEeded, this));
		auto act = Sequence::create(pre_dealing, middle_func, delay, post_dealing, end_func, nullptr);
		spr->runAction(act);
	}
	else {

		this->scheduleOnce(schedule_selector(Dealer::changeDealingOrder), 0);
	}
}
void Dealer::onDealingAnimationEeded()
{
	changeDealingOrder(0);
}
void Dealer::changeDealingOrder(float unused)
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
void Dealer::onMiddleDealingAnimation(PokerCard card)
{
	if (card.getOwner() == CARD_OWNER::PLAYER1 || card.getOwner() == CARD_OWNER::PLAYER2 || card.getOwner() == CARD_OWNER::PLAYER3) {

		_player_sum += card.getPoint();
		if (_player_sum >= 10) {

			_player_sum -= 10;
		}
		_score_player->setString(StringUtils::format("%d", _player_sum));
	}
	else {

		_banker_sum += card.getPoint();
		if (_banker_sum >= 10) {

			_banker_sum -= 10;
		}
		_score_banker->setString(StringUtils::format("%d", _banker_sum));
	}
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
	case CARD_SYMBOL::HEART : name += "heart"; break;
	case CARD_SYMBOL::SPADE : name += "spade"; break;
	}

	return name + ".png";

}
