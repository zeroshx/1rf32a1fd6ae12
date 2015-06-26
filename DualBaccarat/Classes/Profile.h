#ifndef __PROFILE_H__
#define __PROFILE_H__

#include "PublicApi.h"
#include "Sprabel.h"

USING_NS_CC;

class Profile : public cocos2d::Layer
{
public:

	Profile();
	~Profile();

	static Profile* create();
	virtual bool init();

	void setTier(TIER tier);
	void setNickName(const std::string& nickName);
	void setTopRankPoint(const std::string& rp);
	void setHighDividend(const std::string& dividend);
	void setWinningStreak(const std::string& winningStreak);
	void setChips(const std::string& chips);
	void setRankPoint(const std::string& rp);
	void setTicket(const std::string& ticket);

private:

	Sprite *_bg_profile;
	Sprite *_tier;
	Label *_tierName;
	Label *_nickName;
	Label *_topRankPoint;
	Label *_highDividend;
	Label *_winningStreak;
	
	Sprabel *_chips;
	Sprabel *_rp;
	Sprabel *_ticket;
};

#endif // __PROFILE_H__
