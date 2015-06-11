#include "TierManual.h"

TierManual::TierManual()
{		
}
TierManual::~TierManual()
{
}
const std::string& TierManual::getModuleName()
{
	const static std::string moduleName("Store");
	return moduleName;
}
TierManual* TierManual::create()
{
	TierManual *manual = new (std::nothrow) TierManual();
	if (manual && manual->init())
	{
		manual->autorelease();
		return manual;
	}
	CC_SAFE_DELETE(manual);
	return nullptr;
}
bool TierManual::init()
{
	if (_director->getRunningScene()->getChildByName(getModuleName())) {
		return false;
	}

	setContentSize(_visibleSize);
		





	
	this->setName(getModuleName());

	return true;
}