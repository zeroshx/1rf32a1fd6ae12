#ifndef __APP_USER_H__
#define __APP_USER_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json/reader.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

USING_NS_CC;

class AppUser 
{
public:

	static AppUser* getInstance();
		
	AppUser();
	~AppUser();

	void setID(const std::string& id);
	void setName(const std::string& name);
	void setNumber(const std::string& number);
	void setPlatform(const std::string& platform);
	void setIMEI(const std::string& imei);
	void setIMSI(const std::string& imsi);
	void setOrigin(const std::string& origin);

	const std::string& getID();
	const std::string& getName();
	const std::string& getNumber();
	const std::string& getPlatform();
	const std::string& getIMEI();
	const std::string& getIMSI();
	const std::string& getOrigin();

	void parseOrigin();

private:

	std::string ID;
	std::string Name;
	std::string Number;
	std::string Platform;
	std::string IMEI;
	std::string IMSI;

	std::string Origin;
};

#endif // __BACCARAT_PLAYER_H__
