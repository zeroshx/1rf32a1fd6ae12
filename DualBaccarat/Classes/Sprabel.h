#ifndef __SPRABEL_H__
#define __SPRABEL_H__

#include "cocos2d.h"
#include "PublicApi.h"

USING_NS_CC;

class Sprabel: public Sprite
{
public:

	Sprabel();
	~Sprabel();

	static Sprabel* create(const std::string spr);
	static Sprabel* create(const std::string spr, const std::string str);
	virtual bool init(const std::string spr, const std::string str);
	void setString(const std::string str);

private:

	Label *_label;
};

#endif // __SPRABEL_H__
