#ifndef __PROGRESS_CIRCLE_H__
#define __PROGRESS_CIRCLE_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

class ProgressCircle : public Sprite
{
public:

	enum class MODULE_STATE
	{
		IDLE,
		START,
		DONE
	};

	ProgressCircle();
	~ProgressCircle();

	static ProgressCircle* create();
	virtual bool init();
	void run();
	void stop();
	
private :

	MODULE_STATE _state;
};

#endif // __PROGRESS_CIRCLE_H__
