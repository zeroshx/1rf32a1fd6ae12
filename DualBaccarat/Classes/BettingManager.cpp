#include "BettingManager.h"

BettingManager::BettingManager()
{

}
BettingManager::~BettingManager()
{

}
BettingManager* BettingManager::create()
{
	BettingManager* manager = new (std::nothrow) BettingManager();
	if (manager && manager->init()) {
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return nullptr;
}
bool BettingManager::init()
{
	setContentSize(_visibleSize);
	
	initBettingMenu();

	initBettingType();
	
	initBettingInfo();

	reset();

	disable();

	return true;
}
void BettingManager::initBettingMenu()
{
	auto bet5k = MenuItemImage::create("betting_manager/chip_5k.png",
		"betting_manager/chip_5k_pressed.png",
		"betting_manager/chip_5k_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, 5000));
	bet5k->setAnchorPoint(Point(0.5, 0));
	bet5k->setScale(0.8f);
	bet5k->setPosition(Vec2(400, 80));

	auto bet20k = MenuItemImage::create("betting_manager/chip_20k.png",
		"betting_manager/chip_20k_pressed.png",
		"betting_manager/chip_20k_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, 20000));
	bet20k->setAnchorPoint(Point(0.5, 0));
	bet20k->setScale(0.8f);
	bet20k->setPosition(Vec2(580, 80));

	auto bet100k = MenuItemImage::create("betting_manager/chip_100k.png",
		"betting_manager/chip_100k_pressed.png",
		"betting_manager/chip_100k_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, 100000));
	bet100k->setAnchorPoint(Point(0.5, 0));
	bet100k->setScale(0.8f);
	bet100k->setPosition(Vec2(760, 80));

	auto bet500k = MenuItemImage::create("betting_manager/chip_500k.png",
		"betting_manager/chip_500k_pressed.png",
		"betting_manager/chip_500k_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, 500000));
	bet500k->setAnchorPoint(Point(0.5, 0));
	bet500k->setScale(0.8f);
	bet500k->setPosition(Vec2(940, 80));

	auto bet1000k = MenuItemImage::create("betting_manager/chip_1000k.png",
		"betting_manager/chip_1000k_pressed.png",
		"betting_manager/chip_1000k_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, 1000000));
	bet1000k->setAnchorPoint(Point(0.5, 0));
	bet1000k->setScale(0.8f);
	bet1000k->setPosition(Vec2(1120, 80));

	auto betMax = MenuItemImage::create("betting_manager/chip_max.png",
		"betting_manager/chip_max_pressed.png",
		"betting_manager/chip_max_disabled.png",
		CC_CALLBACK_1(BettingManager::onChipTouched, this, -1));
	betMax->setAnchorPoint(Point(0.5, 0));
	betMax->setScale(0.8f);
	betMax->setPosition(Vec2(1300, 80));

	auto rebetting = MenuItemImage::create("betting_manager/rebetting.png",
		"betting_manager/rebetting_pressed.png",
		"betting_manager/rebetting_disabled.png",
		CC_CALLBACK_1(BettingManager::onRebetting, this));
	rebetting->setAnchorPoint(Point(0.5, 0));
	rebetting->setScale(0.8f);
	rebetting->setPosition(Vec2(1480, 80));

	auto betting = MenuItemImage::create("betting_manager/betting.png",
		"betting_manager/betting_pressed.png",
		"betting_manager/betting_disabled.png",
		CC_CALLBACK_0(BettingManager::onBetting, this));
	betting->setPosition(Vec2(1750, 450));

	auto cancel = MenuItemImage::create("betting_manager/cancel.png",
		"betting_manager/cancel_pressed.png",
		"betting_manager/cancel_disabled.png",
		CC_CALLBACK_0(BettingManager::onBettingCancel, this));
	cancel->setPosition(Vec2(1750, 250));
	
	_betMenu = Menu::create(bet5k, bet20k, bet100k, bet500k, bet1000k, betMax, rebetting, betting, cancel, nullptr);
	_betMenu->setPosition(Vec2::ZERO);
	this->addChild(_betMenu, 1);
}
void BettingManager::initBettingType()
{
	_betType[BET_TYPE::PLAYER] = _textureCache->addImage("betting_manager/bet_player.png");
	_betType[BET_TYPE::PLAYER_PAIR] = _textureCache->addImage("betting_manager/bet_player_pair.png");
	_betType[BET_TYPE::PLAYER_NATURAL] = _textureCache->addImage("betting_manager/bet_player_natural.png");
	_betType[BET_TYPE::BANKER] = _textureCache->addImage("betting_manager/bet_banker.png");
	_betType[BET_TYPE::BANKER_PAIR] = _textureCache->addImage("betting_manager/bet_banker_pair.png");
	_betType[BET_TYPE::BANKER_NATURAL] = _textureCache->addImage("betting_manager/bet_banker_natural.png");
	_betType[BET_TYPE::TIE] = _textureCache->addImage("betting_manager/bet_tie.png");
	_betType[BET_TYPE::BIG] = _textureCache->addImage("betting_manager/bet_big.png");
	_betType[BET_TYPE::SMALL] = _textureCache->addImage("betting_manager/bet_small.png");
	_betType[BET_TYPE::NONE] = _textureCache->addImage("betting_manager/bet_none.png");

	_betBoard = Sprite::createWithTexture(_betType[BET_TYPE::NONE]);
	_betBoard->setPosition(_center);
	this->addChild(_betBoard);

	auto field_pn = ImageView::create("betting_manager/touch_field.png");
	field_pn->setOpacity(0);
	field_pn->setTag(BET_TYPE::PLAYER_NATURAL);
	field_pn->setTouchEnabled(true);
	field_pn->addClickEventListener(CC_CALLBACK_1(BettingManager::onBettingTypeTouched, this));
	field_pn->setPosition(Vec2(250, 378));
	_betBoard->addChild(field_pn);

	auto field_p = field_pn->clone();
	field_p->setTag(BET_TYPE::PLAYER);
	field_p->setPosition(Vec2(575, 378));
	_betBoard->addChild(field_p);

	auto field_pp = field_pn->clone();
	field_pp->setTag(BET_TYPE::PLAYER_PAIR);
	field_pp->setPosition(Vec2(900, 378));
	_betBoard->addChild(field_pp);

	auto field_big = field_pn->clone();
	field_big->setTag(BET_TYPE::BIG);
	field_big->setPosition(Vec2(230, 250));
	_betBoard->addChild(field_big);

	auto field_tie = field_pn->clone();
	field_tie->setTag(BET_TYPE::TIE);
	field_tie->setPosition(Vec2(575, 250));
	_betBoard->addChild(field_tie);

	auto field_small = field_pn->clone();
	field_small->setTag(BET_TYPE::SMALL);
	field_small->setPosition(Vec2(920, 250));
	_betBoard->addChild(field_small);

	auto field_bn = field_pn->clone();
	field_bn->setTag(BET_TYPE::BANKER_NATURAL);
	field_bn->setPosition(Vec2(200, 100));
	_betBoard->addChild(field_bn);

	auto field_b = field_pn->clone();
	field_b->setTag(BET_TYPE::BANKER);
	field_b->setPosition(Vec2(575, 100));
	_betBoard->addChild(field_b);

	auto field_bp = field_pn->clone();
	field_bp->setTag(BET_TYPE::BANKER_PAIR);
	field_bp->setPosition(Vec2(950, 100));
	_betBoard->addChild(field_bp);
}
void BettingManager::initBettingInfo()
{
	auto bg_potChips = Sprite::create("betting_manager/bg_pot_money.png");
	bg_potChips->setPosition(Vec2(960, 1010));
	this->addChild(bg_potChips);

	_potChips = Label::createWithTTF("0", _font, 40);
	_potChips->setAnchorPoint(Point(1, 0.5));
	_potChips->setPosition(Vec2(bg_potChips->getContentSize().width - 50, bg_potChips->getContentSize().height / 2));
	bg_potChips->addChild(_potChips);

	auto bg_myChips = Sprite::create("betting_manager/bg_my_chip.png");
	bg_myChips->setPosition(Vec2(960, 270));
	this->addChild(bg_myChips);
	
	_myChips = Label::createWithTTF("0", _font, 30);
	_myChips->setAnchorPoint(Point(1, 0.5));
	_myChips->setPosition(Vec2(bg_myChips->getContentSize().width - 50, bg_myChips->getContentSize().height / 2));
	bg_myChips->addChild(_myChips);
}
void BettingManager::reset()
{
	_selectedType = BET_TYPE::NONE;
	_betBoard->setTexture(_betType[BET_TYPE::NONE]);

	_selectedType = BET_TYPE::NONE;

	_trialBet.reset();
	_finalBet.reset();

	_potChips->setString("0");
	_myChips->setString(stringToMoney(_user->getChips()));

	_isBetted = false;
	_isOpened = false;	
}
void BettingManager::setDelegate(BettingManagerDelegate *bmd)
{
	_delegate = bmd;
}
void BettingManager::enable()
{
	for (auto iter : _betMenu->getChildren())
	{
		((MenuItemImage*)iter)->setEnabled(true);
	}	

	_betBoard->setVisible(true);
}
void BettingManager::disable()
{
	for (auto iter : _betMenu->getChildren())
	{
		((MenuItemImage*)iter)->setEnabled(false);
	}

	_betBoard->setVisible(false);
}
void BettingManager::onBettingTypeTouched(Ref* sender)
{
	auto bt = static_cast<ImageView*>(sender);
	_betBoard->setTexture(_betType[bt->getTag()]);

	_selectedType = bt->getTag();
}
void BettingManager::onChipTouched(Ref *sender, int money)
{
	int max = 1000000;

	if (BET_TYPE::PLAYER <= _selectedType && _selectedType <= BET_TYPE::SMALL) {

		if (money == -1) {	// max betting

			if ((max - (_trialBet._total + _finalBet._total)) > 1000) {

				int remain = max - (_trialBet._total + _finalBet._total);
				remain = (remain / 1000) * 1000;

				if (_user->getChipsInt() - _trialBet._total < remain) {

					remain = (_user->getChipsInt() / 1000) * 1000;
				}
				_trialBet._type[_selectedType] += remain;
				_trialBet._total += remain;
			}
			else {


				auto mg = MessageGuide::getInstance();
				this->addChild(mg->create(MessageGuide::NORMAL, "You can bet maximum 1000000"));
			}
		}
		else  //
		{
			if ((max - (_trialBet._total + _finalBet._total)) >= money) {

				if (_user->getChipsInt() - _trialBet._total >= money) {
				
					_trialBet._type[_selectedType] += money;
					_trialBet._total += money;
				}
				else {

					auto mg = MessageGuide::getInstance();
					this->addChild(mg->create(MessageGuide::NEGATIVE, "You have not money enough"));
				}
			}
			else {

				auto mg = MessageGuide::getInstance();
				this->addChild(mg->create(MessageGuide::NORMAL, "You can bet maximum 1000000"));
			}
		}

		_potChips->setString(stringToMoney(StringUtils::format("%d", _trialBet._total + _finalBet._total)));
		_myChips->setString(stringToMoney(StringUtils::format("%d", _user->getChipsInt() - _trialBet._total)));
	}
	else {

		auto mg = MessageGuide::getInstance();
		this->addChild(mg->create(MessageGuide::NEGATIVE, "Select Betting Type."));
	}
}
void BettingManager::onRebetting(Ref *sender)
{
	if (_isBetted) {

		auto mg = MessageGuide::getInstance();
		this->addChild(mg->create(MessageGuide::NEGATIVE, "already you new bet for this round."));
	}
	else {

		_finalBet = _previousBet;

		_potChips->setString(stringToMoney(StringUtils::format("%d", _trialBet._total + _finalBet._total)));
		_myChips->setString(stringToMoney(StringUtils::format("%d", _user->getChipsInt() - _trialBet._total)));
	}
}
void BettingManager::onBetting()
{
	if (_trialBet._total == 0) {
		
		auto mg = MessageGuide::getInstance();
		this->addChild(mg->create(MessageGuide::NEGATIVE, "Select type and betting your chip."));
	}
	else {
				
		_finalBet._total += _trialBet._total;
		for (int i = 0; i < COUNT_BET_TYPE; i++)
		{
			_finalBet._type[i] += _trialBet._type[i];
		}

		_trialBet.reset();

		_isBetted = true;	

		_delegate->onRequestBetting(_finalBet);

		auto mg = MessageGuide::getInstance();
		this->addChild(mg->create(MessageGuide::POSITIVE, "Betting Complete."));
	}
}
void BettingManager::onBettingCancel()
{
	_trialBet.reset();

	_potChips->setString(stringToMoney(StringUtils::format("%d", _finalBet._total)));
	_myChips->setString(stringToMoney(_user->getChips()));
}
void BettingManager::bettingOpen()
{
	if (!_isOpened) {
		enable();
		_isOpened = false;
	}
}
void BettingManager::bettingClose()
{
	disable();
	onBettingCancel();

	if (_isBetted) {

		_previousBet = _finalBet;		
	}
	else {

	}
}
void BettingManager::throwChip(int type, int money)
{
	std::string chipImgPath[5] = {
		"chip_5k_small.png",
		"chip_20k_small.png",
		"chip_100k_small.png",
		"chip_500k_small.png",
		"chip_1000k_small.png"
	};
	int chipSize[5] = { 5000, 20000, 100000, 500000, 1000000 };
	int chipCnt[5] = { 0, 0, 0, 0, 0 };
	int remainder = money;

	// 1. calculate chip count.
	for (int i = 4; i >= 0; i--)
	{
		chipCnt[i] = getRequiredChips(remainder, chipSize[i]);  // 1000k
		remainder = remainder - (chipCnt[i] * chipSize[i]);
	}
	
	// 2. find bet type
	for (auto iter : _betBoard->getChildren())
	{
		if (iter->getTag() == type)
		{

		}
	}

	// 3. find chip's position.


	// 4. create chip sprite and adjust action each other.
	for (int j = 0; j < 5; j++)
	{
		for (int k = 0; k < chipCnt[j]; k++)
		{
			//auto chip = Sprite::create("betting_manager/" + chipImgPath[j]);
		}
	}
}
int BettingManager::getRequiredChips(int money, int chipSize)
{
	if (chipSize > money) {
		
		return 0;
	}
	else {

		return (money / chipSize);
	}
}