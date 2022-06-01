#include "asset_factory.hpp"
#include "assets/scene_assets.hpp"

namespace bt
{
AssetFactory::AssetFactory(ResourceFactory *rsrc_factory): rsrc_factory(rsrc_factory)
{}
AssetFactory::~AssetFactory()
{
    for (auto& [n, asset] : loaded_assets) {
        destroy(asset);
    }
    loaded_assets.clear();
    rsrc_factory = nullptr;
}
void AssetFactory::build()
{
    msg("AssetFactory::build", "building...");
    rsrc_factory->getTable(all_groups, "scene_groups");
    if (all_groups.size() == 0) {
        warn("AssetFactory::build", "bad scene_groups.json");
        return;
    }
}
void AssetFactory::loadSceneGroup(const std::string &group_name, std::vector<std::string> &scene_names)
{
    if (!all_groups.isMember(group_name)) {
        warn("AssetFactory::loadSceneGroup", "no scene group found for %s", group_name.c_str());
        return;
    }
    Json::Value root = all_groups[group_name];
    Json::Value scenes = root.get("scenes", Json::arrayValue);
    for (Json::Value::ArrayIndex i = 0; i != scenes.size(); i++) {
        std::string scene_name = scenes[i].asString();
        Json::Value root;
        rsrc_factory->getScene(root, scene_name);
        std::string scene_type = root.get("type", "").asString();
        if (scene_type == "instance") {
            InstanceAsset* inst_ast = new InstanceAsset();
            inst_ast->loadFromJson(root, rsrc_factory);
            loaded_assets[scene_name] = inst_ast;
            scene_names.push_back(scene_name);
        } else if (scene_type == "menu") {
            MenuAsset* menu_ast = new MenuAsset();
            menu_ast->loadFromJson(root, rsrc_factory);
            loaded_assets[scene_name] = menu_ast;
            scene_names.push_back(scene_name);
        }
    }
}
}
