#ifndef __RANKING_H__
#define __RANKING_H__

#include "PublicApi.h"
#include "ui\CocosGUI.h"
#include "RankingItem.h"
#include "ModuleDelegate.h"

USING_NS_CC;

class Ranking : public cocos2d::Layer
{
public:
	
	Ranking();
	~Ranking();

	static Ranking* create();
	bool init();
	void show();
	void destroy();
	void setItem(int ranking, TIER tier, const std::string nickName, const std::string rankPoint);
	void onExitClicked(Ref* pSender);
	void setDelegate(ModuleDelegate* md);

private:

	RankingItem *_rankingItem[50];
	ModuleDelegate *_moduleDelegate;
};

#endif // __RANKING_H__