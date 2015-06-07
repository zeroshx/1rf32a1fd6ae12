#ifndef __POKER_CARD_H__
#define __POKER_CARD_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

#define CARD_NAME_COUNT 13
#define CARD_SYMBOL_COUNT 4

enum class CARD_NAME
{
	NONE,
	_A_,
	_2_,
	_3_,
	_4_,
	_5_,
	_6_,
	_7_,
	_8_,
	_9_,
	_10_,
	_J_,
	_Q_,
	_K_
};
enum class CARD_SYMBOL
{
	NONE,
	SPADE,
	HEART,
	CLOVER,
	DIAMOND	
};
enum CARD_OWNER
{
	NONE = 0,
	PLAYER1,
	BANKER1,
	PLAYER2,
	BANKER2,
	PLAYER3,
	BANKER3
};
class PokerCard
{
public:	

	PokerCard();
	PokerCard(bool use, CARD_NAME name, CARD_SYMBOL symbol, int point, CARD_OWNER owner);
	~PokerCard();

	void set(bool use, CARD_NAME name, CARD_SYMBOL symbol, int point, CARD_OWNER owner);
	void setUse(bool use);
	void setName(CARD_NAME name);
	void setSymbol(CARD_SYMBOL symbol);
	void setPoint(int point);
	void setOwner(CARD_OWNER owner);

	bool isUsed();
	CARD_NAME getName();
	CARD_SYMBOL getSymbol();
	int getPoint();
	CARD_OWNER getOwner();

private:

	bool _isUsed;
	CARD_NAME _name;
	CARD_SYMBOL _symbol;
	int _point;
	CARD_OWNER _owner;
};

#endif // __POKER_CARD_H__
