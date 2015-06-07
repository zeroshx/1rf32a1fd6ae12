#ifndef __BACCARAT_TYPE_DELEGATE_H__
#define __BACCARAT_TYPE_DELEGATE_H__

class BaccaratMode;

class BaccaratModeDelegate
{
public:

	virtual void onSinglePlaySelected(BaccaratMode* pDialog) = 0;
	virtual void onWorldClassSelected(BaccaratMode* pDialog) = 0;
};

#endif // __BACCARAT_TYPE_DELEGATE_H__