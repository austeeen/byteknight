#ifndef AST_OBJECTS_HPP
#define AST_OBJECTS_HPP

#include "asset_bases.hpp"
#include "datacore/object_core.hpp"

struct ObjectAsset: BaseJsonAsset
{
    ObjectAsset(Json::Value &root, const int cols, ResourceFactory *rsrc_factory) {
        lyr_cols = cols;
        loadFromJson(root, rsrc_factory);
    };
    virtual void loadFromJson(Json::Value &root, ResourceFactory *rsrc_factory) override;
    Object::ID id;
    Groups::ID group_id;
    int type_id, speed, acl, img_cols, lyr_cols;
    std::string class_type, move_set, img_src, group_name;
    sf::Texture img_texture;
    sptr<sf::Text> nametag;
    SQ::rect position, texture_rect, collision_rect;
    SQ::coord start_coord;
};

#endif // AST_OBJECTS_HPP
