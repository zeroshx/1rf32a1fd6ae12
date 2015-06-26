#include "NoticeBoard.h"

NoticeBoard::NoticeBoard()
{		
}
NoticeBoard::~NoticeBoard()
{
}
NoticeBoard* NoticeBoard::create()
{
	NoticeBoard *notice = new (std::nothrow) NoticeBoard();
	if (notice && notice->init())
	{
		notice->autorelease();
		return notice;
	}
	CC_SAFE_DELETE(notice);
	return nullptr;
}
bool NoticeBoard::init()
{
	setContentSize(_visibleSize);
		
	_bg_notice = Sprite::create("notice/bg_notice_board.png");
	_bg_notice->setPosition(_center);
	this->addChild(_bg_notice);

	auto exitBtn = Button::create("common/button_normal.png", "common/button_pressed.png");
	exitBtn->setTitleText("EXIT");
	exitBtn->setTitleFontSize(40);
	exitBtn->setPosition(Vec2(_bg_notice->getContentSize().width / 2, 50));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(NoticeBoard::onExitClicked, this));
	_bg_notice->addChild(exitBtn);

	auto bg_notice_list = Sprite::create("notice/bg_notice_list.png");
	bg_notice_list->setPosition(_bg_notice->getContentSize() / 2);
	_bg_notice->addChild(bg_notice_list);
	
	_listView = ListView::create();
	_listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_listView->setTouchEnabled(true);
	_listView->setBounceEnabled(true);
	_listView->setContentSize(Size(1100, 650));
	_listView->setAnchorPoint(Point(0.5, 0.5));
	_listView->setPosition(Vec2(bg_notice_list->getContentSize() / 2));
	_listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
	_listView->setItemsMargin(10);
	bg_notice_list->addChild(_listView);
	
	this->setScale(0);
	this->setOpacity(0);

	setNotices();
	setNoticeBoard();

	return true;
}
void NoticeBoard::onExitClicked(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		destroy();
	}
} 
void NoticeBoard::onBackClicked(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		Button *btn = static_cast<Button*>(pSender);
		auto dialog = btn->getParent();		
		dialog->removeAllChildren();
		dialog->removeFromParent();		
	}
}
void NoticeBoard::onNoticeSelected(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		
		Notice* selectedItem = nullptr;

		Button *btn = static_cast<Button*>(pSender);

		//find item in item list
		for (auto iter : _notices)
		{
			if (iter->_id == btn->getName())
			{
				selectedItem = iter;
				break;
			}
		}

		auto bg_dialog = Sprite::create("notice/bg_detail_dialog.png");
		bg_dialog->setPosition(_bg_notice->getContentSize() / 2);
		_bg_notice->addChild(bg_dialog);

		auto title = Label::createWithTTF(selectedItem->_title, _font, 40);
		title->setAnchorPoint(Point(0, 0.5));
		title->setPosition(Vec2(70, 630));
		bg_dialog->addChild(title);

		auto content = Label::createWithTTF(selectedItem->_content, _font, 30);
		content->setAnchorPoint(Point(0, 1));
		content->setPosition(Vec2(70, 540));
		bg_dialog->addChild(content);

		auto btn_back = Button::create("notice/bg_back_normal.png", "notice/bg_back_pressed.png");
		btn_back->setPosition(Vec2(1000, 630));
		btn_back->addTouchEventListener(CC_CALLBACK_2(NoticeBoard::onBackClicked, this));
		bg_dialog->addChild(btn_back);

		bg_dialog->setScale(0);
		bg_dialog->setOpacity(0);

		auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
		auto action_1 = FadeIn::create(0.5);
		auto action = Spawn::create(action_0, action_1, NULL);
		bg_dialog->runAction(action);
	}
}
void NoticeBoard::show()
{
	_moduleDelegate->onModuleBegan();

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	this->runAction(action);
	_director->getRunningScene()->addChild(this, 2);
}
void NoticeBoard::destroy()
{
	_moduleDelegate->onModuleEnded();

	this->removeAllChildren();
	this->removeFromParent();
}
void NoticeBoard::setDelegate(ModuleDelegate* md)
{
	_moduleDelegate = md;
}
void NoticeBoard::setNotices()
{
	for (int i = 0; i < 5; i++)
	{
		auto notice = new Notice();
		notice->_id = StringUtils::format("%da%db%dc", i, i, i);
		notice->_title = StringUtils::format("Title %d", i);
		notice->_content = "fddajlksfjsalkfjaklfjalkfjklajfklaflk\nfjddkalsfjalksfjlksaj\ndfjkaljflk";
		_notices.push_back(notice);
	}
}
Layout* NoticeBoard::setItemModel(Notice* notice)
{
	Layout* layout = Layout::create();
	layout->setTouchEnabled(true);
	layout->setContentSize(Size(1100, 100));

	auto bg_notice = Button::create("notice/bg_notice_normal.png", "notice/bg_notice_pressed.png");
	bg_notice->setName(notice->_id);
	bg_notice->setPosition(bg_notice->getContentSize() / 2);
	bg_notice->addTouchEventListener(CC_CALLBACK_2(NoticeBoard::onNoticeSelected, this));
	layout->addChild(bg_notice);

	auto title = Text::create(notice->_title, _font, 40);
	title->setAnchorPoint(Point(0, 0.5));
	title->setPosition(Vec2(20, bg_notice->getContentSize().height / 2));
	title->setTextVerticalAlignment(TextVAlignment::CENTER);
	title->setTextHorizontalAlignment(TextHAlignment::LEFT);
	bg_notice->addChild(title);

	auto detail = ImageView::create("notice/detail.png");
	detail->setPosition(Vec2(950, 50));
	bg_notice->addChild(detail);
	
	return layout;
}
void NoticeBoard::setNoticeBoard()
{
	for (auto iter : _notices)
	{
		_listView->addChild(setItemModel(iter));
	}
}