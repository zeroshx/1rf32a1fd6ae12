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
	const std::string& getID();
	void setName(const std::string& name);
	const std::string& getName();
	void setNumber(const std::string& number);
	const std::string& getNumber();
	void setPlatform(const std::string& platform);
	const std::string& getPlatform();
	void setIMEI(const std::string& imei);
	const std::string& getIMEI();
	void setIMSI(const std::string& imsi);
	const std::string& getIMSI();
	void setOrigin(const std::string& origin);
	const std::string& getOrigin();
	
	void setChips(const std::string& chips);	
	const std::string& getChips();
	void setChipsInt(long long chips);
	long long getChipsInt();

	void setMaxBet(const std::string& max);
	const std::string& getMaxBet();
	void setMaxBetInt(int max);
	int getMaxBetInt();

	void parseOriginData();

private:

	// User Login Info
	std::string _id;
	std::string _name;
	std::string _number;
	std::string _platform;
	std::string _imei;
	std::string _imsi;

	std::string _originData;

	// SingleGame Info
	std::string _chips;
	std::string _maxBet;
};

#endif // __APP_USER_H__
