#ifndef FCT_ASSET_HPP
#define FCT_ASSET_HPP

#include "common.hpp"
#include "assets/asset_bases.hpp"
#include "rsrc_factory.hpp"

class AssetFactory
{
public:
    AssetFactory(ResourceFactory* rsrc_factory);
    ~AssetFactory();
    void build();
    void loadSceneGroup(const std::string &group_name, std::vector<std::string> &scene_ast_ids);
    template <typename T>
    T* get(const std::string& ast_name) {
        if (loaded_assets.count(ast_name) == 0) {
            SQ::err("AssetFactory::get", "%s not found", ast_name.c_str());
            return nullptr;
        }

        T* ast = dynamic_cast<T*>(loaded_assets.at(ast_name));
        if (ast == nullptr) {
            SQ::err("AssetFactory::get", "%s could not be cast to requested type", ast_name.c_str());
        }
        return ast;
    }
private:
    ResourceFactory* rsrc_factory;
    Json::Value all_groups;
    std::map<const std::string, BaseJsonAsset*> loaded_assets;
};

#endif // FCT_ASSET_HPP
