#ifndef __BACCARAT_TYPE_H__
#define __BACCARAT_TYPE_H__

#include "PublicApi.h"
#include "BaccaratModeDelegate.h"
#include "ModuleDelegate.h"

USING_NS_CC;

class BaccaratMode : public Layer
{
public:

	BaccaratMode();
	~BaccaratMode();
	
	static BaccaratMode* create();
	virtual bool init();
	void show();
	void destroy();
	void setDelegate(BaccaratModeDelegate* dg1, ModuleDelegate* dg2);

	void onSinglePlaySelected(Ref* pSender);
	void onWorldClassSelected(Ref* pSender);
	void onExitSelected(Ref* pSender);

private:

	BaccaratModeDelegate *_delegate;
	ModuleDelegate *_moduleDelegate;
};

#endif // __BACCARAT_TYPE_H__
