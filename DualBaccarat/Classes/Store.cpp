#include "Store.h"

Store::Store()
{		
}
Store::~Store()
{
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
	setContentSize(_visibleSize);
		
	bg_store = Sprite::create("store/bg_store.png");
	bg_store->setPosition(_center);
	this->addChild(bg_store);

	auto exitBtn = Button::create("store/button_normal.png", "store/button_pressed.png");
	exitBtn->setTitleText("EXIT");
	exitBtn->setTitleFontSize(40);
	exitBtn->setPosition(Vec2(bg_store->getContentSize().width / 2, -40));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(Store::onExitClicked, this));
	bg_store->addChild(exitBtn);
		
	_listView = ListView::create();
	_listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	_listView->setTouchEnabled(true);
	_listView->setBounceEnabled(true);
	_listView->setContentSize(Size(1070, 820));
	_listView->setAnchorPoint(Point(0.5, 0.5));
	_listView->setPosition(Vec2(bg_store->getContentSize() / 2));
	_listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
	_listView->setItemsMargin(10);
	bg_store->addChild(_listView);	
	
	this->setScale(0);
	this->setOpacity(0);

	setItems();
	setStore();

	_dialog_state = DIALOG_STATE::NONE;

	return true;
}
void Store::onItemSelected(Ref *pSender, Widget::TouchEventType type)
{	
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_dialog_state == DIALOG_STATE::NONE) {

			_dialog_state = DIALOG_STATE::EXIST;

			StoreItem* selectedItem = nullptr;
			Button *btn = static_cast<Button*>(pSender);

			//find item in item list
			for (auto iter : _items)
			{
				if (iter->_item == btn->getName())
				{
					selectedItem = iter;
					break;
				}
			}

			//make confirm dialog
			auto bg_dialog = Sprite::create("store/bg_confirm_dialog.png");
			bg_dialog->setPosition(bg_store->getContentSize() / 2);
			bg_store->addChild(bg_dialog);

			auto item = Sprite::create(selectedItem->_itemImage);
			item->setPosition(Vec2(170, 220));
			item->setScale(0.7f);
			bg_dialog->addChild(item);

			auto price = Sprite::create(selectedItem->_priceImage);
			price->setPosition(Vec2(470, 220));
			bg_dialog->addChild(price);

			auto btn_ok = Button::create("store/button_normal.png", "store/button_pressed.png");
			btn_ok->setTitleText("OK");
			btn_ok->setTitleFontSize(40);
			btn_ok->setPosition(Vec2(200, 60));
			btn_ok->addTouchEventListener(CC_CALLBACK_2(Store::onItemPurchaseOK, this));
			bg_dialog->addChild(btn_ok);

			auto btn_cancel = Button::create("store/button_normal.png", "store/button_pressed.png");
			btn_cancel->setTitleText("CANCEL");
			btn_cancel->setTitleFontSize(40);
			btn_cancel->setPosition(Vec2(500, 60));
			btn_cancel->addTouchEventListener(CC_CALLBACK_2(Store::onItemPurchaseCancel, this));
			bg_dialog->addChild(btn_cancel);

			bg_dialog->setScale(0);
			bg_dialog->setOpacity(0);

			auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
			auto action_1 = FadeIn::create(0.5);
			auto action = Spawn::create(action_0, action_1, NULL);
			bg_dialog->runAction(action);
		}
	}
}
void Store::onExitClicked(Ref *pSender, Widget::TouchEventType type)
{	
	if (type == Widget::TouchEventType::ENDED)
	{		
		destroy();
	}
}
void Store::onItemPurchaseOK(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Button *btn = static_cast<Button*>(pSender);
		auto dialog = btn->getParent();
		CCLOG(__FUNCTION__);
		dialog->removeAllChildren();
		dialog->removeFromParent();

		_dialog_state = DIALOG_STATE::NONE;
	}
}	
void Store::onItemPurchaseCancel(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Button *btn = static_cast<Button*>(pSender);
		auto dialog = btn->getParent();
		CCLOG(__FUNCTION__);
		dialog->removeAllChildren();
		dialog->removeFromParent();

		_dialog_state = DIALOG_STATE::NONE;
	}
}
void Store::setDelegate(ModuleDelegate* md, StoreDelegate* sd)
{
	_moduleDelegate = md;
	_delegate = sd;
}
void Store::show()
{
	_moduleDelegate->onModuleBegan();

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	this->runAction(action);
	_director->getRunningScene()->addChild(this, 2);
}
void Store::destroy()
{
	_moduleDelegate->onModuleEnded();

	this->removeAllChildren();
	this->removeFromParent();
}
void Store::setItems()
{
	for (int i = 0; i < 29; i++)
	{
		StoreItem *item;
		item = new StoreItem();
		
		item->_item = StringUtils::format("Item %d", i);
		item->_itemCode = StringUtils::format("z%da%db%d", i, i, i);

		item->_itemImage = "store/item.png";
		item->_priceImage = "store/item_price.png";
		
		_items.push_back(item);
	}
}
Layout* Store::setItemModel(StoreItem* item1, StoreItem* item2)
{
	StoreItem *items[2];
	items[0] = item1;
	items[1] = item2;

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(Size(350, 810));

	for (int i = 0; i < 2; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		auto bg_model = ImageView::create("store/bg_item_model.png");
		bg_model->setAnchorPoint(Point(0, 0));

		auto bg_item = ImageView::create("store/bg_item.png");
		bg_item->setAnchorPoint(Point(0.5, 1));
		bg_item->setPosition(Vec2(bg_model->getContentSize().width / 2, bg_model->getContentSize().height - 30));
		bg_model->addChild(bg_item);

		auto itemImage = ImageView::create(items[i]->_itemImage);
		itemImage->setPosition(bg_item->getContentSize() / 2);
		bg_item->addChild(itemImage);

		auto bg_price = Button::create("store/bg_price_normal.png", "store/bg_price_pressed.png");
		bg_price->setName(items[i]->_item);
		bg_price->setAnchorPoint(Point(0.5, 0));
		bg_price->setPosition(Vec2(bg_model->getContentSize().width / 2, 30));
		bg_price->addTouchEventListener(CC_CALLBACK_2(Store::onItemSelected, this));
		bg_model->addChild(bg_price);

		auto priceImage = ImageView::create(items[i]->_priceImage);
		priceImage->setPosition(bg_price->getContentSize() / 2);
		bg_price->addChild(priceImage);

		bg_model->setPosition(Vec2(0, 410 - (410 * i)));
		default_item->addChild(bg_model);
	}

	return default_item;
}
void Store::setStore()
{
	int listCount = (_items.size() + 1) / 2;
	std::vector<StoreItem*> items;
	items = _items;
	
	for (int i = 0; i < listCount * 2; i += 2)
	{
		StoreItem* item1 = nullptr;
		if (!items.empty()) {
			item1 = items.front();
			items.erase(items.begin());
		}

		StoreItem* item2 = nullptr;
		if (!items.empty()) {
			item2 = items.front();
			items.erase(items.begin());
		}

		_listView->addChild(setItemModel(item1, item2));
	}
}