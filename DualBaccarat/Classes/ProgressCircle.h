#ifndef __PROGRESS_CIRCLE_H__
#define __PROGRESS_CIRCLE_H__

#include "PublicApi.h"
#include "ModuleDelegate.h"

USING_NS_CC;

class ProgressCircle : public Sprite
{
public:

	ProgressCircle();
	~ProgressCircle();

	static ProgressCircle* create();
	virtual bool init();
	void run();
	void stop();
	void setDelegate(ModuleDelegate* _md);
	
private :

	MODULE_STATE _state;
	ModuleDelegate *_moduleDelegate;
};

#endif // __PROGRESS_CIRCLE_H__
