#include "AppUser.h"

USING_NS_CC;

AppUser::AppUser()
{
	ID = "None";
	Name = "None";
	Number = "None";
	Platform = "None";
	IMEI = "None";
	IMSI = "None";
	Origin = "None";
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
	ID = id;
}
void AppUser::setName(const std::string& name)
{
	Name = name;
}
void AppUser::setNumber(const std::string& number)
{
	Number = number;
}
void AppUser::setPlatform(const std::string& platform)
{
	Platform = platform;
}
void AppUser::setIMEI(const std::string& imei)
{
	IMEI = imei;
}
void AppUser::setIMSI(const std::string& imsi)
{
	IMSI = imsi;
}
void AppUser::setOrigin(const std::string& origin)
{
	Origin = origin;
}

const std::string& AppUser::getID()
{
	return ID;
}
const std::string& AppUser::getName()
{
	return Name;
}
const std::string& AppUser::getNumber()
{
	return Number;
}
const std::string& AppUser::getPlatform()
{
	return Platform;
}
const std::string& AppUser::getIMEI()
{
	return IMEI;
}
const std::string& AppUser::getIMSI()
{
	return IMSI;
}
const std::string& AppUser::getOrigin()
{
	return Origin;
}

void AppUser::parseOrigin()
{
	rapidjson::Document doc;
	if (doc.Parse<0>(Origin.c_str()).HasParseError()) {

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