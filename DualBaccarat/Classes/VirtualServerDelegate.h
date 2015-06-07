#ifndef __VIRTUAL_SERVER_DELEGATE_H__
#define __VIRTUAL_SERVER_DELEGATE_H__

enum class GAME_STATE
{
	READY,
	SHUFFLE,
	BET,
	DEALING,
	GAMEOVER
};

class VirtualServerDelegate
{
public:

	virtual void onStageShuffle() = 0;
	virtual void onStageBetting(int time) = 0;
	virtual void onStageDealing(std::vector<PokerCard> cardset) = 0;
	virtual void onStageGameover(Winner winner) = 0;
};

#endif // __VIRTUAL_SERVER_DELEGATE_H__
