#ifndef __DEALER_H__
#define __DEALER_H__

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

	void reset();
	void shuffleAnimation();
	void gameoverAnimation(WINNER winner);
	void bettingTimerAnimation(int time);
	void cardDealingAnimation(std::vector<PokerCard> cardset);	

private :	// private member func

	void dealingController(float unused);
	void dealing(float unused);
	void changeDealingOrder(float unused);
	void onDealingAnimationEeded();
	void onMiddleDealingAnimation(PokerCard card);
	void onGameoverAnimationEnded(Ref* target);
	std::string getImageName(PokerCard *p);

private :	// private member vars.

	Label *_timer;
	Label *_score_player;
	Label *_score_banker;

	int _player_sum;
	int _banker_sum;
	
	Layer *_dealingLayer;

	CARD_OWNER _curDealing;
	std::vector<PokerCard> _cardset;
	Vec2 _dealingPos[6];

};

#endif // __DEALER_H__