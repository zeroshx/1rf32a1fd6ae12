#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class Store : public cocos2d::Layer
{
public:

	Store();
	~Store();

	const std::string& getModuleName();

	static Store* create();
	virtual bool init();

private:

	void onItemSelected(Ref *pSender, ListView::EventType type);
	void onExitClicked();

	ListView *_listView;
};

#endif // __STORE_H__
