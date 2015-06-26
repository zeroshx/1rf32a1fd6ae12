#ifndef __MISSION_MANAGER_H__
#define __MISSION_MANAGER_H__

#include "PublicApi.h"
#include "ModuleDelegate.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class Mission
{
public:

	std::string _id;
	std::string _title;
	std::string _current_value;
	std::string _goal_value;
	std::string _reward;
	REWARD_TYPE _reward_type;
	MISSION_STATE _mission_state;
};


class MissionManager : public cocos2d::Layer
{
public:

	MissionManager();
	~MissionManager();

	static MissionManager* create();
	virtual bool init();
	void show();
	void destroy();
	void setDelegate(ModuleDelegate* md);
	Layout* setItemModel(Mission* mission);
	void setMissions();
	void setMissionManager();

private:

	void onMissionSelected(Ref *pSender, Widget::TouchEventType type);
	void onExitClicked(Ref *pSender, Widget::TouchEventType type);

	ListView *_listView;
	ModuleDelegate *_moduleDelegate;
	std::vector<Mission*> _missions;
};

#endif // __MISSION_MANAGER_H__
