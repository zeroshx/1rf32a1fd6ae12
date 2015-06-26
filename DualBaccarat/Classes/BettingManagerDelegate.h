#ifndef __BETTING_MANAGER_DELEGATE_H__
#define __BETTING_MANAGER_DELEGATE_H__

class BettingRecord;

class BettingManagerDelegate
{
public:

	virtual void onRequestBetting(BettingRecord paper) = 0;
};

#endif // __BETTING_MANAGER_DELEGATE_H__
