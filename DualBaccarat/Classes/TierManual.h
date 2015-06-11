#ifndef __TIER_MANUAL_H__
#define __TIER_MANUAL_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

class TierManual : public cocos2d::Layer
{
public:

	TierManual();
	~TierManual();

	const std::string& getModuleName();

	static TierManual* create();
	virtual bool init();

private:


};

#endif // __TIER_MANUAL_H__
