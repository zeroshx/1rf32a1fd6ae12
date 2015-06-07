#include "VirtualServer.h"

VirtualServer::VirtualServer()
{		
}
VirtualServer::~VirtualServer()
{
}
VirtualServer* VirtualServer::create()
{
	VirtualServer *server = new (std::nothrow) VirtualServer();
	if (server && server->init())
	{
		server->autorelease();
		return server;
	}
	CC_SAFE_DELETE(server);
	return nullptr;
}
bool VirtualServer::init()
{
	_state = GAME_STATE::READY;	
	_winner = Winner::NONE;
	_remainingCardCount = TOTAL_CARD_COUNT;
	_betTime = BASIC_BET_TIME;

	// card init
	for (int i = 0; i < TOTAL_CARD_COUNT; i += CARD_NAME_COUNT)
	{
		CARD_SYMBOL symbol;
		if (i % 4 == 0){
			symbol = CARD_SYMBOL::CLOVER;
		}
		else if (i % 4 == 1){
			symbol = CARD_SYMBOL::DIAMOND;
		}
		else if (i % 4 == 2){
			symbol = CARD_SYMBOL::HEART;
		}
		else {
			symbol = CARD_SYMBOL::SPADE;
		}
		_cards[i].set(false, CARD_NAME::_A_, symbol, 1, CARD_OWNER::NONE);
		_cards[i + 1].set(false, CARD_NAME::_2_, symbol, 2, CARD_OWNER::NONE);
		_cards[i + 2].set(false, CARD_NAME::_3_, symbol, 3, CARD_OWNER::NONE);
		_cards[i + 3].set(false, CARD_NAME::_4_, symbol, 4, CARD_OWNER::NONE);
		_cards[i + 4].set(false, CARD_NAME::_5_, symbol, 5, CARD_OWNER::NONE);
		_cards[i + 5].set(false, CARD_NAME::_6_, symbol, 6, CARD_OWNER::NONE);
		_cards[i + 6].set(false, CARD_NAME::_7_, symbol, 7, CARD_OWNER::NONE);
		_cards[i + 7].set(false, CARD_NAME::_8_, symbol, 8, CARD_OWNER::NONE);
		_cards[i + 8].set(false, CARD_NAME::_9_, symbol, 9, CARD_OWNER::NONE);
		_cards[i + 9].set(false, CARD_NAME::_10_, symbol, 0, CARD_OWNER::NONE);
		_cards[i + 10].set(false, CARD_NAME::_J_, symbol, 0, CARD_OWNER::NONE);
		_cards[i + 11].set(false, CARD_NAME::_Q_, symbol, 0, CARD_OWNER::NONE);
		_cards[i + 12].set(false, CARD_NAME::_K_, symbol, 0, CARD_OWNER::NONE);
	}

	return true;
}
void VirtualServer::reset()
{	
	_winner = Winner::NONE;
	_remainingCardCount = TOTAL_CARD_COUNT;
	_betTime = BASIC_BET_TIME;
	_cardset.clear();

	for (int i = 0; i < TOTAL_CARD_COUNT; i++)
	{
		_cards[i].setUse(false);
		_cards[i].setOwner(CARD_OWNER::NONE);
	}
}
void VirtualServer::run()
{
	this->scheduleOnce(schedule_selector(VirtualServer::stateContorller), 0);
}
void VirtualServer::stop()
{
	this->unscheduleAllCallbacks();
}
void VirtualServer::setDelegate(VirtualServerDelegate *del)
{
	_delegate = del;
}
void VirtualServer::stateContorller(float delta)
{
	switch (_state)
	{
	case GAME_STATE::READY :

		this->scheduleOnce(schedule_selector(VirtualServer::ready), 0);
		break;

	case  GAME_STATE::SHUFFLE :

		this->scheduleOnce(schedule_selector(VirtualServer::shuffle), 0);
		break;

	case  GAME_STATE::BET :

		this->scheduleOnce(schedule_selector(VirtualServer::bet), 0);
		break;

	case  GAME_STATE::DEALING :

		this->scheduleOnce(schedule_selector(VirtualServer::dealing), 0);
		break;

	case  GAME_STATE::GAMEOVER :

		this->scheduleOnce(schedule_selector(VirtualServer::gameover), 0);
		break;
	}
}
void VirtualServer::ready(float delta)
{
	reset();
	_state = GAME_STATE::SHUFFLE;
	this->scheduleOnce(schedule_selector(VirtualServer::shuffle), 0);
}
void VirtualServer::shuffle(float delta)
{
	if (_remainingCardCount < BASIC_SHUFFLE_THRESHOLD) {

		_delegate->onStageShuffle();
		_state = GAME_STATE::BET;
		this->scheduleOnce(schedule_selector(VirtualServer::bet), ANIM_SHUFFLE_TIME);
	}
	else {

		_state = GAME_STATE::BET;
		this->scheduleOnce(schedule_selector(VirtualServer::bet), 0);
	}
}
void VirtualServer::bet(float delta)
{
	if (_betTime > -1) {

		_delegate->onStageBetting(_betTime);
		_betTime--;
		this->scheduleOnce(schedule_selector(VirtualServer::stateContorller), 1);
	}
	else {

		_state = GAME_STATE::DEALING;
		this->scheduleOnce(schedule_selector(VirtualServer::dealing), 0);
	}
}
void VirtualServer::dealing(float delta)
{	
	selectCard();
	_delegate->onStageDealing(_cardset);
	_state = GAME_STATE::GAMEOVER;
	this->scheduleOnce(schedule_selector(VirtualServer::gameover), ANIM_DEALING_TIME * _cardset.size() + 1);
}
void VirtualServer::selectCard()
{
	int index;

	// 1. select player first card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::PLAYER1);
	_cardset.push_back(_cards[index]);

	// 2. select banker first card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::BANKER1);
	_cardset.push_back(_cards[index]);

	// 3. select player second card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::PLAYER2);
	_cardset.push_back(_cards[index]);

	// 4. select banker second card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::BANKER2);
	_cardset.push_back(_cards[index]);

	// 5. select player third card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::PLAYER3);
	_cardset.push_back(_cards[index]);

	// 6. select banker second card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::BANKER3);
	_cardset.push_back(_cards[index]);
}
int  VirtualServer::findUnusedCard()
{
	int ran;

	do
	{
		ran = RandomHelper::random_int(0, TOTAL_CARD_COUNT - 1);

	} while (_cards[ran].isUsed());

	return ran;
}
void VirtualServer::gameover(float delta)
{
	_winner = Winner::BANKER;
	_delegate->onStageGameover(_winner);
	_state = GAME_STATE::READY;
	this->scheduleOnce(schedule_selector(VirtualServer::ready), ANIM_GAMEOVER_TIME);
}