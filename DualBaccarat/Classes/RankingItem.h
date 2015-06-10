#ifndef __RANKING_ITEM_H__
#define __RANKING_ITEM_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

class RankingItem : public Sprite
{
public:

	RankingItem();
	~RankingItem();

	static RankingItem* create();

	void setRanking(const std::string ranking);
	void setTier(TIER tier);
	void setNickName(const std::string nickName);
	void setRankPoint(const std::string rankPoint);
	
private:

	Label *_ranking;
	Sprite *_tier;
	Label *_nickName;
	Label *_rankPoint;
};

#endif // __RANKING_ITEM_H__