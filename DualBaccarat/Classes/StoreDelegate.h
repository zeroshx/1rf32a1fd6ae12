#ifndef __STORE_DELEGATE_H__
#define __STORE_DELEGATE_H__

#include "cocos2d.h"

class StoreDelegate
{
public:

	virtual void onItembought(const std::string& itemCode) = 0;
};

#endif // __STORE_DELEGATE_H__
