#include "AppUser.h"

USING_NS_CC;

AppUser::AppUser()
{
	_id = "None";
	_name = "None";
	_number = "None";
	_platform = "None";
	_imei = "None";
	_imsi = "None";
	_originData = "None";
}
AppUser::~AppUser()
{

}
AppUser* AppUser::getInstance()
{
	static AppUser ins;
	return &ins;
}

void AppUser::setID(const std::string& id)
{
	_id = id;
}
const std::string& AppUser::getID()
{
	return _id;
}
void AppUser::setName(const std::string& name)
{
	_name = name;
}
const std::string& AppUser::getName()
{
	return _name;
}
void AppUser::setNumber(const std::string& number)
{
	_number = number;
}
const std::string& AppUser::getNumber()
{
	return _number;
}
void AppUser::setPlatform(const std::string& platform)
{
	_platform = platform;
}
const std::string& AppUser::getPlatform()
{
	return _platform;
}
void AppUser::setIMEI(const std::string& imei)
{
	_imei = imei;
}
const std::string& AppUser::getIMEI()
{
	return _imei;
}
void AppUser::setIMSI(const std::string& imsi)
{
	_imsi = imsi;
}
const std::string& AppUser::getIMSI()
{
	return _imsi;
}
void AppUser::setOrigin(const std::string& origin)
{
	_originData = origin;
}
const std::string& AppUser::getOrigin()
{
	return _originData;
}
void AppUser::setChips(const std::string& chips)
{
	_chips = chips;
}
const std::string& AppUser::getChips()
{
	return _chips;
}
void AppUser::setChipsInt(long long chips)
{
	_chips = StringUtils::format("%lld", chips);
}
long long AppUser::getChipsInt()
{	
	return atoll(_chips.c_str());
}

void AppUser::setMaxBet(const std::string& max)
{
	_maxBet = max;
}
const std::string& AppUser::getMaxBet()
{
	return _maxBet;
}
void AppUser::setMaxBetInt(int max)
{
	_maxBet = StringUtils::format("%d", max);
}
int AppUser::getMaxBetInt()
{
	return atoi(_maxBet.c_str());
}

void AppUser::parseOriginData()
{
	rapidjson::Document doc;
	if (doc.Parse<0>(_originData.c_str()).HasParseError()) {

		log("AppUser origin parsing error : %s", doc.GetParseError());
		return;
	}

	const rapidjson::Value& id = doc["ID"];
	setID(id.GetString());

	const rapidjson::Value& name = doc["Name"];
	setName(name.GetString());

	const rapidjson::Value& number = doc["Number"];
	setNumber(number.GetString());

	const rapidjson::Value& platform = doc["Platform"];
	setPlatform(platform.GetString());

	const rapidjson::Value& imei = doc["IMEI"];
	setIMEI(imei.GetString());

	const rapidjson::Value& imsi = doc["IMSI"];
	setIMSI(imsi.GetString());
}