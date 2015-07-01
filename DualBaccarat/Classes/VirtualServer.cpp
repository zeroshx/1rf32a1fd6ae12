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

	_state = GAME_STATE::READY;
	_shuffle = false;
	_remainingCardCount = TOTAL_CARD_COUNT;

	return true;
}
void VirtualServer::reset()
{	
	_winner = WINNER::NONE;
	_pair = PAIR::NONE;
	_betTime = BASIC_BET_TIME;
	_userBetReport.reset();
	_cardset.clear();
	_extras.clear();
}
void VirtualServer::run()
{
	this->scheduleOnce(schedule_selector(VirtualServer::stageContorller), 0);
}
void VirtualServer::stop()
{
	this->unscheduleAllCallbacks();
}
void VirtualServer::setDelegate(VirtualServerDelegate *del)
{
	_delegate = del;
}
void VirtualServer::stageContorller(float delta)
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
	_delegate->onStageReady();
	_state = GAME_STATE::SHUFFLE;
	this->scheduleOnce(schedule_selector(VirtualServer::shuffle), 0);
}
void VirtualServer::shuffle(float delta)
{
	if (_remainingCardCount < BASIC_SHUFFLE_THRESHOLD || _shuffle) {

		cardShuffle();
		_delegate->onStageShuffle();
		_state = GAME_STATE::BET;		
		this->scheduleOnce(schedule_selector(VirtualServer::bet), ANIM_SHUFFLE_TIME);
	}
	else {

		_state = GAME_STATE::BET;
		this->scheduleOnce(schedule_selector(VirtualServer::bet), 0);
	}
}
void VirtualServer::cardShuffle()
{
	for (int i = 0; i < TOTAL_CARD_COUNT; i++)
	{
		_cards[i].setUse(false);
		_cards[i].setOwner(CARD_OWNER::NONE);
	}
	_remainingCardCount = TOTAL_CARD_COUNT;
	_shuffle = false;
}
void VirtualServer::bet(float delta)
{
	if (_betTime > -1) {

		_delegate->onStageBetting(_betTime);
		_betTime--;
		this->scheduleOnce(schedule_selector(VirtualServer::stageContorller), 1);
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
	//this->scheduleOnce(schedule_selector(VirtualServer::gameover), 0);
}
void VirtualServer::selectCard()
{
	int index;
	int playerSum = 0, drawPoint = 0;
	int bankerSum = 0;
	bool playerDraw = false;
	bool bankerDraw = false;
	CARD_NAME player1 = CARD_NAME::NONE;
	CARD_NAME banker1 = CARD_NAME::NONE;
	bool playerPair = false;
	bool bankerPair = false;
	bool playerNatural = false;
	bool bankerNatural = false;

	// 1. select player first card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::PLAYER1);
	_cardset.push_back(_cards[index]);
	playerSum += _cards[index].getPoint();
	player1 = _cards[index].getName();

	// 2. select banker first card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::BANKER1);
	_cardset.push_back(_cards[index]);
	bankerSum += _cards[index].getPoint();
	banker1 = _cards[index].getName();

	// 3. select player second card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::PLAYER2);
	_cardset.push_back(_cards[index]);
	playerSum += _cards[index].getPoint();
	if (player1 == _cards[index].getName()){
		playerPair = true;
	}

	// 4. select banker second card
	index = findUnusedCard();
	_cards[index].setUse(true);
	_cards[index].setOwner(CARD_OWNER::BANKER2);
	_cardset.push_back(_cards[index]);
	bankerSum += _cards[index].getPoint();
	if (banker1 == _cards[index].getName()){
		bankerPair = true;
	}

	if (playerSum >= 10) {
		playerSum -= 10;
	}
	if (bankerSum >= 10) {
		bankerSum -= 10;
	}

	if (playerSum == 8 || playerSum == 9) {

		playerNatural = true;
	}
	if (bankerSum == 8 || bankerSum == 9) {

		bankerNatural = true;
	}

	if (!playerNatural && !bankerNatural) {

		//player part
		if (0 <= playerSum && playerSum <= 5) {

			// 5. select player third card
			playerDraw = true;			
			index = findUnusedCard();
			_cards[index].setUse(true);
			_cards[index].setOwner(CARD_OWNER::PLAYER3);
			_cardset.push_back(_cards[index]);
			drawPoint = _cards[index].getPoint();
			playerSum += _cards[index].getPoint();
		}

		//banker part
		if (playerDraw) {

			if (0 <= bankerSum && bankerSum <= 2) {

				bankerDraw = true;
			}
			else if (bankerSum == 3 && drawPoint != 8) {
				
				bankerDraw = true;
			}
			else if (bankerSum == 4 && (2 <= drawPoint && drawPoint  <= 7)) {

				bankerDraw = true;
			}
			else if (bankerSum == 5 && (4 <= drawPoint && drawPoint <= 7)) {

				bankerDraw = true;
			}
			else if (bankerSum == 6 && (6 <= drawPoint && drawPoint <= 7)) {

				bankerDraw = true;
			}
		}
		else {

			if (0 <= bankerSum && bankerSum <= 5){

				bankerDraw = true;
			}
		}

		if (bankerDraw){

			// 6. select banker second card
			index = findUnusedCard();
			_cards[index].setUse(true);
			_cards[index].setOwner(CARD_OWNER::BANKER3);
			_cardset.push_back(_cards[index]);
			bankerSum += _cards[index].getPoint();
		}
	}

	if (playerSum >= 10) {
		playerSum -= 10;
	}
	if (bankerSum >= 10) {
		bankerSum -= 10;
	}

	//set winner
	if (playerSum > bankerSum) {
		_winner = WINNER::PLAYER;
	}
	else if (playerSum < bankerSum){
		_winner = WINNER::BANKER;
	}
	else{
		_winner = WINNER::TIE;
	}

	//set PAIR
	if (playerPair && bankerPair) {
		_pair = PAIR::BOTH;
	}
	else if (!playerPair && bankerPair) {
		_pair = PAIR::BANKER;
	}
	else if (playerPair && !bankerPair) {
		_pair = PAIR::PLAYER;
	}
	else {
		_pair = PAIR::NONE;
	}

	//set Player natural
	if (playerNatural) {

		EXTRA_WINNER pn;
		pn = EXTRA_WINNER::PLAYER_NATURAL;
		_extras.push_back(pn);
	}

	//set Banker natural
	if (bankerNatural) {

		EXTRA_WINNER bn;
		bn = EXTRA_WINNER::BANKER_NATURAL;
		_extras.push_back(bn);
	}

	//set big or small
	if (_cardset.size() < 5) {

		EXTRA_WINNER s;
		s = EXTRA_WINNER::SMALL;
		_extras.push_back(s);
	}
	else {

		EXTRA_WINNER b;
		b = EXTRA_WINNER::BIG;
		_extras.push_back(b);
	}

	CCLOG("===============================================================");
	CCLOG("===============================================================");
	for (auto iter : _cardset)
	{
		CCLOG("<%s> : %s(%s)", iter.getOwnerStr().c_str(), iter.getNameStr().c_str(), iter.getSymbolStr().c_str());
	}

	CCLOG("Cards count : %d", _remainingCardCount);

	if (_winner == WINNER::PLAYER) {

		CCLOG("Winner : PLAYER");
	}
	else if (_winner == WINNER::BANKER) {

		CCLOG("Winner : BANKER");
	}
	else if (_winner == WINNER::TIE) {

		CCLOG("Winner : TIE");
	}

	if (_pair == PAIR::PLAYER || _pair == PAIR::BOTH) {

		CCLOG("Pair : PLAYER");
	}
	if (_pair == PAIR::BANKER || _pair == PAIR::BOTH) {

		CCLOG("Pair : BANKER");
	}

	for (auto iter : _extras)
	{
		if (iter == EXTRA_WINNER::PLAYER_NATURAL) {

			CCLOG("PLAYER_NATURAL");
		}
		else if (iter == EXTRA_WINNER::BANKER_NATURAL) {

			CCLOG("BANKER_NATURAL");
		}
		else if (iter == EXTRA_WINNER::BIG) {

			CCLOG("BIG");
		}
		else {	 // small

			CCLOG("SMALL");
		}
	}
}
int  VirtualServer::findUnusedCard()
{
	int ran;

	while (_remainingCardCount > 0){

		ran = RandomHelper::random_int(0, TOTAL_CARD_COUNT - 1);
		if (!_cards[ran].isUsed()) {

			_cards[ran].setUse(true);
			_remainingCardCount--;
			break;
		}
	}

	return ran;
}
void VirtualServer::gameover(float delta)
{
	calculateGameResult();

	_delegate->onStageGameover(_winner, _pair, _extras);
	_state = GAME_STATE::READY;
	this->scheduleOnce(schedule_selector(VirtualServer::ready), ANIM_GAMEOVER_TIME);
}
void VirtualServer::sendUserBetReport(BettingRecord report)
{
	CCLOG("===============================================================");
	CCLOG("===============================================================");
	CCLOG("Before User Chips : %lld", _user->getChipsInt());

	_user->setChipsInt(_user->getChipsInt() - (report._total - _userBetReport._total));
	_userBetReport = report;

	CCLOG("After User Chips : %lld", _user->getChipsInt());
	CCLOG("Player : %d", _userBetReport._type[BET_TYPE::PLAYER]);
	CCLOG("Player Pair: %d", _userBetReport._type[BET_TYPE::PLAYER_PAIR]);
	CCLOG("Player Natural: %d", _userBetReport._type[BET_TYPE::PLAYER_NATURAL]);
	CCLOG("Banker : %d", _userBetReport._type[BET_TYPE::BANKER]);
	CCLOG("Banker Pair : %d", _userBetReport._type[BET_TYPE::BANKER_PAIR]);
	CCLOG("Banker Natural : %d", _userBetReport._type[BET_TYPE::BANKER_NATURAL]);
	CCLOG("Tie : %d", _userBetReport._type[BET_TYPE::TIE]);
	CCLOG("Big : %d", _userBetReport._type[BET_TYPE::BIG]);
	CCLOG("Small : %d", _userBetReport._type[BET_TYPE::SMALL]);
	CCLOG("Betting Total : %d", report._total);
}
void VirtualServer::calculateGameResult()
{
	int total = 0;

	CCLOG("===============================================================");
	CCLOG("===============================================================");	
	
	if (_winner == WINNER::PLAYER) {

		total += _userBetReport._type[BET_TYPE::PLAYER] * PLAYER_RATE;
		CCLOG("PLAYER bet money : %d", _userBetReport._type[BET_TYPE::PLAYER] * PLAYER_RATE);
	}
	else if (_winner == WINNER::BANKER) {

		total += _userBetReport._type[BET_TYPE::BANKER] * BANKER_RATE;
		CCLOG("BANKER bet money : %d", (int)(_userBetReport._type[BET_TYPE::BANKER] * BANKER_RATE));
	}
	else if (_winner == WINNER::TIE) {

		total += _userBetReport._type[BET_TYPE::TIE] * TIE_RATE;
		CCLOG("TIE bet money : %d", _userBetReport._type[BET_TYPE::TIE] * TIE_RATE);
	}

	if (_pair == PAIR::PLAYER || _pair == PAIR::BOTH) {

		total += _userBetReport._type[BET_TYPE::PLAYER_PAIR] * PLAYER_PAIR_RATE;
		CCLOG("PLAYER PAIR bet money : %d", _userBetReport._type[BET_TYPE::PLAYER_PAIR] * PLAYER_PAIR_RATE);
	}
	if (_pair == PAIR::BANKER || _pair == PAIR::BOTH) {

		total += _userBetReport._type[BET_TYPE::BANKER_PAIR] * BANKER_PAIR_RATE;
		CCLOG("BANKER PAIR bet money : %d", _userBetReport._type[BET_TYPE::BANKER_PAIR] * BANKER_PAIR_RATE);
	}	

	for (auto iter : _extras)
	{
		if (iter == EXTRA_WINNER::PLAYER_NATURAL) {

			total += _userBetReport._type[BET_TYPE::PLAYER_NATURAL] * PLAYER_NATURAL_RATE;
			CCLOG("PLAYER NATURAL bet money : %d", _userBetReport._type[BET_TYPE::PLAYER_NATURAL] * PLAYER_NATURAL_RATE);
		}
		else if (iter == EXTRA_WINNER::BANKER_NATURAL) {

			total += _userBetReport._type[BET_TYPE::BANKER_NATURAL] * BANKER_NATURAL_RATE;
			CCLOG("BANKER NATURAL bet money : %d", _userBetReport._type[BET_TYPE::BANKER_NATURAL] * BANKER_NATURAL_RATE);
		}
		else if (iter == EXTRA_WINNER::BIG) {

			total += _userBetReport._type[BET_TYPE::BIG] * BIG_RATE;
			CCLOG("BIG bet money : %d", (int)(_userBetReport._type[BET_TYPE::BIG] * BIG_RATE));
		}
		else {	 // small

			total += _userBetReport._type[BET_TYPE::SMALL] * SMALL_RATE;
			CCLOG("SMALL bet money : %d", (int)(_userBetReport._type[BET_TYPE::SMALL] * SMALL_RATE));
		}
	}
	
	_user->setChipsInt(_user->getChipsInt() + total);
	CCLOG("User Chips : %lld", _user->getChipsInt());
}
void VirtualServer::requestCardShuffle()
{
	_shuffle = true;	
}
void VirtualServer::serverResume()
{
	this->resumeSchedulerAndActions();
}
void VirtualServer::serverPause()
{
	this->pauseSchedulerAndActions();
}