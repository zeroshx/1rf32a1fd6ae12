#include "Mission.h"

Mission::Mission()
{		
}
Mission::~Mission()
{
}
const std::string& Mission::getModuleName()
{
	const static std::string moduleName("Mission");
	return moduleName;
}
Mission* Mission::create()
{
	Mission *mission = new (std::nothrow) Mission();
	if (mission && mission->init())
	{
		mission->autorelease();
		return mission;
	}
	CC_SAFE_DELETE(mission);
	return nullptr;
}
bool Mission::init()
{
	if (_director->getRunningScene()->getChildByName(getModuleName())) {
		return false;
	}

	setContentSize(_visibleSize);
		





	
	this->setName(getModuleName());

	return true;
}