#include "Ranking.h"

Ranking::Ranking()
{

}
Ranking::~Ranking()
{

}
Ranking* Ranking::create()
{
	Ranking* ranking = new (std::nothrow) Ranking();
	if (ranking && ranking->init()) {
		ranking->autorelease();
		return ranking;
	}
	CC_SAFE_DELETE(ranking);
	return nullptr;
}
bool Ranking::init()
{	
	this->setContentSize(_visibleSize);

	auto background = Sprite::create("ranking/background.png");
	background->setPosition(this->getContentSize() / 2);
	this->addChild(background);

	auto exit = MenuItemImage::create(
		"ranking/exit_normal.png",
		"ranking/exit_selected.png",
		CC_CALLBACK_1(Ranking::onExitClicked, this));
	exit->setPosition((background->getPosition() + background->getContentSize() / 2) - Vec2(50, 50));

	// create menu, it's an autorelease object
	auto menu = Menu::create(exit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	// Scroll view setting
	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setAnchorPoint(Point(0.5, 0.5));
	//scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	//scrollView->setBackGroundColor(Color3B::GRAY);
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(1140, 660));
	scrollView->setInnerContainerSize(Size(1160, 5500));
	scrollView->setPosition(background->getPosition() - Vec2(0,30));
	this->addChild(scrollView);

	for (int i = 0; i < 50; i++){

		_rankingItem[i] = RankingItem::create();
		_rankingItem[i]->setPosition(scrollView->getContentSize().width / 2, 
			scrollView->getInnerContainerSize().height - (_rankingItem[i]->getContentSize().height * (0.5 + i)));
		scrollView->addChild(_rankingItem[i]);
	}
	
	this->setScale(0);
	this->setOpacity(0);

	return true;
}
void Ranking::show()
{
	_moduleDelegate->onModuleBegan();

	auto action_0 = EaseBackOut::create(ScaleTo::create(0.5, 1));
	auto action_1 = FadeIn::create(0.5);
	auto action = Spawn::create(action_0, action_1, NULL);
	this->runAction(action);
	_director->getRunningScene()->addChild(this, 2);
}
void Ranking::destroy()
{
	this->removeAllChildren();
	this->removeFromParent();
}
void Ranking::onExitClicked(Ref* pSender)
{
	_moduleDelegate->onModuleEnded();
	this->destroy();
}
void Ranking::setItem(int ranking, TIER tier, const std::string nickName, const std::string rankPoint)
{
	_rankingItem[ranking]->setRanking(StringUtils::format("%d", ranking + 1));
	_rankingItem[ranking]->setTier(tier);
	_rankingItem[ranking]->setNickName(nickName);
	_rankingItem[ranking]->setRankPoint(rankPoint);
}
void Ranking::setDelegate(ModuleDelegate* md)
{
	_moduleDelegate = md;
}