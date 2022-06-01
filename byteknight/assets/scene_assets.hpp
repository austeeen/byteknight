#ifndef AST_SCENE_HPP
#define AST_SCENE_HPP

#include "asset_bases.hpp"
#include "object_assets.hpp"
#include "gui_assets.hpp"
#include "datacore/common_core.hpp"

struct LayerAsset: BaseJsonAsset
{
    virtual void loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory) override;
    int render_order, lyr_cols, img_cols;
    std::string gid_str, img_src;
    sf::Texture img_texture;
};

struct ObjectLayerAsset: LayerAsset
{
    virtual void loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory) override;
    std::vector<ObjectAsset> obj_list;
};

struct SceneAssetBase: BaseJsonAsset
{};

struct InstanceAsset: SceneAssetBase
{
    virtual void loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory) override;
    Meta::gamedata scenedata;
    LayerAsset backdrop_lyr_ast, tile_lyr_ast;
    ObjectLayerAsset object_lyr_ast;
};

struct MenuAsset: SceneAssetBase
{
    virtual void loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory) override;
    bt::rect view_rect;
    std::vector<WidgetAsset> widget_assets;
};

#endif // AST_SCENE_HPP
