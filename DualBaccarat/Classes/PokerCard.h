#ifndef __POKER_CARD_H__
#define __POKER_CARD_H__

#include "PublicApi.h"

USING_NS_CC;

#define CARD_NAME_COUNT 13
#define CARD_SYMBOL_COUNT 4

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
	const std::string getNameStr();
	CARD_SYMBOL getSymbol();
	const std::string getSymbolStr();
	int getPoint();
	CARD_OWNER getOwner();
	const std::string getOwnerStr();

private:

	bool _isUsed;
	CARD_NAME _name;
	CARD_SYMBOL _symbol;
	int _point;
	CARD_OWNER _owner;
};

#endif // __POKER_CARD_H__
