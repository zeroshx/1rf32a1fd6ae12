#ifndef __NOTICE_BOARD_H__
#define __NOTICE_BOARD_H__

#include "PublicApi.h"
#include "ModuleDelegate.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class Notice
{
public :

	std::string _id;
	std::string _title;
	std::string _content;
};

class NoticeBoard : public cocos2d::Layer
{
public:

	NoticeBoard();
	~NoticeBoard();

	static NoticeBoard* create();
	virtual bool init();
	void show();
	void destroy();
	void setDelegate(ModuleDelegate* md);
	Layout* setItemModel(Notice* notice);
	void setNotices();
	void setNoticeBoard();

private:

	void onNoticeSelected(Ref *pSender, Widget::TouchEventType type);
	void onExitClicked(Ref *pSender, Widget::TouchEventType type);
	void onBackClicked(Ref *pSender, Widget::TouchEventType type);

	ListView *_listView;
	ModuleDelegate *_moduleDelegate;
	std::vector<Notice*> _notices;
	Sprite *_bg_notice;
};

#endif // __NOTICE_BOARD_H__
