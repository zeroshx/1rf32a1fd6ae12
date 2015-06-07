#include "PokerCard.h"

PokerCard::PokerCard()
{		
	_isUsed = false;
	_name = CARD_NAME::NONE;
	_symbol = CARD_SYMBOL::NONE;
	_point = 0;
}
PokerCard::PokerCard(bool use, CARD_NAME name, CARD_SYMBOL symbol, int point, CARD_OWNER owner)
{
	set(use, name, symbol, point, owner);
}
PokerCard::~PokerCard()
{
}
void PokerCard::set(bool use, CARD_NAME name, CARD_SYMBOL symbol, int point, CARD_OWNER owner)
{
	_isUsed = use;
	_name = name;
	_symbol = symbol;
	_point = point;
	_owner = owner;
}
void PokerCard::setUse(bool use)
{
	_isUsed = use;	
}
void PokerCard::setName(CARD_NAME name)
{	
	_name = name;
}
void PokerCard::setSymbol(CARD_SYMBOL symbol)
{
	_symbol = symbol;
}
void PokerCard::setPoint(int point)
{
	_point = point;
}
void PokerCard::setOwner(CARD_OWNER owner)
{
	_owner = owner;
}
bool PokerCard::isUsed()
{
	return _isUsed;
}
CARD_NAME PokerCard::getName()
{
	return _name;
}
CARD_SYMBOL PokerCard::getSymbol()
{
	return _symbol;
}
int PokerCard::getPoint()
{
	return _point;
}
CARD_OWNER PokerCard::getOwner()
{
	return _owner;
}
