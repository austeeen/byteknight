#include "asset_bases.hpp"
#include "factory/asset_factory.hpp"

/**************************************************************************************************/
/* DATA */
const int _INT = -1;
const char* _COORD = "-1,-1";
const char* _SIZE = "-1.0,-1.0";
const char* _RECT = "0,0,0,0";
const char* _STR = "";

namespace DATA
{
void get(bool& dst, const Json::Value &val, const std::string& key) {
    dst = val.get(key, false).asBool();
}
void get(unsigned int& dst, const Json::Value &val, const std::string& key) {
    dst = val.get(key, _INT).asInt();
}
void get(int& dst, const Json::Value &val, const std::string& key) {
    dst = val.get(key, _INT).asInt();
}
void get(std::string& dst, const Json::Value &val, const std::string& key) {
    dst = val.get(key, _STR).asString();
}
void get(bt::coord& dst, const Json::Value &val, const std::string& key) {
    dst = bt::coord(val.get(key, _COORD).asString());
}
void get(bt::rect& dst, const Json::Value &val, const std::string& key) {
    dst = bt::rect(val.get(key, _RECT).asString());
}
void get(sf::FloatRect& dst, const Json::Value &val, const std::string& key) {
    dst = bt::rect(val.get(key, _RECT).asString());
}
void get(MSG& dst, const Json::Value &val, const std::string& key) {
    std::string action_str = "";
    dst = MSG::NO_EVENT;
    get(action_str, val, key);
    if (action_str != "") {
        dst = MSGTBL.at(action_str);
    }
}
void xycoord(bt::coord& dst, const Json::Value &val, const std::string& key) {
    dst = bt::coord(val.get(key, _COORD).asString(), 0, 0);
}
void xycoord(bt::coord& dst, const Json::Value &val, const std::string& key, const int c) {
    dst = bt::coord(val.get(key, _COORD).asString(), 0, c);
}
}

void BaseJsonAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    DATA::get(name, root, "name");
    DATA::get(type, root, "type");
}
