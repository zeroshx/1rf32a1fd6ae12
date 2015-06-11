#include "Profile.h"

Profile::Profile()
{		
}
Profile::~Profile()
{
}
Profile* Profile::create()
{
	Profile *profile = new (std::nothrow) Profile();
	if (profile && profile->init())
	{
		profile->autorelease();
		return profile;
	}
	CC_SAFE_DELETE(profile);
	return nullptr;
}
bool Profile::init()
{
	setContentSize(_visibleSize);

	// Hud zone start
	_chips = Sprabel::create("lobby/bg_cash.png");
	_chips->setPosition(Vec2(1450, 1000));
	this->addChild(_chips);

	_rp = Sprabel::create("lobby/bg_cash.png");
	_rp->setPosition(Vec2(900, 1000));
	this->addChild(_rp);

	_ticket = Sprabel::create("lobby/bg_ticket.png");
	_ticket->setPosition(Vec2(500, 1000));
	this->addChild(_ticket);
	// Hud zone end

	// right profile zone start
	auto _bg_profile = Sprite::create("profile/bg_profile.png");
	_bg_profile->setPosition(Vec2(1600, 500));
	this->addChild(_bg_profile);

	auto bg_top_rp = Sprite::create("profile/bg_top_rp.png");
	bg_top_rp->setPosition(Vec2(250, 440));
	_bg_profile->addChild(bg_top_rp);

	auto bg_dividend_rp = Sprite::create("profile/bg_acquire_rp.png");
	bg_dividend_rp->setPosition(Vec2(250, 270));
	_bg_profile->addChild(bg_dividend_rp);

	auto bg_winningStreak = Sprite::create("profile/bg_winning_streak.png");
	bg_winningStreak->setPosition(Vec2(250, 100));
	_bg_profile->addChild(bg_winningStreak);

	_tier = Sprite::create("tier/default.png");
	_tier->setPosition(Vec2(100, 620));
	_bg_profile->addChild(_tier);

	_tierName = Label::createWithTTF("UNRANKER", _font, 30);
	_tierName->setPosition(Vec2(100, 550));
	_bg_profile->addChild(_tierName);

	_nickName = Label::createWithTTF("Guest", _font, 50);
	_nickName->setAnchorPoint(Point(0, 0.5));
	_nickName->setPosition(Vec2(200,630));	
	_bg_profile->addChild(_nickName);

	auto _greet = Label::createWithTTF("Welcome!", _font, 30);
	_greet->setAnchorPoint(Point(0, 0.5));
	_greet->setPosition(Vec2(200, 580));
	_bg_profile->addChild(_greet);

	_topRankPoint = Label::createWithTTF("Load Fail.", _font, 40);
	_topRankPoint->setPosition(Vec2(250, 430));
	_bg_profile->addChild(_topRankPoint);

	_highDividend = Label::createWithTTF("Load Fail.", _font, 40);
	_highDividend->setPosition(Vec2(250, 260));
	_bg_profile->addChild(_highDividend);

	_winningStreak = Label::createWithTTF("Load Fail.", _font, 40);
	_winningStreak->setPosition(Vec2(250, 90));
	_bg_profile->addChild(_winningStreak);
	// right profile zone end
	
	return true;
}
void Profile::setTier(TIER tier)
{
	if (tier == TIER::UNRANKER) {
		return;
	}

	Texture2D *temp;
	
	switch (tier) {

	case TIER::BRONZE :		
		
		temp = _textureCache->addImage("tier/bronze.png");
		_tierName->setString("BRONZE");
		break;

	case TIER::SILVER :
		
		temp = _textureCache->addImage("tier/silver.png");
		_tierName->setString("SILVER");
		break;

	case TIER::GOLD :
		
		temp = _textureCache->addImage("tier/gold.png");
		_tierName->setString("GOLD");
		break;

	case TIER::PLATINUM :
		
		temp = _textureCache->addImage("tier/platinum.png");
		_tierName->setString("PLATINUM");
		break;

	case TIER::DIAMOND :

		temp = _textureCache->addImage("tier/diamond.png");
		_tierName->setString("DIAMOND");
		break;

	case TIER::MASTER :

		temp = _textureCache->addImage("tier/master.png");
		_tierName->setString("MASTER");
		break;

	case TIER::CHALLENGER :

		temp = _textureCache->addImage("tier/challenger.png");
		_tierName->setString("CHALLENGER");
		break;
	}

	_tier->setTexture(temp);
}
void Profile::setNickName(const std::string& nickName)
{
	_nickName->setString(nickName);
}
void Profile::setTopRankPoint(const std::string& rp)
{
	_topRankPoint->setString(rp);
}
void Profile::setHighDividend(const std::string& dividend)
{
	_highDividend->setString(dividend);
}
void Profile::setWinningStreak(const std::string& winningStreak)
{
	_winningStreak->setString(winningStreak);
}
void Profile::setChips(const std::string& chips)
{
	_chips->setString(chips);
}
void Profile::setRankPoint(const std::string& rp)
{
	_rp->setString(rp);
}
void Profile::setTicket(const std::string& ticket)
{
	_ticket->setString(ticket);
}