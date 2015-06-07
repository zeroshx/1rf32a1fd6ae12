#ifndef __BACCARAT_TYPE_H__
#define __BACCARAT_TYPE_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "BaccaratModeDelegate.h"

USING_NS_CC;

class BaccaratMode : public Layer
{
public:

	BaccaratMode();
	~BaccaratMode();

	const std::string& getModuleName();

	static BaccaratMode* create();
	virtual bool init();
	void show();
	void destroy();
	void setDelegate(BaccaratModeDelegate* _typeDelegate);

	void onSinglePlaySelected(Ref* pSender);
	void onWorldClassSelected(Ref* pSender);
	void onExitSelected(Ref* pSender);

private:

	BaccaratModeDelegate *_delegate;
};

#endif // __BACCARAT_TYPE_H__
