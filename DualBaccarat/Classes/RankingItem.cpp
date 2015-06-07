#include "RankingItem.h"

RankingItem::RankingItem()
{

}
RankingItem::~RankingItem()
{

}
RankingItem* RankingItem::create()
{
	RankingItem* item = new (std::nothrow) RankingItem();
	if (item && item->initWithFile("ranking/bg_rankingitem.png")) {
		item->autorelease();
		return item;
	}
	CC_SAFE_DELETE(item);
	return nullptr;
}
void RankingItem::setRanking(const std::string ranking)
{
	_ranking = Label::createWithTTF(ranking, _font, 60);
	_ranking->setAnchorPoint(Point(0, 0));
	_ranking->setPosition(20, 10);
	_ranking->setDimensions(70, 100);
	_ranking->setHorizontalAlignment(TextHAlignment::RIGHT);
	_ranking->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(_ranking);
}
void RankingItem::setTier(TIER tier)
{
	switch (tier)
	{
	case TIER::BRONZE :
	{
		_tier = Sprite::create("tier/tier_ranking_bronze.png");
		break;
	}
	case TIER::SILVER :
	{
		_tier = Sprite::create("tier/tier_ranking_silver.png");
		break;
	}
	case TIER::GOLD :
	{
		_tier = Sprite::create("tier/tier_ranking_gold.png");
		break;
	}
	case TIER::PLATINUM :
	{
		_tier = Sprite::create("tier/tier_ranking_platinum.png");
		break;
	}
	case TIER::DIAMOND :
	{
		_tier = Sprite::create("tier/tier_ranking_diamond.png");
		break;
	}
	}

	_tier->setPosition(160, 20);
	_tier->setAnchorPoint(Point(0, 0));
	this->addChild(_tier);
}
void RankingItem::setNickName(const std::string nickName)
{
	_nickName = Label::createWithTTF("", _font, 50);
	_nickName->setString(nickName);
	_nickName->setAnchorPoint(Point(0, 0));
	_nickName->setPosition(300, 10);
	_nickName->setDimensions(300, 100);
	_nickName->setHorizontalAlignment(TextHAlignment::CENTER);
	_nickName->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(_nickName);
}
void RankingItem::setRankPoint(const std::string rankPoint)
{
	_rankPoint = Label::createWithTTF("", _font, 50);
	_rankPoint->setString(rankPoint);
	_rankPoint->setAnchorPoint(Point(0, 0));
	_rankPoint->setPosition(650, 10);
	_rankPoint->setDimensions(450, 100);
	_rankPoint->setHorizontalAlignment(TextHAlignment::RIGHT);
	_rankPoint->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(_rankPoint);
}