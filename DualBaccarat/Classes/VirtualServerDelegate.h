#ifndef __VIRTUAL_SERVER_DELEGATE_H__
#define __VIRTUAL_SERVER_DELEGATE_H__

class VirtualServerDelegate
{
public:

	virtual void onStageReady() = 0;
	virtual void onStageShuffle() = 0;
	virtual void onStageBetting(int time) = 0;
	virtual void onStageDealing(std::vector<PokerCard> cardset) = 0;
	virtual void onStageGameover(WINNER winner, PAIR pair, std::vector<EXTRA_WINNER> extras) = 0;
};

#endif // __VIRTUAL_SERVER_DELEGATE_H__
