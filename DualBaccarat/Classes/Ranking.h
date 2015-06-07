#ifndef __RANKING_H__
#define __RANKING_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "ui\CocosGUI.h"
#include "RankingItem.h"

USING_NS_CC;

class Ranking : public cocos2d::Layer
{
public:
	
	Ranking();
	~Ranking();

	const std::string& getModuleName();

	static Ranking* create();
	bool init();
	void show();
	void destroy();
	void setItem(int ranking, TIER tier, const std::string nickName, const std::string rankPoint);
	void onExitClicked(Ref* pSender);

private:

	RankingItem *_rankingItem[50];
};

#endif // __RANKING_H__