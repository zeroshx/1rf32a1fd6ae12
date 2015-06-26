#include "PokerCard.h"

PokerCard::PokerCard()
{		
	_isUsed = false;
	_name = CARD_NAME::NONE;
	_symbol = CARD_SYMBOL::NONE;
	_owner = CARD_OWNER::NONE;
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
const std::string PokerCard::getNameStr()
{
	switch (_name)
	{	
	case CARD_NAME::_A_:
		return "A";
	case CARD_NAME::_2_:
		return "2";
	case CARD_NAME::_3_:
		return "3";
	case CARD_NAME::_4_:
		return "4";
	case CARD_NAME::_5_:
		return "5";
	case CARD_NAME::_6_:
		return "6";
	case CARD_NAME::_7_:
		return "7";
	case CARD_NAME::_8_:
		return "8";
	case CARD_NAME::_9_:
		return "9";
	case CARD_NAME::_10_:
		return "10";
	case CARD_NAME::_J_:
		return "J";
	case CARD_NAME::_Q_:
		return "Q";
	case CARD_NAME::_K_:
		return "k";
	default:
		return "None";
	}
}
CARD_SYMBOL PokerCard::getSymbol()
{
	return _symbol;
}
const std::string PokerCard::getSymbolStr()
{
	switch (_symbol)
	{
	case CARD_SYMBOL::CLOVER:
		return "Clover";
	case CARD_SYMBOL::HEART:
		return "Heart";
	case CARD_SYMBOL::DIAMOND:
		return "Diamond";
	case CARD_SYMBOL::SPADE:
		return "Spade";
	default:
		return "None";
	}
}
int PokerCard::getPoint()
{
	return _point;
}
CARD_OWNER PokerCard::getOwner()
{
	return _owner;
}
const std::string PokerCard::getOwnerStr()
{
	switch (_owner)
	{
	case CARD_OWNER::PLAYER1:
		return "Player 1";
	case CARD_OWNER::PLAYER2:
		return "Player 2";
	case CARD_OWNER::PLAYER3:
		return "Player 3";
	case CARD_OWNER::BANKER1:
		return "Banker 1";
	case CARD_OWNER::BANKER2:
		return "Banker 2";
	case CARD_OWNER::BANKER3:
		return "Banker 3";
	default:
		return "None";
	}
}
