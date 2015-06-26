#ifndef __VIRTUAL_SERVER_H__
#define __VIRTUAL_SERVER_H__

#include "PublicApi.h"
#include "PokerCard.h"
#include "VirtualServerDelegate.h"
#include "AppUser.h"

USING_NS_CC;

#define CARDSET_COUNT		CARD_NAME_COUNT * CARD_SYMBOL_COUNT
#define DECK_COUNT			8
#define TOTAL_CARD_COUNT	CARDSET_COUNT * DECK_COUNT

#define BASIC_BET_TIME	15
#define BASIC_SHUFFLE_THRESHOLD 100

#define PLAYER_RATE 2
#define PLAYER_PAIR_RATE 12
#define PLAYER_NATURAL_RATE 5
#define BANKER_RATE 1.95f
#define BANKER_PAIR_RATE 12
#define BANKER_NATURAL_RATE 5
#define TIE_RATE 9
#define BIG_RATE 1.5f
#define SMALL_RATE 2.5f

class VirtualServer : public Node
{
public:	

	VirtualServer();
	~VirtualServer();

	static VirtualServer* create();
	virtual bool init();

	void run();
	void stop();

	void sendUserBetReport(BettingRecord report);
	void setDelegate(VirtualServerDelegate *del);
	void requestCardShuffle();

private :
	
	void reset();

	void stageContorller(float delta);
	void ready(float delta);
	void shuffle(float delta);
	void bet(float delta);
	void dealing(float delta);
	void gameover(float delta);

	void selectCard();
	int findUnusedCard();
	void calculateGameResult();
	void cardShuffle();

	GAME_STATE _state;
	int _betTime;
	int _remainingCardCount;
	PokerCard _cards[TOTAL_CARD_COUNT];
	std::vector<PokerCard> _cardset;
	WINNER _winner;
	PAIR _pair;
	std::vector<EXTRA_WINNER> _extras;
	VirtualServerDelegate *_delegate;
	BettingRecord _userBetReport;
	bool _shuffle;
};

#endif // __VIRTUAL_SERVER_H__
