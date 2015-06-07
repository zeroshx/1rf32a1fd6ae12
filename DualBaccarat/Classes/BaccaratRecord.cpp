#include "BaccaratRecord.h"

USING_NS_CC;

BaccaratRecord::BaccaratRecord()
{
}
BaccaratRecord::~BaccaratRecord()
{
}
BaccaratRecord* BaccaratRecord::create()
{
	BaccaratRecord *record = new (std::nothrow) BaccaratRecord();
	if (record && record->init())
	{
		record->autorelease();
		return record;
	}
	else
	{
		CC_SAFE_DELETE(record);
		return nullptr;
	}
}

// on "init" you need to initialize your instance
bool BaccaratRecord::init()
{
	setContentSize(_visibleSize);

	_bg_prototype = Sprite::create("baccarat_record/bg_exterior.png");
	_bg_prototype->setAnchorPoint(Point(0, 0));
	_bg_prototype->setPosition(0, 0);
	this->addChild(_bg_prototype);

	_bg_scoreBoard = Sprite::create("baccarat_record/bg_scoreboard.png");
	_bg_scoreBoard->setAnchorPoint(Point(0, 0));
	_bg_scoreBoard->setPosition(Vec2(40, 500));
	this->addChild(_bg_scoreBoard);

	_scoreType[SCORE_TYPE::BANKER] = ScoreboardItem::create("baccarat_record/banker.png",
		"baccarat_record/name_banker.png");
	_scoreType[SCORE_TYPE::BANKER]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::BANKER]->setPosition(Vec2(20, 370));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::BANKER]);

	_scoreType[SCORE_TYPE::PLAYER] = ScoreboardItem::create("baccarat_record/player.png",
		"baccarat_record/name_player.png");
	_scoreType[SCORE_TYPE::PLAYER]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::PLAYER]->setPosition(Vec2(20, 300));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::PLAYER]);

	_scoreType[SCORE_TYPE::TIE] = ScoreboardItem::create("baccarat_record/tie.png",
		"baccarat_record/name_tie.png");
	_scoreType[SCORE_TYPE::TIE]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::TIE]->setPosition(Vec2(20, 230));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::TIE]);

	_scoreType[SCORE_TYPE::BANKER_PAIR] = ScoreboardItem::create("baccarat_record/pair_b.png",
		"baccarat_record/name_banker_pair.png");
	_scoreType[SCORE_TYPE::BANKER_PAIR]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::BANKER_PAIR]->setPosition(Vec2(20, 160));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::BANKER_PAIR]);

	_scoreType[SCORE_TYPE::PLAYER_PAIR] = ScoreboardItem::create("baccarat_record/pair_p.png",
		"baccarat_record/name_player_pair.png");
	_scoreType[SCORE_TYPE::PLAYER_PAIR]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::PLAYER_PAIR]->setPosition(Vec2(20, 90));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::PLAYER_PAIR]);

	_scoreType[SCORE_TYPE::TOTAL] = ScoreboardItem::create("baccarat_record/icon_totalscore.png",
		"baccarat_record/name_totalscore.png");
	_scoreType[SCORE_TYPE::TOTAL]->setAnchorPoint(Point(0, 0));
	_scoreType[SCORE_TYPE::TOTAL]->setPosition(Vec2(20, 20));
	_bg_scoreBoard->addChild(_scoreType[SCORE_TYPE::TOTAL]);

	_bg_boneFrame = Sprite::create("baccarat_record/bg_interior.png");
	_bg_boneFrame->setPosition(_center);
	_bg_boneFrame->setScale(0);
	_bg_boneFrame->setOpacity(0);
	this->addChild(_bg_boneFrame);

	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setAnchorPoint(Point(0, 0));
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setContentSize(BASE_FRAME_SIZE);
	scrollView->setInnerContainerSize(BASE_CONTENT_SIZE);
	scrollView->setPosition(Vec2(20, 420));
	_bg_boneFrame->addChild(scrollView);

	_bg_base = Sprite::create("baccarat_record/bg_base.png");
	_bg_base->setAnchorPoint(Point(0, 0));
	_bg_base->setPosition(Vec2(0, 0));
	scrollView->addChild(_bg_base);

	ui::ScrollView* scrollView2 = ui::ScrollView::create();
	scrollView2->setAnchorPoint(Point(0, 0));
	scrollView2->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView2->setContentSize(DIV_FRAME_SIZE);
	scrollView2->setInnerContainerSize(DIV_CONTENT_SIZE);
	scrollView2->setPosition(Vec2(20, 220));
	_bg_boneFrame->addChild(scrollView2);

	_bg_divination[0] = Sprite::create("baccarat_record/bg_divination.png");
	_bg_divination[0]->setAnchorPoint(Point(0, 0));
	_bg_divination[0]->setPosition(Vec2(0, 0));
	scrollView2->addChild(_bg_divination[0]);

	ui::ScrollView* scrollView3 = ui::ScrollView::create();
	scrollView3->setAnchorPoint(Point(0, 0));
	scrollView3->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView3->setContentSize(DIV2_FRAME_SIZE);
	scrollView3->setInnerContainerSize(DIV_CONTENT_SIZE);
	scrollView3->setPosition(Vec2(20, 20));
	_bg_boneFrame->addChild(scrollView3);

	_bg_divination[1] = Sprite::create("baccarat_record/bg_divination.png");
	_bg_divination[1]->setAnchorPoint(Point(0, 0));
	_bg_divination[1]->setPosition(Vec2(0, 0));
	scrollView3->addChild(_bg_divination[1]);

	ui::ScrollView* scrollView4 = ui::ScrollView::create();
	scrollView4->setAnchorPoint(Point(0, 0));
	scrollView4->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView4->setContentSize(DIV2_FRAME_SIZE);
	scrollView4->setInnerContainerSize(DIV_CONTENT_SIZE);
	scrollView4->setPosition(Vec2(840, 20));
	_bg_boneFrame->addChild(scrollView4);

	_bg_divination[2] = Sprite::create("baccarat_record/bg_divination.png");
	_bg_divination[2]->setAnchorPoint(Point(0, 0));
	_bg_divination[2]->setPosition(Vec2(0, 0));
	scrollView4->addChild(_bg_divination[2]);

	_bg_nextRecord = Sprite::create("baccarat_record/bg_nextrecord.png");
	_bg_nextRecord->setAnchorPoint(Point(0, 0));
	_bg_nextRecord->setPosition(Vec2(1420, 420));
	_bg_boneFrame->addChild(_bg_nextRecord);

	_bg_recommend = Sprite::create("baccarat_record/bg_recommend.png");
	_bg_recommend->setAnchorPoint(Point(0, 0));
	_bg_recommend->setPosition(Vec2(1420, 220));
	_bg_boneFrame->addChild(_bg_recommend);	

	auto frameTrigger = MenuItemImage::create(
		"baccarat_record/btn_divination_normal.png",
		"baccarat_record/btn_divination_selected.png",
		CC_CALLBACK_1(BaccaratRecord::onFrameTriggered, this));
	frameTrigger->setAnchorPoint(Point(0, 0));
	frameTrigger->setPosition(Vec2(0, 120));

	auto _menu = Menu::create(frameTrigger, NULL);
	_menu->setPosition(Vec2::ZERO);
	this->addChild(_menu, 1);
	
	_state = MODULE_STATE::IDLE;
	reset();
    return true;
}
void BaccaratRecord::onFrameTriggered(Ref *pSender)
{
	if (_state == MODULE_STATE::IDLE) {

		_state = MODULE_STATE::START;
		show();
	}
	else if (_state == MODULE_STATE::DONE) {

		hide();
		_state = MODULE_STATE::IDLE;
	}
}
void BaccaratRecord::show()
{	
	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action_2 = Spawn::create(action_0, action_1, NULL);
	auto action_3 = CallFunc::create(CC_CALLBACK_0(BaccaratRecord::onFrameAnimCompleted, this));
	auto action = Sequence::create(action_2, action_3, NULL);
	_bg_boneFrame->runAction(action);	
}
void BaccaratRecord::onFrameAnimCompleted()
{
	_state = MODULE_STATE::DONE;
}
void BaccaratRecord::hide()
{
	_bg_boneFrame->setScale(0);
	_bg_boneFrame->setOpacity(0);	
}
void BaccaratRecord::reset()
{
	_lastBase = nullptr;
	_lastPrototype = nullptr;
	_lastDivination[0] = nullptr;
	_lastDivination[1] = nullptr;
	_lastDivination[2] = nullptr;

	for (int i = 0; i < PROTOTYPE_LENGTH; i++)
	{
		_prototype[i].reset();
	}

	for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
	{
		for (int j = 0; j < BASE_HEIGHT_LENGTH; j++)
		{
			_base[i][j].reset();
			_divination[0][i][j].reset();
			_divination[1][i][j].reset();
			_divination[2][i][j].reset();
		}
	}

	for (int i = 0; i < 3; i++)
	{
		_nextRecord[0][i].reset();
		_nextRecord[1][i].reset();
	}

	for (int i = 0; i < 6; i++)
	{
		_scoreboard[i] = 0;
	}

	_recommend.reset();

	_bg_prototype->removeAllChildren();
	_bg_base->removeAllChildren();
	_bg_divination[0]->removeAllChildren();
	_bg_divination[1]->removeAllChildren();
	_bg_divination[2]->removeAllChildren();
	_bg_nextRecord->removeAllChildren();
	_bg_recommend->removeAllChildren();

	_scoreType[SCORE_TYPE::BANKER]->setScore("0");
	_scoreType[SCORE_TYPE::PLAYER]->setScore("0");
	_scoreType[SCORE_TYPE::TIE]->setScore("0");
	_scoreType[SCORE_TYPE::BANKER_PAIR]->setScore("0");
	_scoreType[SCORE_TYPE::PLAYER_PAIR]->setScore("0");
	_scoreType[SCORE_TYPE::TOTAL]->setScore("0");
}
void BaccaratRecord::push(Winner winner, Pair pair)
{
	// 1. make record 1D chart
	chartPrototype(winner, pair);

	// 2. make record 2D chart
	chartBase(winner, pair);

	// 3. make divination chart
	chartDivination(DIV_DEPTH::FIRST);
	chartDivination(DIV_DEPTH::SECOND);
	chartDivination(DIV_DEPTH::THIRD);

	// 4. find next item record
	chartNextRecord(winner);

	// 5. find next item will be recommended.
	findRecommendedItem();

	// 6. change score of scoreboard
	updateScoreboard(winner, pair);
}
void BaccaratRecord::drawLatestRecord()
{
	drawLatestPrototype();

	drawLatestBase();

	drawLatestDivination(DIV_DEPTH::FIRST);

	drawLatestDivination(DIV_DEPTH::SECOND);

	drawLatestDivination(DIV_DEPTH::THIRD);

	drawNextRecord();

	drawRecommendedItem();
}
void BaccaratRecord::chartPrototype(Winner winner, Pair pair)
{
	if (winner == Winner::NONE) {

		return;
	}
	if (!_lastPrototype) {

		_prototype[0]._number = 1;
		_prototype[0]._x = 0;
		_lastPrototype = &_prototype[0];
	}
	else {

		if (_lastPrototype->_x == PROTOTYPE_LENGTH - 1) {

			for (int i = 1; i < PROTOTYPE_LENGTH - 1; i++)
			{
				_prototype[i - 1] = _prototype[i];
				_prototype[i - 1]._x = i - 1;
			}

			_prototype[PROTOTYPE_LENGTH - 1]._number = _lastPrototype->_number + 1;
			_prototype[PROTOTYPE_LENGTH - 1]._x = PROTOTYPE_LENGTH - 1;
			_lastPrototype = &_prototype[PROTOTYPE_LENGTH - 1];
		}
		else {

			_prototype[_lastPrototype->_x + 1]._number = _lastPrototype->_number + 1;
			_prototype[_lastPrototype->_x + 1]._x = _lastPrototype->_x + 1;
			_lastPrototype = &_prototype[_lastPrototype->_x + 1];
		}
	}

	_lastPrototype->_isUsed = true;
	_lastPrototype->_winner = winner;
	_lastPrototype->_pair = pair;
}
void BaccaratRecord::chartBase(Winner winner, Pair pair)
{
	if (winner == Winner::TIE || winner == Winner::NONE) {

		return;
	}

	bool isFailed = false;

	if (!_lastBase) {

		_base[0][0]._x = 0;
		_base[0][0]._y = 0;		
		_base[0][0]._number = 1;
		_base[0][0]._row = 0;
		_base[0][0]._column = 0;
		_base[0][0]._columnCount = 0;
		_base[0][0]._root = &_base[0][0];
		_lastBase = &_base[0][0];
	}
	else {

		if (_lastBase->_winner == winner) {

			if (_lastBase->_y == BASE_HEIGHT_LENGTH - 1) {

				if (_lastBase->_x + 1 < BASE_WIDTH_LENGTH) {
					
					_base[_lastBase->_x + 1][_lastBase->_y]._number = _lastBase->_number + 1;
					_base[_lastBase->_x + 1][_lastBase->_y]._x = _lastBase->_x + 1;
					_base[_lastBase->_x + 1][_lastBase->_y]._y = _lastBase->_y;
					_base[_lastBase->_x + 1][_lastBase->_y]._column = _lastBase->_column + 1;
					_base[_lastBase->_x + 1][_lastBase->_y]._row = _lastBase->_row;
					_base[_lastBase->_x + 1][_lastBase->_y]._root = _lastBase->_root;
					_lastBase = &_base[_lastBase->_x + 1][_lastBase->_y];
				}
				else {

					isFailed = true;
				}
			}
			else {

				if (!_base[_lastBase->_x][_lastBase->_y + 1]._isUsed) {

					_base[_lastBase->_x][_lastBase->_y + 1]._number = _lastBase->_number + 1;
					_base[_lastBase->_x][_lastBase->_y + 1]._x = _lastBase->_x;
					_base[_lastBase->_x][_lastBase->_y + 1]._y = _lastBase->_y + 1;
					_base[_lastBase->_x][_lastBase->_y + 1]._column = _lastBase->_column + 1;
					_base[_lastBase->_x][_lastBase->_y + 1]._row = _lastBase->_row;
					_base[_lastBase->_x][_lastBase->_y + 1]._root = _lastBase->_root;
					_lastBase = &_base[_lastBase->_x][_lastBase->_y + 1];
				}
				else {

					if (_lastBase->_x + 1 < BASE_WIDTH_LENGTH) {

						_base[_lastBase->_x + 1][_lastBase->_y]._number = _lastBase->_number + 1;
						_base[_lastBase->_x + 1][_lastBase->_y]._x = _lastBase->_x + 1;
						_base[_lastBase->_x + 1][_lastBase->_y]._y = _lastBase->_y;
						_base[_lastBase->_x + 1][_lastBase->_y]._column = _lastBase->_column + 1;
						_base[_lastBase->_x + 1][_lastBase->_y]._row = _lastBase->_row;
						_base[_lastBase->_x + 1][_lastBase->_y]._root = _lastBase->_root;
						_lastBase = &_base[_lastBase->_x + 1][_lastBase->_y];
					}
					else {

						isFailed = true;
					}
				}
			}
		}
		else { // _lastBase->_result != result

			int x = -1;

			for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
			{
				if (_base[i][0]._isUsed == false && _base[i][1]._isUsed == false)
				{
					x = i;
					break;
				}
			}
			if (x != -1) {

				_base[x][0]._x = x;
				_base[x][0]._y = 0;
				_base[x][0]._row = _lastBase->_row + 1;
				_base[x][0]._column = 0;
				_base[x][0]._columnCount = 0;
				_base[x][0]._root = &_base[x][0];
				_base[x][0]._number = _lastBase->_number + 1;
				_lastBase = &_base[x][0];
			}
			else {

				isFailed = true;
			}
		}
	}

	if (!isFailed) {

		_lastBase->_winner = winner;
		_lastBase->_pair = pair;
		_lastBase->_isUsed = true;
		_lastBase->_root->_columnCount++;
	}
}
void BaccaratRecord::chartDivination(DIV_DEPTH depth)
{
	if (!_lastBase || _lastBase->_isDrawn) {

		return;
	}
	else if (!_base[depth][0]._isUsed || _lastBase->_number <= _base[depth][0]._number) {
		
		return;
	}

	bool isFailed = false;
	Continuation continuation;
	BaccaratRecordItem* previousItem;

	// 1. find previous item
	for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
	{
		for (int j = 0; j < BASE_HEIGHT_LENGTH; j++)
		{
			if (_base[i][j]._number == _lastBase->_number - 1) {

				previousItem = &_base[i][j];
			}
		}
	}

	// 2. select solution
	if (_lastBase->_winner == findNextConsecutiveItem(previousItem, depth)) {

		continuation = Continuation::KEEP;
	}
	else {

		continuation = Continuation::INVERSE;
	}

	// 3. add to chart
	if (!_lastDivination[depth - 1]) {

		_divination[depth - 1][0][0]._x = 0;
		_divination[depth - 1][0][0]._y = 0;
		_lastDivination[depth - 1] = &_divination[depth - 1][0][0];
	}
	else {
		
		if (_lastDivination[depth - 1]->_continuation == continuation) {

			if (_lastDivination[depth - 1]->_y == BASE_HEIGHT_LENGTH - 1) {

				if (_lastDivination[depth - 1]->_x + 1 < BASE_WIDTH_LENGTH) {
					
					_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y]._x = _lastDivination[depth - 1]->_x + 1;
					_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y]._y = _lastDivination[depth - 1]->_y;
					_lastDivination[depth - 1] = &_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y];
				}
				else {

					isFailed = true;
				}
			}
			else {

				if (!_divination[depth - 1][_lastDivination[depth - 1]->_x][_lastDivination[depth - 1]->_y + 1]._isUsed) {

					_divination[depth - 1][_lastDivination[depth - 1]->_x][_lastDivination[depth - 1]->_y + 1]._x = _lastDivination[depth - 1]->_x;
					_divination[depth - 1][_lastDivination[depth - 1]->_x][_lastDivination[depth - 1]->_y + 1]._y = _lastDivination[depth - 1]->_y + 1;
					_lastDivination[depth - 1] = &_divination[depth - 1][_lastDivination[depth - 1]->_x][_lastDivination[depth - 1]->_y + 1];

				}
				else {

					if (_lastDivination[depth - 1]->_x + 1 < BASE_WIDTH_LENGTH) {

						_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y]._x = _lastDivination[depth - 1]->_x + 1;
						_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y]._y = _lastDivination[depth - 1]->_y;
						_lastDivination[depth - 1] = &_divination[depth - 1][_lastDivination[depth - 1]->_x + 1][_lastDivination[depth - 1]->_y];
					}
					else {

						isFailed = true;
					}
				}
			}
		}
		else { // _lastBase->_result != result

			int x = -1;

			for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
			{
				if (_divination[depth - 1][i][0]._isUsed == false && _divination[depth - 1][i][1]._isUsed == false)
				{
					x = i;
					break;
				}
			}
			if (x != -1) {

				_divination[depth - 1][x][0]._x = x;
				_divination[depth - 1][x][0]._y = 0;
				_lastDivination[depth - 1] = &_divination[depth - 1][x][0];
			}
			else {

				isFailed = true;
			}
		}
	}

	if (!isFailed) {

		_lastDivination[depth - 1]->_continuation = continuation;
		_lastDivination[depth - 1]->_isUsed = true;
	}
}
Winner BaccaratRecord::findNextConsecutiveItem(BaccaratRecordItem* lastItem, DIV_DEPTH depth)
{
	for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
	{
		if (_base[i][0]._row == lastItem->_row - depth) {

			if (_base[i][0]._columnCount == lastItem->_column + 1) {

				return lastItem->reverseWinner();
			}
			else {

				return lastItem->_winner;
			}
		}		
	}

	return Winner::NONE;
}
Winner BaccaratRecord::findNextConsecutiveItem(DIV_DEPTH depth)
{
	return findNextConsecutiveItem(_lastBase, depth);
}
void BaccaratRecord::chartNextRecord(Winner winner)
{
	Winner w[3];

	if (_lastBase->_number >= _base[1][0]._number) {

		w[0] = findNextConsecutiveItem(DIV_DEPTH::FIRST);
	}
	else {

		w[0] = Winner::NONE;
	}
	if (_lastBase->_number >= _base[2][0]._number) {

		w[1] = findNextConsecutiveItem(DIV_DEPTH::SECOND);
	}
	else {

		w[1] = Winner::NONE;
	}
	if (_lastBase->_number >= _base[3][0]._number) {

		w[2] = findNextConsecutiveItem(DIV_DEPTH::THIRD);
	}
	else {

		w[2] = Winner::NONE;
	}

	for (int i = 0; i < 3; i++)
	{
		if (w[i] == Winner::PLAYER) {
					
			_nextRecord[SCORE_TYPE::BANKER][i]._continuation = Continuation::INVERSE;
			_nextRecord[SCORE_TYPE::PLAYER][i]._continuation = Continuation::KEEP;
		}
		else if (w[i] == Winner::BANKER) {

			_nextRecord[SCORE_TYPE::BANKER][i]._continuation = Continuation::KEEP;
			_nextRecord[SCORE_TYPE::PLAYER][i]._continuation = Continuation::INVERSE;
		}
		else {

			_nextRecord[SCORE_TYPE::BANKER][i]._continuation = Continuation::NONE;
			_nextRecord[SCORE_TYPE::PLAYER][i]._continuation = Continuation::NONE;
		}
	}
}
void BaccaratRecord::findRecommendedItem()
{
	int player = 0, banker = 0;

	for (int j = 0; j < 3; j++)
	{
		if (_nextRecord[SCORE_TYPE::BANKER][j]._continuation == Continuation::KEEP) {

			banker++;
		}
		else if (_nextRecord[SCORE_TYPE::PLAYER][j]._continuation == Continuation::KEEP) {

			player++;
		}
	}

	if (player > banker) {

		_recommend._winner = Winner::PLAYER;
	}
	else {

		_recommend._winner = Winner::BANKER;
	}
}
void BaccaratRecord::updateScoreboard(Winner winner, Pair pair)
{
	switch (winner)
	{
	case Winner::BANKER :

		_scoreboard[SCORE_TYPE::BANKER]++;
		break;

	case Winner::PLAYER :

		_scoreboard[SCORE_TYPE::PLAYER]++;
		break;

	case Winner::TIE :

		_scoreboard[SCORE_TYPE::TIE]++;
		break;
	}

	switch (pair)
	{
	case Pair::BANKER:

		_scoreboard[SCORE_TYPE::BANKER_PAIR]++;
		break;

	case Pair::PLAYER:

		_scoreboard[SCORE_TYPE::PLAYER_PAIR]++;
		break;

	}

	_scoreboard[SCORE_TYPE::TOTAL]++;

	_scoreType[SCORE_TYPE::BANKER]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::BANKER]));
	_scoreType[SCORE_TYPE::PLAYER]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::PLAYER]));
	_scoreType[SCORE_TYPE::TIE]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::TIE]));
	_scoreType[SCORE_TYPE::BANKER_PAIR]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::BANKER_PAIR]));
	_scoreType[SCORE_TYPE::PLAYER_PAIR]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::PLAYER_PAIR]));
	_scoreType[SCORE_TYPE::TOTAL]->setScore(StringUtils::format("%d", _scoreboard[SCORE_TYPE::TOTAL]));
}
void BaccaratRecord::drawPrototype()
{
	float interval = _bg_prototype->getContentSize().width / PROTOTYPE_LENGTH;
	float height = _bg_prototype->getContentSize().height / 2;

	for (int i = 0; i < PROTOTYPE_LENGTH; i++)
	{
		if (_prototype[i]._isUsed) {

			auto spr = Sprite::create(getImageName(RecordType::PROTOTYPE,
				_prototype[i]._winner, _prototype[i]._pair, _prototype[i]._continuation));
			spr->setAnchorPoint(Point(0, 0));
			spr->setPosition(i * interval, height);
			spr->setTag(_prototype[i]._number);
			_bg_prototype->addChild(spr);
		}
	}
}
void BaccaratRecord::drawLatestPrototype()
{
	float interval = _bg_prototype->getContentSize().width / PROTOTYPE_LENGTH;
	float height = _bg_prototype->getContentSize().height / 2;

	if (!_lastPrototype) {
		return;
	}

	auto spr = Sprite::create(getImageName(RecordType::PROTOTYPE,
		_lastPrototype->_winner, _lastPrototype->_pair, _lastPrototype->_continuation));
	spr->setAnchorPoint(Point(0, 0.5));	
	spr->setTag(_lastPrototype->_number);
	spr->setOpacity(0);
	_bg_prototype->addChild(spr);

	if (_lastPrototype->_number > PROTOTYPE_LENGTH) {

		spr->setPosition((_lastPrototype->_x + 1) * interval, height);

		for (auto iter : _bg_prototype->getChildren()){

			if (iter->getTag() == spr->getTag() - PROTOTYPE_LENGTH) {

				auto act1 = MoveBy::create(0.5f, Vec2(-interval, 0));
				auto act2 = RemoveSelf::create();
				auto act3 = Sequence::create(act1, act2, NULL);
				iter->runAction(act3);
			}
			else {
				
				auto act = MoveBy::create(0.5f, Vec2(-interval, 0));
				iter->runAction(act);
			}
		}
	}
	else {

		spr->setPosition(_lastPrototype->_x * interval, height);
	}

	auto act = FadeIn::create(0.5);
	spr->runAction(act);	
}
void BaccaratRecord::drawBase()
{
	float height = _bg_base->getContentSize().height;
	float interval = height / BASE_HEIGHT_LENGTH;

	for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
	{
		for (int j = 0; j < BASE_HEIGHT_LENGTH; j++)
		{
			if (_base[i][j]._isUsed) {

				auto spr = Sprite::create(getImageName(RecordType::BASE, _base[i][j]._winner, Pair::NONE, Continuation::NONE));
				spr->setAnchorPoint(Point(0, 1));
				spr->setPosition(i * interval, height - j * interval);
				_bg_base->addChild(spr);

				_base[i][j]._isDrawn = true;
			}
		}
	}
}
void BaccaratRecord::drawLatestBase()
{
	float height = _bg_base->getContentSize().height;
	float interval = height / BASE_HEIGHT_LENGTH;
	
	if (!_lastBase || _lastBase->_isDrawn) {
		return;
	}

	auto spr = Sprite::create(getImageName(RecordType::BASE, _lastBase->_winner, Pair::NONE, Continuation::NONE));
	spr->setAnchorPoint(Point(0, 1));
	spr->setPosition(_lastBase->_x * interval, height - _lastBase->_y * interval);
	spr->setOpacity(0);
	_bg_base->addChild(spr);

	auto act = FadeIn::create(0.5);
	spr->runAction(act);
	
	_lastBase->_isDrawn = true;
}
void BaccaratRecord::drawDivination(int depth)
{
	float height = _bg_divination[depth - 1]->getContentSize().height;
	float interval = height / BASE_HEIGHT_LENGTH;

	for (int i = 0; i < BASE_WIDTH_LENGTH; i++)
	{
		for (int j = 0; j < BASE_HEIGHT_LENGTH; j++)
		{
			if (_divination[depth - 1][i][j]._isUsed) {

				auto spr = Sprite::create(getImageName(RecordType::DIVINATION1TH, Winner::NONE, Pair::NONE, _divination[depth - 1][i][j]._continuation));
				spr->setAnchorPoint(Point(0, 1));
				spr->setPosition(i * interval, height - j * interval);
				_bg_divination[depth - 1]->addChild(spr);

				_divination[depth - 1][i][j]._isDrawn = true;
			}
		}
	}
}
void BaccaratRecord::drawLatestDivination(int depth)
{
	if (!_lastDivination[depth - 1] || _lastDivination[depth - 1]->_isDrawn) {
		return;
	}

	float height = _bg_divination[depth - 1]->getContentSize().height;
	float interval = height / BASE_HEIGHT_LENGTH;
	RecordType type;

	if (depth == DIV_DEPTH::FIRST) {
		type = RecordType::DIVINATION1TH;
	}
	else if (depth == DIV_DEPTH::SECOND) {
		type = RecordType::DIVINATION2ND;
	}
	else {
		type = RecordType::DIVINATION3RD;
	}
	
	auto spr = Sprite::create(getImageName(type, Winner::NONE, Pair::NONE, _lastDivination[depth - 1]->_continuation));
	spr->setAnchorPoint(Point(0, 1));
	spr->setPosition(_lastDivination[depth - 1]->_x * interval, height - _lastDivination[depth - 1]->_y * interval);
	spr->setOpacity(0);
	_bg_divination[depth - 1]->addChild(spr);

	auto act = FadeIn::create(0.5);
	spr->runAction(act);

	_lastDivination[depth - 1]->_isDrawn = true;
}
void BaccaratRecord::drawNextRecord()
{
	// div 1
	if (_nextRecord[0][0]._continuation != Continuation::NONE) {
			
		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV1TH, Winner::NONE, Pair::NONE, _nextRecord[0][0]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(30, 170));
		_bg_nextRecord->addChild(spr);
	}
	if (_nextRecord[1][0]._continuation != Continuation::NONE) {

		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV1TH, Winner::NONE, Pair::NONE, _nextRecord[1][0]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(110, 170));
		_bg_nextRecord->addChild(spr);
	}

	// div 2
	if (_nextRecord[0][1]._continuation != Continuation::NONE) {

		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV2ND, Winner::NONE, Pair::NONE, _nextRecord[0][1]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(30, 100));
		_bg_nextRecord->addChild(spr);
	}
	if (_nextRecord[1][1]._continuation != Continuation::NONE) {

		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV2ND, Winner::NONE, Pair::NONE, _nextRecord[1][1]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(110, 100));
		_bg_nextRecord->addChild(spr);
	}

	// div 3
	if (_nextRecord[0][2]._continuation != Continuation::NONE) {

		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV3RD, Winner::NONE, Pair::NONE, _nextRecord[0][2]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(30, 40));
		_bg_nextRecord->addChild(spr);
	}
	if (_nextRecord[1][2]._continuation != Continuation::NONE) {

		auto spr = Sprite::create(getImageName(RecordType::NEXT_DIV3RD, Winner::NONE, Pair::NONE, _nextRecord[1][2]._continuation));
		spr->setAnchorPoint(Point(0, 0));
		spr->setPosition(Vec2(110, 40));
		_bg_nextRecord->addChild(spr);
	}		
}
void BaccaratRecord::drawRecommendedItem()
{
	Sprite* spr;

	if (_recommend._winner == Winner::PLAYER) {

		spr = Sprite::create(getImageName(RecordType::BASE, Winner::PLAYER, Pair::NONE, Continuation::NONE));
	}
	else {

		spr = Sprite::create(getImageName(RecordType::BASE, Winner::BANKER, Pair::NONE, Continuation::NONE));
	}

	spr->setAnchorPoint(Point(0.5, 0.5));
	spr->setPosition(Vec2(100, 70));
	_bg_recommend->addChild(spr);
}
const std::string BaccaratRecord::getImageName(RecordType type, Winner winner, Pair pair, Continuation continuity)
{
	std::string name = "baccarat_record/";

	if (type == RecordType::NEXT_DIV1TH || type == RecordType::NEXT_DIV2ND || type == RecordType::NEXT_DIV3RD) {

		name += "next_";
	}

	if (type == RecordType::PROTOTYPE) {

		name += getStringForWinner(winner);
		name += getStringForPair(pair);
	}
	else if (type == RecordType::BASE) {

		name += getStringForWinner(winner);
	}
	else if (type == RecordType::DIVINATION1TH || type == RecordType::NEXT_DIV1TH) {

		name += "div1";
		name += getStringForContinuity(continuity);
	}
	else if (type == RecordType::DIVINATION2ND || type == RecordType::NEXT_DIV2ND) {

		name += "div2";
		name += getStringForContinuity(continuity);
	}
	else {	// DIVINATION3RD

		name += "div3";
		name += getStringForContinuity(continuity);
	}	

	return name + ".png";
}
const std::string BaccaratRecord::getStringForWinner(Winner winner)
{
	if (winner == Winner::PLAYER) {

		return "player";
	}
	else if (winner == Winner::BANKER) {

		return "banker";
	}
	else if (winner == Winner::TIE) {

		return "tie";
	}

	return "";
}
const std::string BaccaratRecord::getStringForPair(Pair pair)
{
	if (pair == Pair::PLAYER) {

		return "_p";
	}
	else if (pair == Pair::BANKER) {

		return "_b";
	}
	else if (pair == Pair::BOTH) {

		return "_pb";
	}

	return "";
}
const std::string BaccaratRecord::getStringForContinuity(Continuation continuation)
{
	if (continuation == Continuation::KEEP){

		return "_keep";
	}
	else if (continuation == Continuation::INVERSE) {

		return "_inverse";
	}

	return "";
}