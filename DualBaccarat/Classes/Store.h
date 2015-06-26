#ifndef __STORE_H__
#define __STORE_H__

#include "PublicApi.h"
#include "ui/CocosGUI.h"
#include "ModuleDelegate.h"
#include "StoreDelegate.h"

USING_NS_CC;
using namespace ui;

class StoreItem
{
public:

	std::string _itemImage;
	std::string _priceImage;

	std::string _item;
	std::string _itemCode;
};

class Store : public cocos2d::Layer
{
public:

	enum class DIALOG_STATE
	{
		EXIST,
		NONE
	};

	Store();
	~Store();

	static Store* create();
	virtual bool init();
	void show();
	void destroy();
	void setDelegate(ModuleDelegate* md, StoreDelegate* sd);
	void setItems();
	Layout* setItemModel(StoreItem* item1, StoreItem* item2);
	void setStore();

private:

	void onItemSelected(Ref *pSender, Widget::TouchEventType type);
	void onExitClicked(Ref *pSender, Widget::TouchEventType type);

	void onItemPurchaseOK(Ref *pSender, Widget::TouchEventType type);
	void onItemPurchaseCancel(Ref *pSender, Widget::TouchEventType type);

	ListView *_listView;
	ModuleDelegate *_moduleDelegate;
	StoreDelegate *_delegate;

	std::vector<StoreItem*> _items;

	Sprite* bg_store;

	DIALOG_STATE _dialog_state;
};

#endif // __STORE_H__
