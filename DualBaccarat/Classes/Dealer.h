#ifndef __DEALER_H__
#define __DEALER_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "PokerCard.h"

USING_NS_CC;

#define CARD_COUNT	52
#define DECK_COUNT	8

class Dealer : public Layer
{
public:	

	Dealer();
	~Dealer();

	static Dealer* create();
	virtual bool init();

	void shuffleAnimation();
	void gameoverAnimation(Winner winner);
	void bettingTimerAnimation(int time);
	void cardDealingAnimation(std::vector<PokerCard> cardset);
	

private :	// private member func

	void dealingController(float unused);
	void dealing(float unused);
	void onDealingAnimationEeded();
	void onGameoverAnimationEnded(Ref *target);
	std::string getImageName(PokerCard *p);

private :	// private member vars.

	Label *_timer;
	
	Layer *_dealingLayer;

	CARD_OWNER _curDealing;
	std::vector<PokerCard> _cardset;
	Vec2 _dealingPos[6];

};

#endif // __DEALER_H__