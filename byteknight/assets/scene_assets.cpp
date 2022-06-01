#include "scene_assets.hpp"
#include "factory/asset_factory.hpp"

/**************************************************************************************************/
void LayerAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    BaseJsonAsset::loadFromJson(root, rsrc_factory);
    DATA::get(lyr_cols, root, "lyr_cols");
    DATA::get(gid_str, root, "gid_str");
    DATA::get(render_order, root, "render_order");
    DATA::get(img_src, root, "img_src");
    if (img_src != "") {
        rsrc_factory->getImage(img_texture, img_cols, img_src);
    }
}
/**************************************************************************************************/
void ObjectLayerAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    LayerAsset::loadFromJson(root, rsrc_factory);
    Json::Value object_list = root["objects"];
    for (Json::Value::ArrayIndex i = 0; i != object_list.size(); i++) {
        obj_list.push_back(ObjectAsset(object_list[i], lyr_cols, rsrc_factory));
    }
}
/**************************************************************************************************/
void InstanceAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    BaseJsonAsset::loadFromJson(root, rsrc_factory);
    DATA::get(scenedata.board_size, root, "board_size");
    DATA::get(scenedata.tile_size, root, "tile_size");
    DATA::get(scenedata.pxl_size, root, "pxl_size");
    scenedata.total_tiles = scenedata.board_size.width * scenedata.board_size.height;
    backdrop_lyr_ast.loadFromJson(root["layers"][0], rsrc_factory);
    tile_lyr_ast.loadFromJson(root["layers"][1], rsrc_factory);
    object_lyr_ast.loadFromJson(root["layers"][2], rsrc_factory);
}
/**************************************************************************************************/
void MenuAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    BaseJsonAsset::loadFromJson(root, rsrc_factory);
    Json::Value widget_list = root["widgets"];
    for (Json::Value::ArrayIndex i = 0; i != widget_list.size(); i++) {
        widget_assets.push_back(WidgetAsset(widget_list[i], i, rsrc_factory));
    }
}
