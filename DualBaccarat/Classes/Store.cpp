#include "Store.h"

Store::Store()
{		
}
Store::~Store()
{
}
const std::string& Store::getModuleName()
{
	const static std::string moduleName("Store");
	return moduleName;
}
Store* Store::create()
{
	Store *store = new (std::nothrow) Store();
	if (store && store->init())
	{
		store->autorelease();
		return store;
	}
	CC_SAFE_DELETE(store);
	return nullptr;
}
bool Store::init()
{
	if (_director->getRunningScene()->getChildByName(getModuleName())) {
		return false;
	}

	setContentSize(_visibleSize);
		
	auto bg_store = Sprite::create("store/bg_store.png");
	bg_store->setPosition(_center);
	this->addChild(bg_store);

	auto exitBtn = Button::create("store/button_normal.png", "store/button_pressed.png");
	exitBtn->setTitleText("EXIT");
	exitBtn->setTitleFontSize(40);
	exitBtn->setPosition(Vec2(bg_store->getContentSize().width / 2, 70));
	exitBtn->addTouchEventListener(CC_CALLBACK_0(Store::onExitClicked, this));
	bg_store->addChild(exitBtn);
		
	_listView = ListView::create();
	_listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	_listView->setTouchEnabled(true);
	_listView->setBounceEnabled(true);
	_listView->setContentSize(Size(1200, 500));
	_listView->setAnchorPoint(Point(0.5, 0.5));
	_listView->setPosition(Vec2(bg_store->getContentSize().width / 2.0f, bg_store->getContentSize().height / 2.0f));
	_listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(Store::onItemSelected, this));
	_listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
	_listView->setItemsMargin(20);
	bg_store->addChild(_listView);

	this->setName(getModuleName());

	return true;
}
void Store::onItemSelected(Ref *pSender, ListView::EventType type)
{
	if (type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END)
	{
		ListView* listView = static_cast<ListView*>(pSender);
		CC_UNUSED_PARAM(listView);
		CCLOG("select child end index = %ld", listView->getCurSelectedIndex());

		CCLOG("%s", listView->getItem(listView->getCurSelectedIndex())->getChildByName("Title Button")->getName().c_str());
	}
}
void Store::onExitClicked()
{
	CCLOG(__FUNCTION__);
	this->removeAllChildren();
	this->removeFromParent();
}