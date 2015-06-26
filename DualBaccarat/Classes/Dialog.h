#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "PublicApi.h"
#include "DialogDelegate.h"

USING_NS_CC;

class Dialog : public cocos2d::Layer
{
public:

	static const int BUTTON_TYPE_1 = 0;
	static const int BUTTON_TYPE_2 = 1;

	Dialog();
	~Dialog();

	static Dialog* create();
	bool init();

	void show();
	void destroy();

	void setIndex(int index);

	void setTitle(const std::string& title);
	void setMessage(const std::string& message);
	void setPositiveButtonText(const std::string& text);
	void setNegativeButtonText(const std::string& text);
	void setButtonType(int type);

	void onClickPositive(Ref* sender);
	void onClickNegative(Ref* sender);

	void setDelegate(DialogDelegate* dialogDelegate);

private:

	int _index;
	
	int _btnType;

	Sprite* _bg;

	std::string _title;
	Label* _titleLabel;
	Sprite* _titleImage;

	std::string _message;
	Label* _messageLabel;
	Sprite* _messageImage;

	std::string _positiveText;
	MenuItemImage* _positiveImage;
	Label* _positiveLabel;

	std::string _negativeText;
	MenuItemImage* _negativeImage;
	Label* _negativeLabel;

	DialogDelegate* _delegate;
	Scene* _scene;
};

#endif // __DIALOG_H__