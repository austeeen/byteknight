#ifndef ASSET_HPP
#define ASSET_HPP

#include "common.hpp"
#include "json/json.h"
#include "datacore/event_core.hpp"
#include "math/math.hpp"

class AssetFactory;
class ResourceFactory;

namespace DATA
{
    void get(bool& dst, const Json::Value &val, const std::string& key);
    void get(unsigned int& dst, const Json::Value &val, const std::string& key);
    void get(int& dst, const Json::Value &val, const std::string& key);
    void get(std::string& dst, const Json::Value &val, const std::string& key);
    void get(SQ::coord& dst, const Json::Value &val, const std::string& key);
    void get(SQ::rect& dst, const Json::Value &val, const std::string& key);
    void get(sf::FloatRect& dst, const Json::Value &val, const std::string& key);
    void get(MSG& dst, const Json::Value &val, const std::string& key);

    void xycoord(SQ::coord& dst, const Json::Value &val, const std::string& key);
    void xycoord(SQ::coord& dst, const Json::Value &val, const std::string& key, const int c);
}

struct BaseJsonAsset
{
    BaseJsonAsset(): name("none"), type("none") {};
    virtual ~BaseJsonAsset() {};
    virtual void loadFromJson(Json::Value &root, ResourceFactory *rsrc_factory);
    std::string name, type;
};

#endif // ASSET_HPP
