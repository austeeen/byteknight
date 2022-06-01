#ifndef ASSET_HPP
#define ASSET_HPP

#include "common.hpp"
#include "json/json.h"
#include "datacore/event_core.hpp"
#include "utils/math.hpp"

namespace bt {
    class AssetFactory;
    class ResourceFactory;
}

namespace DATA
{
    void get(bool& dst, const Json::Value &val, const std::string& key);
    void get(unsigned int& dst, const Json::Value &val, const std::string& key);
    void get(int& dst, const Json::Value &val, const std::string& key);
    void get(std::string& dst, const Json::Value &val, const std::string& key);
    void get(bt::coord& dst, const Json::Value &val, const std::string& key);
    void get(bt::rect& dst, const Json::Value &val, const std::string& key);
    void get(sf::FloatRect& dst, const Json::Value &val, const std::string& key);
    void get(MSG& dst, const Json::Value &val, const std::string& key);

    void xycoord(bt::coord& dst, const Json::Value &val, const std::string& key);
    void xycoord(bt::coord& dst, const Json::Value &val, const std::string& key, const int c);
}

struct BaseJsonAsset
{
    BaseJsonAsset(): name("none"), type("none") {};
    virtual ~BaseJsonAsset() {};
    virtual void loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory);
    std::string name, type;
};

#endif // ASSET_HPP
