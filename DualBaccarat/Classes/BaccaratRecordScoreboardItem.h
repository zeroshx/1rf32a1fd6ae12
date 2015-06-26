#ifndef __BACCARAT_RECORD__SCORDBOARD_ITEM_H__
#define __BACCARAT_RECORD__SCORDBOARD_ITEM_H__

#include "PublicApi.h"

USING_NS_CC;

#define ITEM_SIZE	Size(400,60)

typedef class BaccaratRecordScoreboardItem : public Node
{
public:

	BaccaratRecordScoreboardItem();
	~BaccaratRecordScoreboardItem();

	static BaccaratRecordScoreboardItem* create(const std::string& icon, const std::string& name);
	virtual bool init(const std::string& icon, const std::string& name);

	void setScore(const std::string& value);

private:

	Sprite *_icon;
	Label *_value;

} ScoreboardItem;

#endif // __BACCARAT_RECORD__SCORDBOARD_ITEM_H__
