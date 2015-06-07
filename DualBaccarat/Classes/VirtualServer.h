#ifndef __VIRTUAL_SERVER_H__
#define __VIRTUAL_SERVER_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "PokerCard.h"
#include "VirtualServerDelegate.h"

USING_NS_CC;

#define CARDSET_COUNT		CARD_NAME_COUNT * CARD_SYMBOL_COUNT
#define DECK_COUNT			8
#define TOTAL_CARD_COUNT	CARDSET_COUNT * DECK_COUNT

#define BASIC_BET_TIME	3
#define BASIC_SHUFFLE_THRESHOLD 50

class VirtualServer : public Node
{
public:	

	VirtualServer();
	~VirtualServer();

	static VirtualServer* create();
	virtual bool init();

	void run();
	void stop();

	void setDelegate(VirtualServerDelegate *del);

private :
	
	void reset();

	void stateContorller(float delta);
	void ready(float delta);
	void shuffle(float delta);
	void bet(float delta);
	void dealing(float delta);
	void gameover(float delta);

	void selectCard();
	int findUnusedCard();

	GAME_STATE _state;

	int _betTime;

	int _remainingCardCount;
	PokerCard _cards[TOTAL_CARD_COUNT];

	std::vector<PokerCard> _cardset;

	Winner _winner;

	VirtualServerDelegate *_delegate;
};

#endif // __VIRTUAL_SERVER_H__
