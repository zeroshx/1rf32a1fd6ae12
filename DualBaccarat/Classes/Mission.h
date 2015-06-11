#ifndef __MISSION_H__
#define __MISSION_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

class Mission : public cocos2d::Layer
{
public:

	Mission();
	~Mission();

	const std::string& getModuleName();

	static Mission* create();
	virtual bool init();

private:


};

#endif // __MISSION_H__
