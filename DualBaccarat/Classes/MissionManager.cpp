#include "MissionManager.h"

MissionManager::MissionManager()
{		
}
MissionManager::~MissionManager()
{
}
MissionManager* MissionManager::create()
{
	MissionManager *manager = new (std::nothrow) MissionManager();
	if (manager && manager->init())
	{
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return nullptr;
}
bool MissionManager::init()
{
	setContentSize(_visibleSize);
		
	auto bg_manager = Sprite::create("mission/bg_mission_manager.png");
	bg_manager->setPosition(_center);
	this->addChild(bg_manager);

	auto exitBtn = Button::create("mission/button_normal.png", "mission/button_pressed.png");
	exitBtn->setTitleText("EXIT");
	exitBtn->setTitleFontSize(40);
	exitBtn->setPosition(Vec2(bg_manager->getContentSize().width / 2, 70));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(MissionManager::onExitClicked, this));
	bg_manager->addChild(exitBtn);
	
	_listView = ListView::create();
	_listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_listView->setTouchEnabled(true);
	_listView->setBounceEnabled(true);
	_listView->setContentSize(Size(1100, 650));
	_listView->setAnchorPoint(Point(0.5, 0.5));
	_listView->setPosition(Vec2(bg_manager->getContentSize() / 2));
	_listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
	_listView->setItemsMargin(10);
	bg_manager->addChild(_listView);
	
	this->setScale(0);
	this->setOpacity(0);

	setMissions();
	setMissionManager();

	return true;
}
void MissionManager::onExitClicked(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		destroy();
	}
} 
void MissionManager::onMissionSelected(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		
	}
}
void MissionManager::show()
{
	_moduleDelegate->onModuleBegan();

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	this->runAction(action);
	_director->getRunningScene()->addChild(this, 2);
}
void MissionManager::destroy()
{
	_moduleDelegate->onModuleEnded();

	this->removeAllChildren();
	this->removeFromParent();
}
void MissionManager::setDelegate(ModuleDelegate* md)
{
	_moduleDelegate = md;
}
void MissionManager::setMissions()
{
	for (int i = 0; i < 5; i++)
	{
		auto miss = new Mission();
		miss->_id = StringUtils::format("%da%db%dc", i, i, i);
		miss->_title = StringUtils::format("Mission %d", i);
		miss->_reward = StringUtils::format("%d", i*1000);
		miss->_reward_type = REWARD_TYPE::CHIP;
		miss->_mission_state = MISSION_STATE::COMPLETE;
		miss->_current_value = StringUtils::format("%d", i+1);
		miss->_goal_value = StringUtils::format("%d", (i+1)*i+1);

		_missions.push_back(miss);
	}
}
Layout* MissionManager::setItemModel(Mission* mission)
{
	Layout* layout = Layout::create();
	layout->setTouchEnabled(true);
	layout->setContentSize(Size(1100, 240));

	auto bg_mission = Button::create("mission/bg_mission_normal.png", "mission/bg_mission_pressed.png");
	bg_mission->setName(mission->_id);	
	bg_mission->setPosition(bg_mission->getContentSize() / 2);
	bg_mission->addTouchEventListener(CC_CALLBACK_2(MissionManager::onMissionSelected, this));
	layout->addChild(bg_mission);

	auto mission_title = Text::create(mission->_title, _font, 50);
	mission_title->setAnchorPoint(Point(0, 0));
	mission_title->setColor(Color3B::BLACK);
	mission_title->setPosition(Vec2(30, 160));
	bg_mission->addChild(mission_title);

	auto bg_progressbar = ImageView::create("mission/bg_progressbar.png");
	bg_progressbar->setPosition(bg_mission->getContentSize() / 2);
	bg_mission->addChild(bg_progressbar);

	LoadingBar* loadingBar = LoadingBar::create("mission/progressbar.png");
	loadingBar->setContentSize(Size(1000, 80));
	loadingBar->setDirection(LoadingBar::Direction::LEFT);		
	loadingBar->setPosition(bg_progressbar->getContentSize() / 2);	
	loadingBar->setPercent((atoi(mission->_current_value.c_str())*100) / atoi(mission->_goal_value.c_str()));
	bg_progressbar->addChild(loadingBar);

	auto gauge = Text::create(mission->_current_value + " / " + mission->_goal_value, _font, 30);
	gauge->setPosition(bg_progressbar->getContentSize() / 2);
	bg_progressbar->addChild(gauge);

	auto reward = Text::create(mission->_reward, _font, 40);
	reward->setColor(Color3B::BLUE);
	reward->setAnchorPoint(Point(1, 0));
	reward->setPosition(Vec2(1050, 20));
	bg_mission->addChild(reward);

	std::string path;
	switch (mission->_reward_type) {
	case REWARD_TYPE::CHIP:
		path = "mission/icon_chip.png";
		break;
	case REWARD_TYPE::RP :
		path = "mission/icon_rp.png";
		break;
	case REWARD_TYPE::TICKET :
		path = "mission/icon_ticket.png";
		break;
	}

	auto reward_type = ImageView::create(path);
	reward_type->setAnchorPoint(Point(1, 0));
	reward_type->setPosition(Vec2(1100 - reward->getContentSize().width - 70, 20));
	bg_mission->addChild(reward_type);

	auto bg_reward_head = ImageView::create("mission/bg_reward_head.png");
	bg_reward_head->setAnchorPoint(Point(1, 0));
	bg_reward_head->setPosition(Vec2(1100 - reward->getContentSize().width - reward_type->getContentSize().width - 80, 20));
	bg_mission->addChild(bg_reward_head);

	if (mission->_mission_state == MISSION_STATE::COMPLETE) {

		auto completed = ImageView::create("mission/bg_completed.png");		
		completed->setPosition(bg_mission->getContentSize() / 2);
		bg_mission->addChild(completed);
	}
	
	return layout;
}
void MissionManager::setMissionManager()
{
	for (auto iter : _missions)
	{
		_listView->addChild(setItemModel(iter));
	}
}